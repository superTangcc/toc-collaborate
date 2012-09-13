
      program naive
      implicit none

#ifndef DEBUG
#include "f90papi.h"
#endif

      integer nx, ny, nz, num_iter
      integer nreals_x, nreals_y, nreals_z
      integer realMin_x, realMin_y, realMin_z
      integer realMax_x, realMax_y, realMax_z
      integer ghostCellDepth
      parameter (ghostCellDepth=1)

#ifdef ALIASED
      integer t, iter_flag
#endif
#ifdef STATIC_ALLOC
      parameter (nreals_x=256, nreals_y=256, nreals_z=256)
      double precision A(nreals_x+2*ghostCellDepth, nreals_y+2*ghostCellDepth, nreals_z+2*ghostCellDepth), &
      B(nreals_x+2*ghostCellDepth, nreals_y+2*ghostCellDepth, nreals_z+2*ghostCellDepth)
#endif
#ifdef DYNAMIC_ALLOC
      double precision, dimension(:, :, :), allocatable :: A, B
#endif

!     TRIAL COUNTS AND TIMES
      integer num_trials, trial_num
      parameter (num_trials=5)
      double precision trial_times(num_trials)

!     FLUSHING THE CACHE
      integer flush_cache_array_size
      parameter (flush_cache_array_size=8388608)
      double precision FC(flush_cache_array_size)

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

#ifdef STATIC_ALLOC
      read *, num_iter
#endif
#ifdef DYNAMIC_ALLOC
      read *, num_iter, nreals_x, nreals_y, nreals_z
#endif
      nx = nreals_x + 2*ghostCellDepth
      ny = nreals_y + 2*ghostCellDepth
      nz = nreals_z + 2*ghostCellDepth
#ifdef DYNAMIC_ALLOC
      allocate (A(nx, ny, nz))
      allocate (B(nx, ny, nz))
#endif

      realMin_x = ghostCellDepth + 1
      realMin_y = ghostCellDepth + 1
      realMin_z = ghostCellDepth + 1
      realMax_x = realMin_x + nreals_x - 1
      realMax_y = realMin_y + nreals_y - 1
      realMax_z = realMin_z + nreals_z - 1

      print "(/, a, a)", "7-point stencil, no add, naive Fortran code with non-periodic boundary conditions"
      print "(a, /, i8, a)", "num_iter = ", num_iter, ", "
      print "(a, /, i4, a, i4, a, i4, a)", "full grid size =", nx, ", ", ny, ", ", nz, ", "
      print "(a, /, i4, a, i4, a, i4, a)", "real grid size =", nreals_x, ", ", nreals_y, ", ", nreals_z, ", "
      print "(a, /, a)", "cache block size =", "0, 0, 0"
#ifndef DEBUG
      print "(a, /, i1, a, /)", "num_sets = ", num_available_events, ", "
#endif

      call init_flush_cache_array()

!     THE FOLLOWING CALLS CHANGE THE PASSED PARAMETERS

#ifndef DEBUG
      do 10 desired_event_num = 1, num_desired_events
         if (available_events(desired_event_num).eqv..true.) then
            do 20 trial_num = 1, num_trials
#endif
               call init_grids()
               call flush_cache()
#ifndef DEBUG
               call PAPIF_start_counters(desired_events(desired_event_num), 1, check)
#endif
#ifdef ALIASED
               iter_flag = 0

               do 30 t = 1, num_iter
                  if (iter_flag.eq.0) then
                     call naive_stencil(A, B)
                  else
                     call naive_stencil(B, A)
                  endif
                  iter_flag = 1-iter_flag
 30            continue
#endif
#ifdef UNALIASED
               call naive_stencil()
#endif
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

      subroutine print_grid(C)
      integer i, j, k
      double precision C(nx, ny, nz)

      do 10 k = 1, nz
         do 20 j = 1, ny
            do 30 i = 1, nx
               print *, i, j, k, " = ",  C(i,j,k)
 30         continue
            print *, "\n"
 20      continue
 10   continue
      end subroutine print_grid
      
      subroutine init_flush_cache_array()
      integer i;
      
      do 10 i = 1, flush_cache_array_size
         FC(i) = 0.0
 10   continue
      end subroutine init_flush_cache_array
      
      subroutine flush_cache()
      integer i
      
      do 10 i = 1, flush_cache_array_size
         FC(i) = FC(i) + 1.0
 10   continue
      end subroutine flush_cache
      
      subroutine checksum()
      integer i
      double precision cs
      
      cs = 0.0
      do 10 i = 1, flush_cache_array_size
         cs = cs + FC(i)
 10   continue
      cs = cs / flush_cache_array_size
      print *, " "
      print *, "checksum =", cs
      end subroutine checksum
      
      subroutine init_grids()
      integer i, j, k

!     ** initialize full arrays (including ghost cells) **
      do 10 k = 1, nz
         do 20 j = 1, ny
            do 30 i = 1, nx
               A(i,j,k) = 0
               B(i,j,k) = 0
 30         continue
 20      continue
 10   continue

!     ** initialize non-ghost cells **
      do 40 k = realMin_z, realMax_z
         do 50 j = realMin_y, realMax_y
            do 60 i = realMin_x, realMax_x
               A(i,j,k) = 1
 60         continue
 50      continue
 40   continue
      end subroutine init_grids

#ifdef ALIASED
      subroutine naive_stencil(C, D)
      integer i, j, k
      double precision S0, S1
      parameter(S0=4, S1=2)
      double precision C(nx, ny, nz), D(nx, ny, nz)
      
      do 20 k = realMin_z, realMax_z
         do 30 j = realMin_y, realMax_y
            do 40 i = realMin_x, realMax_x
               D(i,j,k) = S0 * C(i,j,k) &
               + S1 * (C(i,j,k-1) + C(i,j,k+1) + C(i,j-1,k) + C(i,j+1,k) + C(i-1,j,k) + C(i+1,j,k))
 40         continue
 30      continue
 20   continue
      end subroutine naive_stencil
#endif
#ifdef UNALIASED
      subroutine naive_stencil()
      integer i, j, k, t
      double precision S0, S1
      parameter(S0=4, S1=2)
      integer iter_flag

      iter_flag = 0

      do 10 t = 1, num_iter
         if (iter_flag.eq.0) then
            do 20 k = realMin_z, realMax_z
               do 30 j = realMin_y, realMax_y
                  do 40 i = realMin_x, realMax_x
                     B(i,j,k) = S0 * A(i,j,k) &
                     + S1 * (A(i,j,k-1) + A(i,j,k+1) + A(i,j-1,k) + A(i,j+1,k) + A(i-1,j,k) + A(i+1,j,k))
 40               continue
 30            continue
 20         continue
         else
            do 50 k = realMin_z, realMax_z
               do 60 j = realMin_y, realMax_y
                  do 70 i = realMin_x, realMax_x
                     A(i,j,k) = S0 * B(i,j,k) &
                     + S1 * (B(i,j,k-1) + B(i,j,k+1) + B(i,j-1,k) + B(i,j+1,k) + B(i-1,j,k) + B(i+1,j,k))
 70               continue
 60            continue
 50         continue
         endif
         iter_flag = 1-iter_flag
 10   continue
      end subroutine naive_stencil
#endif

      end program naive
