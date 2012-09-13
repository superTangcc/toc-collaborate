
      program striad_benchmark
      implicit none

#ifndef DEBUG
#include "f90papi.h"
#endif

      integer log2_stanza_length, log2_max_stanza_length, log2_jump_length, log2_array_length
      integer stanza_length, num_stanzas, jump_length, array_length, array_padding

      parameter(array_padding = 30)
      parameter(log2_jump_length = 11)

#ifdef TWO_ARRAYS
      double precision, dimension(:), allocatable :: A, X
#else
      double precision, dimension(:), allocatable :: A, X, Y      
#endif

!     CHECKSUM
      double precision cs_total

!     TRIAL COUNTS AND TIMES
      integer num_trials, trial_num
      parameter (num_trials=5)
      double precision trial_times(num_trials)

!     FLUSHING THE CACHE
      integer flush_cache_size
      parameter (flush_cache_size=2**23)
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

      call papi_init()
#endif

      read *, log2_array_length

      jump_length = 2**log2_jump_length
      array_length = 2**log2_array_length

      allocate (A(array_length + array_padding))
      allocate (X(array_length + array_padding))
#ifndef TWO_ARRAYS
      allocate (Y(array_length + array_padding))
#endif

      log2_max_stanza_length = log2_array_length - 1

      call init_flush_cache()
      cs_total = 0.0;

      do 10 log2_stanza_length = LOG2_CACHE_LINE_SIZE_IN_DOUBLES, log2_max_stanza_length
         stanza_length = 2**log2_stanza_length
         call striad_fixed_stanza_length()
 10   continue

      print "(/, a, f7.2)", "checksum = ", cs_total
      call fc_checksum()

      contains

!     ********* SUBROUTINES ***********************

      subroutine init_grids()
      integer i
      
      do 10 i = 1, array_length
         A(i) = 0.0;
         X(i) = 2.0;
#ifndef TWO_ARRAYS
         Y(i) = 0.5;
#endif
 10   continue
      end subroutine init_grids

#ifndef DEBUG
      subroutine papi_init()
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
      end subroutine papi_init
#endif

      subroutine init_flush_cache()
      integer i

      do 10 i = 1, flush_cache_size
         FC(i) = 0.0
 10   continue
      end subroutine init_flush_cache

      subroutine flush_cache()
      integer i

      do 10 i = 1, flush_cache_size
         FC(i) = FC(i) + 1.0;
 10   continue
      end subroutine flush_cache

      subroutine fc_checksum()
      double precision cs
      integer i

      do 10 i = 1, flush_cache_size
         cs = cs + FC(i)
 10   continue

      cs = cs / flush_cache_size
      print "(a, f7.2)", "flush cache checksum = ", cs
      end subroutine fc_checksum

      function checksum()  result(cs_temp)
      double precision cs_temp
      integer i

      cs_temp = 0.0

      do 10 i = 1, array_length
         cs_temp = cs_temp + A(i)
 10   continue

      end function checksum

      subroutine striad()
      integer i, j
      integer idx_start, idx_end
      double precision S0
#ifdef TWO_ARRAYS
      parameter(S0=0.5)
#else
      parameter(S0=0.25)
#endif

      idx_start = 1
      idx_end = stanza_length
      
      do 10 i = 1, num_stanzas
         do 20 j = idx_start, idx_end
#ifdef TWO_ARRAYS
            A(j) = S0 * X(j)
#else
            A(j) = S0 * X(j) + Y(j)
#endif
 20      continue
         
         idx_start = idx_end + jump_length + 1
         idx_end = idx_start + stanza_length - 1
 10   continue
      end subroutine striad
      
      subroutine striad_fixed_stanza_length()
      num_stanzas = int(array_length / (stanza_length + jump_length))

#ifdef TWO_ARRAYS
      print "(/, a)", "Fortran STriad Benchmark with two arrays"
#else
      print "(/, a)", "Fortran STriad Benchmark with three arrays"
#endif
      print "(a, /, i8)", "array length = ", array_length
      print "(a, /, i8)", "jump length = ", jump_length
      print "(a, /, i8)", "stanza length = ", stanza_length
      print "(a, /, i8)", "num stanzas = ", num_stanzas
#ifndef DEBUG
      print "(a, /, i8)", "num sets = ", num_available_events
      print "(a)", " "
#endif

#ifndef DEBUG
      do 10 desired_event_num = 1, num_desired_events
         if (available_events(desired_event_num).eqv..true.) then
            do 20 trial_num = 1, num_trials
               call init_grids()
               call flush_cache()
               call PAPIF_start_counters(desired_events(desired_event_num), 1, check)
#endif
               call striad()
#ifndef DEBUG
               call PAPIF_stop_counters(counter_values(trial_num), 1, check)
 20         continue
            call PAPIF_event_code_to_name(desired_events(desired_event_num), event_name, check)
            print "(a12, a)", event_name, " = "
            print "(5(i11, a))", counter_values(1), ", ", counter_values(2), ", ", counter_values(3), ", ", counter_values(4), ", ", counter_values(5), ", "
         endif
 10   continue
#endif
      cs_total = cs_total + (checksum() / (stanza_length * num_stanzas))

      end subroutine striad_fixed_stanza_length

      end program striad_benchmark
