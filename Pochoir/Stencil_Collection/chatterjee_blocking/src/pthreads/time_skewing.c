/*  Time skewing stencil code
 *  Kaushik Datta (kdatta@cs.berkeley.edu)
 *  University of California Berkeley
 *
 *  This code implements the time skewing algorithm for stencil codes.  The
 *  cache blocks need to be traversed in a specific order in order for the
 *  algorithm to work properly.
 *
 *  NOTE: The number of iterations can only be up to one greater than the
 *  smallest cache block dimension.  If you wish to do more iterations, there
 *  are two options:
 *    1.  Make the smallest cache block dimension larger.
 *    2.  Split the number of iterations into smaller runs where each run
 *        conforms to the above rule.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "globals.h"
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
#include "grid.c"
#include "../common/flush_cache.c"
#if !defined(DEBUG)
double *results;
#if defined(PAPI_ENABLED)
int num_desired = 9;
int desired_events[] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCA, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS};
#endif
#endif

barrier_t my_barrier;
int32_t num_threads;

double median_counts_per_sec;

double *queuePlanes, *queuePlane0, *queuePlane1, *queuePlane2;
int32_t *queuePlanesIndices;

/* This method traverses all of the cache blocks in a specific order to preserve
   dependencies.  For each cache block, it performs (possibly) several iterations while
   still respecting boundary conditions.
   NOTE: Positive slopes indicate that each iteration goes further out from the center
   of the current cache block, while negative slopes go toward the block center. */
void time_skewing_per_thread(int32_t *threadBlock, int32_t *threadBlockMin, int32_t *threadBlockMax, int32_t task_id) {
  double * __restrict__ temp_ptr;
  uint32_t block_i, block_j, block_k;
  uint32_t neg_x_slope, pos_x_slope, neg_y_slope, pos_y_slope, neg_z_slope, pos_z_slope;
  uint32_t initBlockMin_x, initBlockMin_y, initBlockMin_z;
  uint32_t initBlockMax_x, initBlockMax_y, initBlockMax_z;
  uint32_t blockMin_x, blockMin_y, blockMin_z;
  uint32_t blockMax_x, blockMax_y, blockMax_z;
  uint32_t offset_x, offset_y, offset_z;
  uint32_t end_x, end_y, end_z;
  uint32_t i, j, k, t;

  const int32_t threadBlock_x = threadBlock[0];
  const int32_t threadBlock_y = threadBlock[1];
  const int32_t threadBlock_z = threadBlock[2];
  const int32_t threadBlockMin_x = threadBlockMin[0];
  const int32_t threadBlockMin_y = threadBlockMin[1];
  const int32_t threadBlockMin_z = threadBlockMin[2];
  const int32_t threadBlockMax_x = threadBlockMax[0];
  const int32_t threadBlockMax_y = threadBlockMax[1];
  const int32_t threadBlockMax_z = threadBlockMax[2];

  double * __restrict__ Read_start = A;
  double * __restrict__ Write_start = B;

  neg_x_slope = 1;
  pos_x_slope = 1;
  neg_y_slope = 1;
  pos_y_slope = 1;
  neg_z_slope = 1;
  pos_z_slope = 1;

  end_x = 0;
  end_y = 0;
  end_z = 0;

  offset_x = 2*(numIter-1);
  offset_y = 2*(numIter-1);
  offset_z = 2*(numIter-1);

  if (threadBlock_x == 0) {
    neg_x_slope = 0;
  }
  if (threadBlock_x == (numThreadBlocks_x-1)) {
    pos_x_slope = 0;
    end_x = 1;
    offset_x = 0;
  }

  if (threadBlock_y == 0) {
    neg_y_slope = 0;
  }
  if (threadBlock_y == (numThreadBlocks_y-1)) {
    pos_y_slope = 0;
    end_y = 1;
    offset_y = 0;
  }
      
  if (threadBlock_z == 0) {
    neg_z_slope = 0;
  }
  if (threadBlock_z == (numThreadBlocks_z-1)) {
    pos_z_slope = 0;
    end_z = 1;
    offset_z = 0;
  }

  for (t=0; t < numIter; t++) {
    if (!end_x) {
      for (i=(threadBlockMax_x-2*numIter+t+1); i < (threadBlockMax_x-t); i++) {
	for (j=(threadBlockMin_y+neg_y_slope*t); j < (threadBlockMax_y-t); j++) {
	  for (k=(threadBlockMin_z+neg_z_slope*t); k < (threadBlockMax_z-t); k++) {
	    Write_start[Index3D(i,j,k)] = alpha * Read_start[Index3D(i,j,k)] + 
	      beta * (Read_start[Index3D(i-1,j,k)] + Read_start[Index3D(i+1,j,k)] + Read_start[Index3D(i,j-1,k)] + Read_start[Index3D(i,j+1,k)] + Read_start[Index3D(i,j,k-1)] + Read_start[Index3D(i,j,k+1)]);
	  }
	}
      }
    }
    if (!end_y) {
      for (i=(threadBlockMin_x+neg_x_slope*t); i < (threadBlockMax_x-t); i++) {
	for (j=(threadBlockMax_y-2*numIter+t+1); j < (threadBlockMax_y-t); j++) {
	  for (k=(threadBlockMin_z+neg_z_slope*t); k < (threadBlockMax_z-t); k++) {
	    Write_start[Index3D(i,j,k)] = alpha * Read_start[Index3D(i,j,k)] + 
	      beta * (Read_start[Index3D(i-1,j,k)] + Read_start[Index3D(i+1,j,k)] + Read_start[Index3D(i,j-1,k)] + Read_start[Index3D(i,j+1,k)] + Read_start[Index3D(i,j,k-1)] + Read_start[Index3D(i,j,k+1)]);
	  }
	}
      }
    }
    if (!end_z) {
      for (i=(threadBlockMin_x+neg_x_slope*t); i < (threadBlockMax_x-t); i++) {
	for (j=(threadBlockMin_y+neg_y_slope*t); j < (threadBlockMax_y-t); j++) {
	  for (k=(threadBlockMax_z-2*numIter+t+1); k < (threadBlockMax_z-t); k++) {
	    Write_start[Index3D(i,j,k)] = alpha * Read_start[Index3D(i,j,k)] + 
	      beta * (Read_start[Index3D(i-1,j,k)] + Read_start[Index3D(i+1,j,k)] + Read_start[Index3D(i,j-1,k)] + Read_start[Index3D(i,j+1,k)] + Read_start[Index3D(i,j,k-1)] + Read_start[Index3D(i,j,k+1)]);
	  }
	}
      }
    }

    if (!end_x && end_y) {
      for (i=(threadBlockMax_x-2*numIter+t+1); i < (threadBlockMax_x-t); i++) {
	for (k=(threadBlockMin_z+neg_z_slope*t); k < (threadBlockMax_z-t); k++) {
	  j=threadBlockMax_y-(threadBlockMax_x-i);
	}
      }
    }
    if (!end_x && end_z) {
      for (i=(threadBlockMax_x-2*numIter+t+1); i < (threadBlockMax_x-t); i++) {
	for (j=(threadBlockMin_y+neg_y_slope*t); j < (threadBlockMax_y-t); j++) {
	  k=threadBlockMax_z-(threadBlockMax_x-i);
	}
      }
    }
    if (!end_y && end_x) {
      for (j=(threadBlockMax_y-2*numIter+t+1); j < (threadBlockMax_y-t); j++) {
	for (k=(threadBlockMin_z+neg_z_slope*t); k < (threadBlockMax_z-t); k++) {
	  i=threadBlockMax_x-(threadBlockMax_y-j);
	}
      }
    }
    if (!end_z && end_x) {
      for (k=(threadBlockMax_z-2*numIter+t+1); k < (threadBlockMax_z-t); k++) {
	for (j=(threadBlockMin_z+neg_y_slope*t); k < (threadBlockMax_z-t); k++) {
	  i=threadBlockMax_x-(threadBlockMax_z-k);
	}
      }
    }
    if (!end_y && end_z) {
      for (j=(threadBlockMax_y-2*numIter+t+1); j < (threadBlockMax_y-t); j++) {
	for (i=(threadBlockMin_x+neg_x_slope*t); i < (threadBlockMax_x-t); i++) {
	  k=threadBlockMax_z-(threadBlockMax_y-j);
	}
      }
    }
    if (!end_z && end_y) {
      for (k=(threadBlockMax_z-2*numIter+t+1); k < (threadBlockMax_z-t); k++) {
	for (i=(threadBlockMin_x+neg_x_slope*t); i < (threadBlockMax_x-t); i++) {
	  j=threadBlockMax_y-(threadBlockMax_z-k);
	}
      }
    }

    temp_ptr = Read_start;
    Read_start = Write_start;
    Write_start = temp_ptr;
  }

  barrier_wait(&my_barrier, task_id);
  /*
  Read_start = A;
  Write_start = B;

  initBlockMin_x = realMin_x + threadBlock_x * numThreadBlockCells_x;
  initBlockMin_y = realMin_y + threadBlock_y * numThreadBlockCells_y;
  initBlockMin_z = realMin_z + threadBlock_z * numThreadBlockCells_z;
  
  initBlockMax_x = initBlockMin_x + numThreadBlockCells_x - offset_x;
  initBlockMax_y = initBlockMin_y + numThreadBlockCells_y - offset_y;
  initBlockMax_z = initBlockMin_z + numThreadBlockCells_z - offset_z;

  for (t=0; t < numIter; t++) {
    // set block size based on number of iterations performed
    blockMin_x = initBlockMin_x - t * neg_x_slope;
    blockMin_y = initBlockMin_y - t * neg_y_slope;
    blockMin_z = initBlockMin_z - t * neg_z_slope;
    
    blockMax_x = initBlockMax_x + t * pos_x_slope;
    blockMax_y = initBlockMax_y + t * pos_y_slope;
    blockMax_z = initBlockMax_z + t * pos_z_slope;

    // actual calculations
    for (i=blockMin_x; i < blockMax_x; i++) {
      for (j=blockMin_y; j < blockMax_y; j++) {
	for (k=blockMin_z; k < blockMax_z; k++) {
	  Write_start[Index3D(i,j,k)] = alpha * Read_start[Index3D(i,j,k)] + 
	    beta * (Read_start[Index3D(i-1,j,k)] + Read_start[Index3D(i+1,j,k)] + Read_start[Index3D(i,j-1,k)] + Read_start[Index3D(i,j+1,k)] + Read_start[Index3D(i,j,k-1)] + Read_start[Index3D(i,j,k+1)]);
	}
      }
    }
    temp_ptr = Read_start;
    Read_start = Write_start;
    Write_start = temp_ptr;
  }
  */
}

void *all_threads(void *thread_id) {
  int32_t threadBlock_id, task_id;
  int32_t threadBlock[3], threadBlockMin[3], threadBlockMax[3];

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
  if (task_id == 0) {
    printf("\nGRID A BEFORE:");
    print_grid(A);
    printf("\nGRID B BEFORE:");
    print_grid(B);
  }
  barrier_wait(&my_barrier, task_id);
  time_skewing_per_thread(threadBlock, threadBlockMin, threadBlockMax, task_id);
  barrier_wait(&my_barrier, task_id);
  if (task_id == 0) {
    printf("\nGRID A AFTER:");
    print_grid(A);
    printf("\nGRID B AFTER:");
    print_grid(B);
  }
#else
#if defined(PAPI_ENABLED)
  int papi_setnum;
  
  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, time_skewing_per_thread(threadBlock, threadBlockMin, threadBlockMax, task_id), results, NUM_TRIALS*(papi_setnum*num_threads+task_id), NUM_TRIALS);
  }
  barrier_wait(&my_barrier, task_id);
  if (task_id == 0) {
    print_papi_measurements(event_sets, results, num_sets, num_threads, NUM_TRIALS);
  }
#else
  TIMER_MAKE_MEASUREMENTS(time_skewing_per_thread(threadBlock, threadBlockMin, threadBlockMax, task_id), results, task_id, NUM_TRIALS);
  barrier_wait(&my_barrier, task_id);
  if (task_id == 0) {
    int32_t t;
    printf("TIME (IN SECONDS)\n");
    for (t=0; t < num_threads; t++) {
      printf("Thread %d:\n", t);
      print_timer_measurements(&results[t * NUM_TRIALS], NUM_TRIALS, median_counts_per_sec);
    }
    printf("Max time over all threads:\n");
    print_max_timer_measurements(results, num_threads, NUM_TRIALS, median_counts_per_sec);
  }
#endif
#endif
}

int main(int argc, char *argv[]) {
  pthread_t *threads;
  pthread_attr_t attr;
  int32_t **task_ids;
  int status;

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

  // initialize threaded PAPI
  if (PAPI_thread_init((unsigned long (*)(void)) (pthread_self)) != PAPI_OK) {
    printf("Error with PAPI_thread_init().\n");
    exit(EXIT_FAILURE);
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
    printf("Creating thread %u\n", t);
#endif
    rc = pthread_create(&threads[t], &attr, all_threads, (void *) task_ids[t]);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }

  // wait on other threads
  for (t=0; t < num_threads; t++) {
    pthread_join(threads[t], (void **) &status);
  }

  printf("\nFinal interior values: A[%u, %u, %u] = %4.2e, B[%u, %u, %u] = %4.2e\n", nx/2, ny/2, nz/2, A[Index3D(nx/2, ny/2, nz/2)], nx/2, ny/2, nz/2, B[Index3D(nx/2, ny/2, nz/2)]);
  fc_checksum();

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  papi_cleanup(event_sets, num_sets);
#endif
  pthread_attr_destroy(&attr);
  pthread_exit(NULL);
  barrier_destroy(&my_barrier);
  free_grids();

  return EXIT_SUCCESS;
}
