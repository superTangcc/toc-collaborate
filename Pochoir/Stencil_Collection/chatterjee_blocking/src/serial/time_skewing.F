
      program time_skewing
      implicit none

#ifndef DEBUG
#include "f90papi.h"
#endif

      integer nx, ny, nz, num_iter
      integer nreals_x, nreals_y, nreals_z
      integer realMin_x, realMin_y, realMin_z
      integer realMax_x, realMax_y, realMax_z
      integer numBlockCells_x, numBlockCells_y, numBlockCells_z
      integer numBlocks_x, numBlocks_y, numBlocks_z
      integer ghostCellDepth
      parameter (ghostCellDepth=1)

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
      read *, num_iter, numBlockCells_x, numBlockCells_y, numBlockCells_z
#endif
#ifdef DYNAMIC_ALLOC
      read *, num_iter, nreals_x, nreals_y, nreals_z, numBlockCells_x, numBlockCells_y, numBlockCells_z
#endif
      nx = nreals_x + 2*ghostCellDepth
      ny = nreals_y + 2*ghostCellDepth
      nz = nreals_z + 2*ghostCellDepth
#ifdef DYNAMIC_ALLOC
      allocate (A(nx, ny, nz))
      allocate (B(nx, ny, nz))
#endif

      print "(/, a, a)", "7-point stencil, no add, time-skewing Fortran code with non-periodic boundary conditions"
      print "(a, /, i8, a)", "num_iter = ", num_iter, ", "
      print "(a, /, i4, a, i4, a, i4, a)", "full grid size =", nx, ", ", ny, ", ", nz, ", "
      print "(a, /, i4, a, i4, a, i4, a)", "real grid size =", nreals_x, ", ", nreals_y, ", ", nreals_z, ", "
      print "(a, /, i4, a, i4, a, i4, a)", "cache block size =", numBlockCells_x, ", ", numBlockCells_y,", ", numBlockCells_z, ", "
#ifndef DEBUG
      print "(a, /, i1, a, /)", "num_sets = ", num_available_events, ", "
#endif

      call init_flush_cache_array()

      numBlocks_x = nreals_x / numBlockCells_x
      numBlocks_y = nreals_y / numBlockCells_y
      numBlocks_z = nreals_z / numBlockCells_z

      realMin_x = ghostCellDepth + 1
      realMin_y = ghostCellDepth + 1
      realMin_z = ghostCellDepth + 1
      realMax_x = realMin_x + nreals_x - 1
      realMax_y = realMin_y + nreals_y - 1
      realMax_z = realMin_z + nreals_z - 1

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
               call ts_stencil()
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

!     ** initialized full arrays (including ghost cells) **
      do 10 k = 1, nz
         do 20 j = 1, ny
            do 30 i = 1, nx
               A(i,j,k) = 0;
               B(i,j,k) = 0;
 30         continue
 20      continue
 10   continue

!     ** initialized non-ghost cells **
      do 40 k = realMin_z, realMax_z
         do 50 j = realMin_y, realMax_y
            do 60 i = realMin_x, realMax_x
               A(i,j,k) = 1;
 60         continue
 50      continue
 40   continue
      end subroutine init_grids

      subroutine single_block_stencil(i_block, j_block, k_block, &
      neg_x_slope, pos_x_slope, neg_y_slope, &
      pos_y_slope, neg_z_slope, pos_z_slope)
      integer i, j, k, t
      integer i_block, j_block, k_block
      integer neg_x_slope, neg_y_slope, neg_z_slope
      integer pos_x_slope, pos_y_slope, pos_z_slope
      integer x_initBlockMin, y_initBlockMin, z_initBlockMin
      integer x_initBlockMax, y_initBlockMax, z_initBlockMax
      integer x_min, y_min, z_min
      integer x_max, y_max, z_max
      double precision S0, S1
      parameter(S0 = 4, S1 = 2)
      integer iter_flag

      x_initBlockMin = i_block * numBlockCells_x + 2
      y_initBlockMin = j_block * numBlockCells_y + 2
      z_initBlockMin = k_block * numBlockCells_z + 2

      x_initBlockMax = x_initBlockMin + numBlockCells_x - 1
      y_initBlockMax = y_initBlockMin + numBlockCells_y - 1
      z_initBlockMax = z_initBlockMin + numBlockCells_z - 1

      iter_flag = 0

      do 10 t = 0, (num_iter-1)
         x_min = x_initBlockMin - t * neg_x_slope;
         y_min = y_initBlockMin - t * neg_y_slope;
         z_min = z_initBlockMin - t * neg_z_slope;

         x_max = x_initBlockMax + t * pos_x_slope;
         y_max = y_initBlockMax + t * pos_y_slope;
         z_max = z_initBlockMax + t * pos_z_slope;

         if (iter_flag.eq.0) then
            do 20 k = z_min, z_max
               do 30 j = y_min, y_max
                  do 40 i = x_min, x_max
                     B(i,j,k) = S0 * A(i,j,k) &
                     + S1 * (A(i,j,k-1) + A(i,j,k+1) + A(i,j-1,k) + A(i,j+1,k) + A(i-1,j,k) + A(i+1,j,k))
 40               continue
 30            continue
 20         continue
         else
            do 50 k = z_min, z_max
               do 60 j = y_min, y_max
                  do 70 i = x_min, x_max
                     A(i,j,k) = S0 * B(i,j,k) &
                     + S1 * (B(i,j,k-1) + B(i,j,k+1) + B(i,j-1,k) + B(i,j+1,k) + B(i-1,j,k) + B(i+1,j,k))
 70               continue
 60            continue
 50         continue
         end if
         iter_flag = 1-iter_flag
 10   continue
      end subroutine single_block_stencil

      subroutine ts_stencil()
      integer i_block, j_block, k_block
      integer neg_x_slope, neg_y_slope, neg_z_slope
      integer pos_x_slope, pos_y_slope, pos_z_slope
      
      do 10 k_block = 0, (numBlocks_z-1)
         neg_z_slope = 1
         pos_z_slope = -1
         
         if (k_block.eq.0) neg_z_slope = 0
         if (k_block.eq.(numBlocks_z-1)) pos_z_slope = 0
         
         do 20 j_block = 0, (numBlocks_y-1)
            neg_y_slope = 1
            pos_y_slope = -1

            if (j_block.eq.0) neg_y_slope = 0
            if (j_block.eq.(numBlocks_y-1)) pos_y_slope = 0

            do 30 i_block = 0, (numBlocks_x-1)
               neg_x_slope = 1
               pos_x_slope = -1
               
               if (i_block.eq.0) neg_x_slope = 0
               if (i_block.eq.(numBlocks_x-1)) pos_x_slope = 0
               
               call single_block_stencil(i_block, j_block, k_block, &
               neg_x_slope, pos_x_slope, neg_y_slope, &
               pos_y_slope, neg_z_slope, pos_z_slope)
 30         continue
 20      continue
 10   continue
      end subroutine ts_stencil

      end program time_skewing
