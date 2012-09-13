#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include "globals.h"
#include "../common/intrin.h"
#include "../common/prefetch.h"
#if defined(AFFINITY_ENABLED)
#if defined(__x86_64__)
#include "../common/affinity.sles.h"
#elif defined(__sparc) && defined(__GNUC__)
#include "../common/affinity.solaris.h"
#else
#include "../common/affinity.h"
#endif
#endif
#include "../common/barrier.h"
#include "../common/helper_functions.h"
#include "../common/flush_cache.h"
#include "grid.h"
#include "code_variant.h"
#include "function_headers.h"
#include "helmholtz_pthreads.h"
#if defined(GETTIMEOFDAY)
#include "../../timers/gettimeofday.h"
#endif
#if defined(CLOCK_GETTIME)
#include "../../timers/clock_gettime.h"
#endif
#include "../../timers/time_pthreads.h"
#if defined(CYCLE_TIME)
#include "../../timers/cycle_time.c"
#endif
#if defined(GETTIMEOFDAY)
#include "../../timers/gettimeofday.c"
#endif
#if defined(CLOCK_GETTIME)
#include "../../timers/clock_gettime.c"
#endif
#if (!defined(DEBUG) && defined(PAPI_ENABLED))
#include "../../papi/papi_util_pthreads.c"
#endif
#if defined(AFFINITY_ENABLED)
#if defined(__x86_64__)
#include "../common/affinity.sles.c"
#elif defined(__sparc) && defined(__GNUC__)
#include "../common/affinity.solaris.c"
#else
#include "../common/affinity.c"
#endif
#endif
#include "../common/barrier.c"
#include "../common/helper_functions.c"
#include "../common/flush_cache.c"
#include "grid.c"
#include "function_table.c"
#include "code_variant.c"
#include "variables.c"
#include "functions.c"

void *pthreads_each(void *rank_ptr) {
  uint32_t rank;
#if defined(DEBUG)
  uint32_t g;
#endif

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  int num_sets;
  PAPI_event_set_wrapper_t* event_sets;

  papi_filter_events(desired_events, num_desired, &event_sets, &num_sets);
#endif

  rank = *((uint32_t *) rank_ptr);

#if defined(AFFINITY_ENABLED)
  Affinity_Bind_Thread(rank);
  Affinity_Bind_Memory(rank);
#endif

#if defined(DEBUG)
  init_grids(rank);
  barrier_wait(&my_barrier, rank);
  if (rank == 0) {
    for (g=0; g < numGrids; g++) {
      printf("\nGRID phi_grids[%u] BEFORE:", g);
      print_grid(phi_grids[g], nx_rhs+2, ny_rhs+2, nz_rhs+2);
      printf("\nGRID rhs_grids[%u] BEFORE:", g);
      print_grid(rhs_grids[g], nx_rhs, ny_rhs, nz_rhs);
      printf("\nGRID aCoef_grids[%u] BEFORE:", g);
      print_grid(aCoef_grids[g], nx_rhs, ny_rhs, nz_rhs);
      printf("\nGRID bCoef0_grids[%u] BEFORE:", g);
      print_grid(bCoef0_grids[g], nx_rhs+1, ny_rhs, nz_rhs);
      printf("\nGRID bCoef1_grids[%u] BEFORE:", g);
      print_grid(bCoef1_grids[g], nx_rhs, ny_rhs+1, nz_rhs);
      printf("\nGRID bCoef2_grids[%u] BEFORE:", g);
      print_grid(bCoef2_grids[g], nx_rhs, ny_rhs, nz_rhs+1);
      printf("\nGRID lambda_grids[%u] BEFORE:", g);
      print_grid(lambda_grids[g], nx_rhs, ny_rhs, nz_rhs);
    }
    printf("\n\n");
  }
  barrier_wait(&my_barrier, rank);
  helmholtz_per_thread[prefetch_index_type][prefetch_distance][rb_size](rank, 2.5, 5.0, 10.0, 0);
  if (rank == 0) {
    for (g=0; g < numGrids; g++) {
      printf("\nGRID phi_grids[%u] AFTER:", g);
      print_grid(phi_grids[g], nx_rhs+2, ny_rhs+2, nz_rhs+2);
      printf("\nGRID rhs_grids[%u] AFTER:", g);
      print_grid(rhs_grids[g], nx_rhs, ny_rhs, nz_rhs);
      printf("\nGRID aCoef_grids[%u] AFTER:", g);
      print_grid(aCoef_grids[g], nx_rhs, ny_rhs, nz_rhs);
      printf("\nGRID bCoef0_grids[%u] AFTER:", g);
      print_grid(bCoef0_grids[g], nx_rhs+1, ny_rhs, nz_rhs);
      printf("\nGRID bCoef1_grids[%u] AFTER:", g);
      print_grid(bCoef1_grids[g], nx_rhs, ny_rhs+1, nz_rhs);
      printf("\nGRID bCoef2_grids[%u] AFTER:", g);
      print_grid(bCoef2_grids[g], nx_rhs, ny_rhs, nz_rhs+1);
      printf("\nGRID lambda_grids[%u] AFTER:", g);
      print_grid(lambda_grids[g], nx_rhs, ny_rhs, nz_rhs);
    }
    printf("\n\n");
  }
  barrier_wait(&my_barrier, rank);
#else
#if defined(PAPI_ENABLED)
  int papi_setnum;

  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, helmholtz_per_thread[prefetch_index_type][prefetch_distance][rb_size](rank, 2.5, 5.0, 10.0, 0), results, NUM_TRIALS*(papi_setnum*numThreads+rank), NUM_TRIALS);
  }
  if (rank == 0) {
    print_papi_measurements(event_sets, results, num_sets, numThreads, NUM_TRIALS);
    printf("\n\n");
  }
#else
  TIMER_MAKE_MEASUREMENTS(helmholtz_per_thread[prefetch_index_type][prefetch_distance][rb_size](rank, 2.5, 5.0, 10.0, 0), results, rank, NUM_TRIALS);
  if (rank == 0) {
    printf("TIME (IN SECONDS)\n");
#if defined(THREAD_PROFILING)
    uint32_t t;
    for (t=0; t < numThreads; t++) {
      printf("Thread %u:\n", t);
      print_timer_measurements(&results[t * NUM_TRIALS], NUM_TRIALS, median_counts_per_sec);
    }
#endif
    print_max_timer_measurements(results, numThreads, NUM_TRIALS, median_counts_per_sec);
    printf("\n\n");
  }
#endif
#endif
  pthread_exit((void*) 0);
}

int main(int argc, char *argv[]) {
  pthread_t *threads;
  pthread_attr_t attr;
  uint32_t **ranks;
  void *status;

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  int num_sets;
  PAPI_event_set_wrapper_t* event_sets;
#endif
  int rc;
  int32_t t;

  printf("Variable coefficient Helmholtz GSRB solver\n");

  init_flush_cache_array();
  malloc_grids(argv);
  print_grid_parameters();
  select_code_variant(argv);
  print_code_variant_parameters();

  threads = (pthread_t *) malloc(numThreads * sizeof(pthread_t));
  ranks = (uint32_t **) malloc(numThreads * sizeof(int32_t *));

#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
  papi_init(desired_events, num_desired, &event_sets, &num_sets);

  // initialize threaded PAPI
  if (PAPI_thread_init((unsigned long (*)(void)) (pthread_self)) != PAPI_OK) {
    printf("Error with PAPI_thread_init().\n");
    exit(EXIT_FAILURE);
  }

  results = (double *) malloc(num_sets * numThreads * NUM_TRIALS * sizeof(double));
  if (results==NULL) {
    printf("Error on array results malloc.\n");
    exit(EXIT_FAILURE);
  }
#else
  results = (double *) malloc(numThreads * NUM_TRIALS * sizeof(double));
  if (results==NULL) {
    printf("Error on array results malloc.\n");
    exit(EXIT_FAILURE);
  }
#if defined(CYCLE_TIME)
  // calculate clock rate
  GET_CLOCK_RATE(results, NUM_TRIALS);
  median_counts_per_sec = find_median(results, NUM_TRIALS);
  //printf("Median ticks per second = %e\n", median_counts_per_sec);

#else
  timer_init();
  median_counts_per_sec = 1.0;
#endif
#endif
#endif

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  barrier_init(&my_barrier, numThreads);
#if defined(AFFINITY_ENABLED)
  Affinity_Init();
#endif

  // run stencil tests
  for (t=0; t < numThreads; t++) {
    ranks[t] = (uint32_t *) malloc(sizeof(int32_t));
    *ranks[t] = t;
  }

  for (t=1; t < numThreads; t++) {
#if defined(DEBUG)
    printf("Creating thread %d\n", t);
#endif
    rc = pthread_create(&threads[t], &attr, pthreads_each, (void *) ranks[t]);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }
  pthreads_each((void *) ranks[0]);

  // join the other threads
  for (t=1; t < numThreads; t++) {
    pthread_join(threads[t], &status);
  }

  //printf("\nFinal interior values: A[%d, %d, %d] = %4.2e, B[%d, %d, %d] = %4.2e\n\n", nx/2, ny/2, nz/2, A[Index3D(nx/2, ny/2, nz/2)], nx/2, ny/2, nz/2, B[Index3D(nx/2, ny/2, nz/2)]);

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  papi_cleanup(event_sets, num_sets);
#endif
  pthread_attr_destroy(&attr);
  pthread_exit(NULL);
  barrier_destroy(&my_barrier);
  free_grids();

  return EXIT_SUCCESS;
}
