#!/bin/bash
#
# To build:
#
#   Modify the following flags as appropriate for your platform:
#     CC           :  Your C compiler
#     COPTFLAGS    :  Compiler optimization flags
#     CFLAGS       :  Any optional non-optimization related C flags
#     LDFLAGS      :  Linker flags
#
#     CFLAGS_TIMER :  Indicates timer to use and timing options
#                     (see src/my_util.c)
#

# -----------------------------------------------------------------------
include Make.nehalem
# -----------------------------------------------------------------------

SRC_DIR = ../src
SERIAL_DIR = ../src/serial
STREAM_DIR = ../src/Stream
OPTIMIZED_STREAM_DIR = ../src/optimized_stream
PTHREADS_DIR = ../src/pthreads
HELMHOLTZ_DIR = ../src/gsrb_helmholtz_vc_3d
PAPI_DIR = ../papi

all:		clean $(OPTIMIZED_STREAM_DIR)/stream_pthreads_$(CC_NAME)_c

$(SERIAL_DIR)/stanza_triad_c:	$(SERIAL_DIR)/stanza_triad.c
				$(CC) $(C_FLAGS) $? -o $@

$(STREAM_DIR)/stream_$(CC_NAME)_c:	$(STREAM_DIR)/stream.c
					$(CC) $(C_FLAGS) $(OPEN_MP_FLAGS) $? -o $@

$(OPTIMIZED_STREAM_DIR)/stream_pthreads_$(CC_NAME)_c:	$(OPTIMIZED_STREAM_DIR)/stream_pthreads.c
						$(CC) $(C_FLAGS) $(PAPI_ENABLED_FLAG) $(PAPI_INC_FLAGS) $? $(PTHREAD_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(HELMHOLTZ_DIR)/helmholtz_pthreads_$(CC_NAME)_c:	$(HELMHOLTZ_DIR)/helmholtz_pthreads.c
						$(CC) $(C_FLAGS) $(PAPI_ENABLED_FLAG) $(PAPI_INC_FLAGS) $? $(PTHREAD_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(PTHREADS_DIR)/stencil_pthreads_$(CC_NAME)_c:	$(PTHREADS_DIR)/stencil_pthreads.c
						$(CC) $(C_FLAGS) $(PAPI_ENABLED_FLAG) $(PAPI_INC_FLAGS) $? $(PTHREAD_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(PTHREADS_DIR)/stencil_sse_$(CC_NAME)_c:	$(PTHREADS_DIR)/stencil_sse.c
						$(CC) $(C_FLAGS) $(PAPI_ENABLED_FLAG) $(PAPI_INC_FLAGS) $? $(PTHREAD_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(PTHREADS_DIR)/cq_$(CC_NAME)_c:	$(PTHREADS_DIR)/circular_queue.c
					$(CC) $(C_FLAGS) $(PAPI_FLAG) $(PAPI_INC_FLAGS) $? $(PTHREAD_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(PTHREADS_DIR)/ts_$(CC_NAME)_c:	$(PTHREADS_DIR)/time_skewing.c
					$(CC) $(C_FLAGS) $(PAPI_FLAG) $(PAPI_INC_FLAGS) $? $(PTHREAD_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(SERIAL_DIR)/serial_$(CC_NAME)_c:	$(SERIAL_DIR)/serial_code.c
					$(CC) $(C_FLAGS) $(PAPI_INC_FLAGS) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(SERIAL_DIR)/cq_$(CC_NAME)_c:	$(SERIAL_DIR)/circular_queue.c
				$(CC) $(C_FLAGS) $(PAPI_INC_FLAGS) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(SERIAL_DIR)/ts_$(CC_NAME)_c:	$(SERIAL_DIR)/time_skewing.c
				$(CC) $(C_FLAGS) $(PAPI_INC_FLAGS) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

serial:		$(SERIAL_DIR)/serial_$(CC_NAME)_c

c_code:		$(SRC_DIR)/striad_c $(SRC_DIR)/stanza_c $(SRC_DIR)/naive_c $(SRC_DIR)/naive_prefetch_c $(SRC_DIR)/naive_pthreads_c $(SRC_DIR)/ts_c

F_code:		$(SRC_DIR)/striad_F naive_F ts_F

$(SRC_DIR)/naive_caf_$(CC_NAME)_c:	$(PAPI_UTIL_FLAG) $(SRC_DIR)/naive_caf.c
					$(CC) $(C_FLAGS) $(PAPI_ENABLED_FLAG) $(PAPI_INC_FLAGS) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

periodic:	$(SRC_DIR)/periodic.c $(SRC_DIR)/periodic.h
		$(CC) $(FULL_CFLAGS) -o $(SRC_DIR)/periodic.o -c $(SRC_DIR)/periodic.c

$(SRC_DIR)/naive_1D_loop_unrolling_$(CC_NAME)_c:	$(PAPI_UTIL_FLAG) $(SRC_DIR)/naive_1D_loop_unrolling.c
							$(CC) $(C_OPT_FLAGS) $(PAPI_FLAG) $(PAPI_INC_FLAGS) -D$(ARCH) -D$(COMP) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

proc_f:		$(SRC_DIR)/proc_benchmark.F
ifneq ($(PLATFORM), bassi)
		$(FC90) $(F_OPT_FLAGS) -o $(SRC_DIR)/proc_f90 $(SRC_DIR)/proc_benchmark.F $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS)
else
		$(FC77) $(F_OPT_FLAGS) -o $(SRC_DIR)/proc_f77 $(SRC_DIR)/proc_benchmark.F $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS)
		$(FC90) $(F_OPT_FLAGS) -qsuffix=cpp=F -o $(SRC_DIR)/proc_f90 $(SRC_DIR)/proc_benchmark.F $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS)
endif

ts_F:		$(SRC_DIR)/time_skewing.F
ifneq ($(PLATFORM), bassi)
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DSTATIC_ALLOC $(SRC_DIR)/time_skewing.F $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $(SRC_DIR)/ts_static_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DDYNAMIC_ALLOC $(SRC_DIR)/time_skewing.F $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $(SRC_DIR)/ts_dynamic_F
else
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DSTATIC_ALLOC $(SRC_DIR)/time_skewing.F -o $(SRC_DIR)/ts_static_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DDYNAMIC_ALLOC $(SRC_DIR)/time_skewing.F -o $(SRC_DIR)/ts_dynamic_F
endif

$(SRC_DIR)/comp_bound_c:	$(PAPI_UTIL_FLAG) $(SRC_DIR)/flush_cache.o $(SRC_DIR)/comp_bound_grid.o $(SRC_DIR)/comp_bound_naive.o
				$(CC) $(C_OPT_FLAGS) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@

$(SRC_DIR)/comp_bound_naive.o:	$(SRC_DIR)/naive.c
				$(CC) $(C_OPT_FLAGS) $(PAPI_FLAG) $(PAPI_INC_FLAGS) -c $? -o $@

$(SRC_DIR)/bench_sse_c:		$(SRC_DIR)/bench.sse.c
					$(CC) $(C_OPT_FLAGS) $? -o $@

naive_F:	$(SRC_DIR)/naive.F
ifneq ($(PLATFORM), bassi)
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DSTATIC_ALLOC -DUNALIASED $(SRC_DIR)/naive.F $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $(SRC_DIR)/naive_static_unaliased_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DSTATIC_ALLOC -DALIASED $(SRC_DIR)/naive.F $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $(SRC_DIR)/naive_static_aliased_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DDYNAMIC_ALLOC -DUNALIASED $(SRC_DIR)/naive.F $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $(SRC_DIR)/naive_dynamic_unaliased_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DDYNAMIC_ALLOC -DALIASED $(SRC_DIR)/naive.F $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $(SRC_DIR)/naive_dynamic_aliased_F
else
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DSTATIC_ALLOC,-DUNALIASED $(SRC_DIR)/naive.F -o $(SRC_DIR)/naive_static_unaliased_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DSTATIC_ALLOC,-DALIASED $(SRC_DIR)/naive.F -o $(SRC_DIR)/naive_static_aliased_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DDYNAMIC_ALLOC,-DUNALIASED $(SRC_DIR)/naive.F -o $(SRC_DIR)/naive_dynamic_unaliased_F
		$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DDYNAMIC_ALLOC,-DALIASED $(SRC_DIR)/naive.F -o $(SRC_DIR)/naive_dynamic_aliased_F
endif

$(SRC_DIR)/comp_bound_grid.o:	$(SRC_DIR)/grid.c
				$(CC) $(C_OPT_FLAGS) -DCOMPUTATION_BOUND -c $? -o $@

$(SRC_DIR)/grid.o:	$(SRC_DIR)/grid.c
			$(CC) $(C_OPT_FLAGS) -c $? -o $@

$(SRC_DIR)/stanza_F:	$(SRC_DIR)/striad_benchmark.F
ifneq ($(PLATFORM), bassi)
			$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DTWO_ARRAYS -DLOG2_CACHE_LINE_SIZE_IN_DOUBLES=$(LOG2_CACHE_LINE_SIZE_IN_DOUBLES) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@
else
			$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DLOG2_CACHE_LINE_SIZE_IN_DOUBLES=$(LOG2_CACHE_LINE_SIZE_IN_DOUBLES),-DTWO_ARRAYS $? -o $@
endif

$(SRC_DIR)/striad_F:	$(SRC_DIR)/striad_benchmark.F
ifneq ($(PLATFORM), bassi)
			$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) -DLOG2_CACHE_LINE_SIZE_IN_DOUBLES=$(LOG2_CACHE_LINE_SIZE_IN_DOUBLES) $? $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -o $@
else
			$(FC90) $(F_OPT_FLAGS) $(PAPI_INC_FLAGS) $(PAPI_LINK_FLAGS) $(TIMER_FLAGS) -qsuffix=cpp=F -WF,-DLOG2_CACHE_LINE_SIZE_IN_DOUBLES=$(LOG2_CACHE_LINE_SIZE_IN_DOUBLES) $? -o $@
endif

$(SRC_DIR)/flush_cache.o:	$(SRC_DIR)/flush_cache.c
				$(CC) $(C_OPT_FLAGS) -c $? -o $@

clean:
		rm -f $(PAPI_DIR)/*~ $(PAPI_DIR)/*.o $(SERIAL_DIR)/*_c $(STREAM_DIR)/*_c $(PTHREADS_DIR)/*_c $(HELMHOLTZ_DIR)/*_c $(OPTIMIZED_STREAM_DIR)/*_c
