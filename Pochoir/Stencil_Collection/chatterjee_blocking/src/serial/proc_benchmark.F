
      program proc_benchmark
      implicit none

#ifndef DEBUG
#include "f90papi.h"
#endif

      integer nx, ny, nz, num_iter
      parameter (nx=128, ny=1, nz=1)
      parameter (num_iter=10**6)
      double precision A(nx+2,ny+2,nz+2), B(nx+2,ny+2,nz+2)

!     TRIAL COUNTS AND TIMES
      integer num_trials, trial_num
      parameter (num_trials=5)
      double precision trial_times(num_trials)

!     FLUSHING THE CACHE
      integer flush_cache_size
      parameter (flush_cache_size=8388608)
      double precision FC(flush_cache_size)

#ifndef DEBUG
      integer check
      integer num_desired_events, desired_event_num
      integer num_available_events
      parameter(num_desired_events = 9)
      integer desired_events(num_desired_events)
      logical available_events(num_desired_events)
      integer*8 counter_values(num_trials)
      character*(PAPI_MAX_STR_LEN) event_name

      desired_events(1:num_desired_events) = (/ PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCA, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS /)

      call papi_initialize()
#endif

      print "(/, a, a)", "7-point stencil, no add, naive Fortran code with non-periodic boundary conditions"
      print "(a, /, i10, a)", "num_iter = ", num_iter, ", "
      print "(a, /, i4, a, i4, a, i4, a)", "full grid size =", (nx+2), ", ", (ny+2), ", ", (nz+2), ", "
      print "(a, /, i4, a, i4, a, i4, a)", "real grid size =", nx, ", ", ny, ", ", nz, ", "
#ifndef DEBUG
      print "(a, /, i1, a, /)", "num_sets = ", num_available_events, ", "
#endif

      call init_flush_cache()
      call init_grids()

!     THE FOLLOWING CALLS CHANGE THE PASSED PARAMETERS

#ifndef DEBUG
      do 10 desired_event_num = 1, num_desired_events
         if (available_events(desired_event_num).eqv..true.) then
            do 20 trial_num = 1, num_trials
               call flush_cache()
               call PAPIF_start_counters(desired_events(desired_event_num), 1, check)
#endif

               call stencil()

#ifndef DEBUG
               call PAPIF_stop_counters(counter_values(trial_num), 1, check)
 20         continue
            call PAPIF_event_code_to_name(desired_events(desired_event_num), event_name, check)
            print "(a12, a)", event_name, " = "
            print "(5(i11, a))", counter_values(1), ", ", counter_values(2), ", ", counter_values(3), ", ", counter_values(4), ", ", counter_values(5), ", "
         endif
 10   continue
#endif

      call checksum()

      contains

!     ********* SUBROUTINES ***********************

#ifndef DEBUG
      subroutine papi_initialize()
      integer i
      
      check = PAPI_VER_CURRENT
      call PAPIF_library_init(check)

      if (check.ne.PAPI_VER_CURRENT) then
         write (*,*) "PAPI Version Error!"
      endif

      num_available_events = 0
      do i= 1, num_desired_events
         call PAPIF_query_event(desired_events(i), check)
         if (check.eq.PAPI_OK) then
            available_events(i) = .true.
            num_available_events = num_available_events + 1
         else
            available_events(i) = .false.
         endif
      enddo
      end subroutine papi_initialize
#endif

      subroutine init_flush_cache()
      integer i

      do 10 i = 1, flush_cache_size
         FC(i) = 0.0;
 10   continue
      end subroutine init_flush_cache

      subroutine flush_cache()
      integer i

      do 10 i = 1, flush_cache_size
         FC(i) = FC(i) + 1.0;
 10   continue
      end subroutine flush_cache

      subroutine checksum()
      double precision cs;
      integer i

      do 10 i = 1, flush_cache_size
         cs = cs + FC(i)
 10   continue

      cs = cs / flush_cache_size
      print "(/, a, f5.0)", "checksum = ", cs
      end subroutine checksum


      subroutine print_grid(C)
      integer i, j, k
      double precision C(nx+2, ny+2, nz+2)

      do 10 k = 1, nz+2
         do 20 j = 1, ny+2
            do 30 i = 1, nx+2
               print *, i, j, k, " = ",  C(i,j,k)
 30         continue
            print *, "\n"
 20      continue
 10   continue
      end subroutine print_grid
      
      subroutine init_grids()
      integer i, j, k

!     ** initialized full arrays (including ghost cells) **
      do 10 k = 1, nz+2
         do 20 j = 1, ny+2
            do 30 i = 1, nx+2
               A(i,j,k) = 1.5;
               B(i,j,k) = 1.5;
 30         continue
 20      continue
 10   continue

!     ** initialized non-ghost cells **
      do 40 k = 2, nz+1
         do 50 j = 2, ny+1
            do 60 i = 2, nx+1
               A(i,j,k) = 1.5;
 60         continue
 50      continue
 40   continue
      end subroutine init_grids

      subroutine stencil()
      integer i, j, k, t
      double precision S0, S1
      parameter(S0=2.5, S1=-0.25)

      do 10 t = 1, num_iter
         if (mod(num_iter, 2).eq.1) then
            do 20 k = 2, nz+1
               do 30 j = 2, ny+1
                  do 40 i = 2, nx+1
                     B(i,j,k) = S0 * A(i,j,k) + S1 * (A(i,j,k-1) + A(i,j,k+1) + A(i,j-1,k) + A(i,j+1,k) + A(i-1,j,k) + A(i+1,j,k))
 40               continue
 30            continue
 20         continue
         else
            do 50 k = 2, nz+1
               do 60 j = 2, ny+1
                  do 70 i = 2, nx+1
                     A(i,j,k) = S0 * B(i,j,k) + S1 * (B(i,j,k-1) + B(i,j,k+1) + B(i,j-1,k) + B(i,j+1,k) + B(i-1,j,k) + B(i+1,j,k))
 70               continue
 60            continue
 50         continue
         endif
 10   continue
      end subroutine stencil

      end program proc_benchmark
