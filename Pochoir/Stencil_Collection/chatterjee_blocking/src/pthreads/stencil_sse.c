#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "globals.h"
#if (defined(__ppc__) || defined(__powerpc__) || defined(__PPC__) || defined(__PPC))
  #define PREFETCH_FOR_REUSE(address)
  #define PREFETCH_FOR_ONE_READ(address)
  #define PREFETCH_FOR_ONE_WRITE(address)
#elif defined(__x86_64__)
  #include <xmmintrin.h>
  #include <emmintrin.h>
  #include <pmmintrin.h>
  #define PREFETCH_FOR_REUSE(address)     _mm_prefetch((address), _MM_HINT_T0 )
  #define PREFETCH_FOR_ONE_READ(address)  _mm_prefetch((address), _MM_HINT_NTA)
  #define PREFETCH_FOR_ONE_WRITE(address) /* N/A, use stream_pd */
#elif defined(__ia64__)
  #include <ia64intrin.h>
  #define PREFETCH_FOR_REUSE(address)     __lfetch(lfetch.nt1,(address))
  #define PREFETCH_FOR_ONE_READ(address)  __lfetch(lfetch.nta,(address))
  #define PREFETCH_FOR_ONE_WRITE(address) __lfetch(lfetch.nta,(address))
#elif (defined(__sparc) || defined(__sparcv9))
  #define PREFETCH_FOR_REUSE(address)     __sparc_prefetch_read_many_intrinsic((address))
  #define PREFETCH_FOR_ONE_READ(address)  __sparc_prefetch_read_once_intrinsic((address))
  #define PREFETCH_FOR_ONE_WRITE(address) __sparc_prefetch_write_once_intrinsic((address))
#endif
#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
#include "../../papi/papi_util_pthreads.c"
#else
#include <unistd.h>
#include "../../cycle_time/cycle_time_pthreads.h"
#include "../../cycle_time/cycle_time.c"
#endif
#endif
#include "barrier.c"
#if defined(AFFINITY_ENABLED)
#include "../common/affinity.sched.c"
#endif
#include "../common/helper_functions.c"
#include "grid.c"
#include "../common/flush_cache.c"

#if !defined(DEBUG)
double *results;
#if defined(PAPI_ENABLED)
int num_desired = 9;
int desired_events[] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCA, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS};
#endif
#endif

#define PREFETCH_PENCILS
#define PREFETCH_DIST 64
#define STREAM

barrier_t my_barrier;
int32_t num_threads;

int32_t cacheBlock_y;

double median_counts_per_sec;

void stencil_per_thread(int32_t *threadBlockMin, int32_t *threadBlockMax, int32_t task_id) {
  double * __restrict__ temp_ptr;
  int32_t cacheBlockMin_y, cacheBlockMax_y, cb_j;
  int32_t i, j, k, t;
  
  double * __restrict__ Read_start = A;
  double * __restrict__ Write_start = B;

  const int32_t threadBlockMin_x = threadBlockMin[0];
  const int32_t threadBlockMin_y = threadBlockMin[1];
  const int32_t threadBlockMin_z = threadBlockMin[2];
  const int32_t threadBlockMax_x = threadBlockMax[0];
  const int32_t threadBlockMax_y = threadBlockMax[1];
  const int32_t threadBlockMax_z = threadBlockMax[2];

  const int32_t plane_size = ny * nz;

  double a_const = alpha;
  double b_const = beta;

  __m128d a_constQW = _mm_load1_pd(&(a_const));
  __m128d b_constQW = _mm_load1_pd(&(b_const));

  for (t=0; t < numIter; t++) {
    double * ReadXM = Read_start - plane_size;
    double * ReadXP = Read_start + plane_size;
    double * ReadYM = Read_start - nz;
    double * ReadYP = Read_start + nz;
    for (cb_j=0; cb_j < numCacheBlocks_y; cb_j++) {
      cacheBlockMin_y = threadBlockMin_y + cb_j * numCacheBlockCells_y;
      cacheBlockMax_y = cacheBlockMin_y + numCacheBlockCells_y;
      for (i=threadBlockMin_x; i < threadBlockMax_x; i++) {
	for (j=cacheBlockMin_y; j < cacheBlockMax_y; j++) {
	  // THIS NEEDS TO BE FIXED (PADDING??)
	  uint64_t ijk = Index3D(i,j,threadBlockMin_z-1);
	  for (k=threadBlockMin_z; k < threadBlockMax_z; k+=8) {
#if defined(PREFETCH_RB)
	    PREFETCH_FOR_REUSE(&(ReadXP[ijk+6])+PREFETCH_DIST);
#elif defined(PREFETCH_PLANES)
	    PREFETCH_FOR_REUSE(&(ReadXP[ijk+6])+PREFETCH_DIST);
	    PREFETCH_FOR_REUSE(&(ReadYP[ijk+6])+PREFETCH_DIST));
	    PREFETCH_FOR_REUSE(&(ReadXM[ijk+6])+PREFETCH_DIST));
#elif defined(PREFETCH_PENCILS)
	    PREFETCH_FOR_REUSE(&(ReadXP[ijk+6])+PREFETCH_DIST);
	    PREFETCH_FOR_REUSE(&(ReadYP[ijk+6])+PREFETCH_DIST));
	    PREFETCH_FOR_REUSE(&(Read_start[ijk+6])+PREFETCH_DIST));
	    PREFETCH_FOR_REUSE(&(ReadYM[ijk+6])+PREFETCH_DIST));
	    PREFETCH_FOR_REUSE(&(ReadXM[ijk+6])+PREFETCH_DIST));
#endif
	    PREFETCH_FOR_ONE_WRITE(&(Write_start[ijk+6])+PREFETCH_DIST));
	    
	    __m128d Read_0 = _mm_loadu_pd(&(Read_start[ijk-1]));
	    __m128d Read12 = _mm_loadu_pd(&(Read_start[ijk+1]));
	    __m128d Read34 = _mm_loadu_pd(&(Read_start[ijk+3]));
	    __m128d Read56 = _mm_loadu_pd(&(Read_start[ijk+5]));
	    __m128d Read7a = _mm_loadu_pd(&(Read_start[ijk+7]));
	    
	    __m128d Write01 = Read_0;
	    __m128d Write23 = Read12;
	    __m128d Write45 = Read34;
	    __m128d Write67 = Read56;
	    
	    Write01 = _mm_add_pd(Write01, Read12);
	    Write23 = _mm_add_pd(Write23, Read34);
	    Write45 = _mm_add_pd(Write45, Read56);
	    Write67 = _mm_add_pd(Write67, Read7a);
	    
	    Write01 = _mm_add_pd(Write01, *(__m128d *)(&(ReadXM[ijk  ])));
	    Write23 = _mm_add_pd(Write23, *(__m128d *)(&(ReadXM[ijk+2])));
	    Write45 = _mm_add_pd(Write45, *(__m128d *)(&(ReadXM[ijk+4])));
	    Write67 = _mm_add_pd(Write67, *(__m128d *)(&(ReadXM[ijk+6])));
	    
	    Write01 = _mm_add_pd(Write01, *(__m128d *)(&(ReadYM[ijk  ])));
	    Write23 = _mm_add_pd(Write23, *(__m128d *)(&(ReadYM[ijk+2])));
	    Write45 = _mm_add_pd(Write45, *(__m128d *)(&(ReadYM[ijk+4])));
	    Write67 = _mm_add_pd(Write67, *(__m128d *)(&(ReadYM[ijk+6])));
	    
	    Write01 = _mm_add_pd(Write01, *(__m128d *)(&(ReadYP[ijk  ])));
	    Write23 = _mm_add_pd(Write23, *(__m128d *)(&(ReadYP[ijk+2])));
	    Write45 = _mm_add_pd(Write45, *(__m128d *)(&(ReadYP[ijk+4])));
	    Write67 = _mm_add_pd(Write67, *(__m128d *)(&(ReadYP[ijk+6])));
	    
	    Write01 = _mm_add_pd(Write01, *(__m128d *)(&(ReadXP[ijk  ])));
	    Write23 = _mm_add_pd(Write23, *(__m128d *)(&(ReadXP[ijk+2])));
	    Write45 = _mm_add_pd(Write45, *(__m128d *)(&(ReadXP[ijk+4])));
	    Write67 = _mm_add_pd(Write67, *(__m128d *)(&(ReadXP[ijk+6])));
	    
	    Write01 = _mm_mul_pd(Write01, b_constQW);
	    Write23 = _mm_mul_pd(Write23, b_constQW);
	    Write45 = _mm_mul_pd(Write45, b_constQW);
	    Write67 = _mm_mul_pd(Write67, b_constQW);
	    
	    Write01 = _mm_add_pd(Write01, _mm_mul_pd(a_constQW,*(__m128d *)(&(Read_start[ijk  ]))));
	    Write23 = _mm_add_pd(Write23, _mm_mul_pd(a_constQW,*(__m128d *)(&(Read_start[ijk+2]))));
	    Write45 = _mm_add_pd(Write45, _mm_mul_pd(a_constQW,*(__m128d *)(&(Read_start[ijk+4]))));
	    Write67 = _mm_add_pd(Write67, _mm_mul_pd(a_constQW,*(__m128d *)(&(Read_start[ijk+6]))));

#ifndef STREAM
	    _mm_store_pd(&(Write_start[ijk  ]), Write01);
	    _mm_store_pd(&(Write_start[ijk+2]), Write23);
	    _mm_store_pd(&(Write_start[ijk+4]), Write45);
	    _mm_store_pd(&(Write_start[ijk+6]), Write67);

#else
	    _mm_stream_pd(&(Write_start[ijk  ]), Write01);
	    _mm_stream_pd(&(Write_start[ijk+2]), Write23);
	    _mm_stream_pd(&(Write_start[ijk+4]), Write45);
	    _mm_stream_pd(&(Write_start[ijk+6]), Write67);
#endif

	    ijk += 8;
	  }
	}
      }
    }
    temp_ptr = Read_start;
    Read_start = Write_start;
    Write_start = temp_ptr;

    // barrier after each iteration (except the last iteration)
    if (t < (numIter-1)) {
      barrier_wait(&my_barrier, task_id);
    }
  }
}

void *naive_per_thread(void *thread_id) {
  int32_t threadBlock_id, task_id;
  int32_t threadBlock[3];
  int32_t threadBlockMin[3];
  int32_t threadBlockMax[3];

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  int num_sets;
  PAPI_event_set_wrapper_t* event_sets;

  papi_filter_events(desired_events, num_desired, &event_sets, &num_sets);
#endif

  task_id = *((int32_t *) thread_id);

#if defined(AFFINITY_ENABLED)
  Affinity_Bind_Thread(task_id);
  Affinity_Bind_Memory(task_id);
#endif

  threadBlock_id = task_id;
  threadBlock[0] = threadBlock_id / (numThreadBlocks_y * numThreadBlocks_z);
  threadBlock_id = threadBlock_id - (threadBlock[0] * numThreadBlocks_y * numThreadBlocks_z);
  threadBlock[1] = threadBlock_id / numThreadBlocks_z;
  threadBlock[2] = threadBlock_id - (threadBlock[1] * numThreadBlocks_z);

  threadBlockMin[0] = threadBlock[0] * numThreadBlockCells_x + 1;
  threadBlockMax[0] = threadBlockMin[0] + numThreadBlockCells_x;
  threadBlockMin[1] = threadBlock[1] * numThreadBlockCells_y + 1;
  threadBlockMax[1] = threadBlockMin[1] + numThreadBlockCells_y;
  threadBlockMin[2] = threadBlock[2] * numThreadBlockCells_z + 1;
  threadBlockMax[2] = threadBlockMin[2] + numThreadBlockCells_z;

#if defined(DEBUG)
  printf("Thread %d: threadBlock = [%d, %d, %d]\n", task_id, threadBlock[0], threadBlock[1], threadBlock[2]);
  printf("Thread %d: threadBlockMin = [%d, %d, %d]\n", task_id, threadBlockMin[0], threadBlockMin[1], threadBlockMin[2]);
  printf("Thread %d: threadBlockMax = [%d, %d, %d]\n", task_id, threadBlockMax[0], threadBlockMax[1], threadBlockMax[2]);
#endif

#if defined(DEBUG)
  init_grids_per_thread(threadBlock, threadBlockMin, threadBlockMax);
  barrier_wait(&my_barrier, task_id);
  stencil_per_thread(threadBlockMin, threadBlockMax, task_id);
#else
#if defined(PAPI_ENABLED)
  int papi_setnum;
  
  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, stencil_per_thread(threadBlockMin, threadBlockMax, task_id), results, NUM_TRIALS*(papi_setnum*num_threads+task_id), NUM_TRIALS);
  }
#else
  TIMER_MAKE_MEASUREMENTS(stencil_per_thread(threadBlockMin, threadBlockMax, task_id), results, task_id, NUM_TRIALS);
#endif
#endif

  pthread_exit((void*) 0);
}

int main(int argc, char *argv[]) {
  pthread_t *threads;
  pthread_attr_t attr;
  int32_t **task_ids;
  void *status;

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  int num_sets;
  PAPI_event_set_wrapper_t* event_sets;
#endif
  int rc;
  int32_t t;

  printf("7-point stencil, no add, naive C code with non-periodic boundary conditions\n");

  // initialize arrays
  init_flush_cache_array();
  malloc_grids(argv);

  num_threads = numThreadBlocks_x * numThreadBlocks_y * numThreadBlocks_z;
#if defined(DEBUG)
  printf("num_threads = %d\n", num_threads);
#endif
  threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
  task_ids = (int32_t **) malloc(num_threads * sizeof(int32_t *));
  
#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
  papi_init(desired_events, num_desired, &event_sets, &num_sets);

  // initialize threaded papi
  if (PAPI_thread_init((unsigned long (*)(void)) (pthread_self)) != PAPI_OK) {
    printf("Error with PAPI_thread_init().\n");
    exit(1);
  }

  results = (double *) malloc(num_sets * num_threads * NUM_TRIALS * sizeof(double));
  if (results==NULL) {
      printf("Error on array results malloc.\n");
      exit(EXIT_FAILURE);
  }
#else
  results = (double *) malloc(num_threads * NUM_TRIALS * sizeof(double));
  if (results==NULL) {
      printf("Error on array results malloc.\n");
      exit(EXIT_FAILURE);
  }

  // calculate clock rate
  GET_CLOCK_RATE(results, NUM_TRIALS);
  median_counts_per_sec = find_median(results, NUM_TRIALS);
  printf("Median ticks per second = %e\n", median_counts_per_sec);
#endif
#endif
  
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  barrier_init(&my_barrier, num_threads);
#if defined(AFFINITY_ENABLED)
  Affinity_Init();
#endif

  // run stencil tests
  for (t=0; t < num_threads; t++) {
    task_ids[t] = (int32_t *) malloc(sizeof(int32_t));
    *task_ids[t] = t;
#if defined(DEBUG)
    printf("Creating thread %d\n", t);
#endif
    rc = pthread_create(&threads[t], &attr, naive_per_thread, (void *) task_ids[t]);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }

  // wait on other threads
  for (t=0; t < num_threads; t++) {
    pthread_join(threads[t], &status);
  }

#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
  print_papi_measurements(event_sets, results, num_sets, num_threads, NUM_TRIALS);
  papi_cleanup(event_sets, num_sets);
#else
  for (t=0; t < num_threads; t++) {
    printf("t%d: ", t);
    print_timer_measurements(&results[t * NUM_TRIALS], NUM_TRIALS, median_counts_per_sec);
  }
#endif
#endif

#if defined(DEBUG)
  printf("\nGRID A AFTER:");
  print_grid(A);
  printf("\nGRID B AFTER:");
  print_grid(B);
#endif

  printf("\nFinal interior values: A[%d, %d, %d] = %lf, B[%d, %d, %d] = %lf\n", nx/2, ny/2, nz/2, A[Index3D(nx/2, ny/2, nz/2)], nx/2, ny/2, nz/2, B[Index3D(nx/2, ny/2, nz/2)]);
  flush_cache_checksum();
  pthread_attr_destroy(&attr);
  pthread_exit(NULL);
  barrier_destroy(&my_barrier);
  free_grids();
  
  return EXIT_SUCCESS;
}
