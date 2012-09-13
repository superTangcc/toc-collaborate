/*  Circular queue stencil code
 *  Kaushik Datta (kdatta@cs.berkeley.edu)
 *  University of California Berkeley
 *
 *  This code implements the circular queue algorithm for stencil codes.
 *  Intermediate queues, each with three revolving planes, store temporary
 *  results until the final result is written to the target array.  Unlike
 *  the time skewing algorithm, this algorithm will perform redundant
 *  computation between adjacent slabs.
 *
 *  NOTE: Only the cache block's y-dimension is used in this code; it
 *  specifies the size of the circular queue's y-dimension.  The grid's
 *  y-dimension needs to be a multiple of the cache block's y-dimension.
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

barrier_t my_barrier;
int32_t num_threads;

double median_counts_per_sec;

/* This method traverses each slab and uses the circular queues to perform the
   specified number of iterations.  The circular queue at a given timestep is
   shrunken in the y-dimension from the circular queue at the previous timestep. */
void circular_queue_per_thread(double *queuePlane0, double *queuePlane1, double *queuePlane2, int32_t *queuePlanesIndices, int32_t *threadBlockMin, int32_t *threadBlockMax, int32_t task_id) {
  double *readQueuePlane0, *readQueuePlane1, *readQueuePlane2, *writeQueuePlane, *tempQueuePlane;
  int32_t blockMin_y, blockMax_y;
  int32_t writeBlockMin_y, writeBlockMax_y;
  int32_t writeBlockRealMin_y, writeBlockRealMax_y;
  int32_t readBlockUnitStride_y, writeBlockUnitStride_y;
  int32_t readOffset, writeOffset;
  int32_t i, j, k, s, t;

  const int32_t threadBlockMin_x = threadBlockMin[0];
  const int32_t threadBlockMin_y = threadBlockMin[1];
  const int32_t threadBlockMin_z = threadBlockMin[2];
  const int32_t threadBlockMax_x = threadBlockMax[0];
  const int32_t threadBlockMax_y = threadBlockMax[1];
  const int32_t threadBlockMax_z = threadBlockMax[2];
  
  double * __restrict__ Read_start = A;
  double * __restrict__ Write_start = B;

  s = task_id;
  for (i=realMin_x; i < (realMax_x+numIter-1); i++) {
    for (t=0; t < numIter; t++) {
      if ((i > t) && (i < (realMax_x+t))) {
	if (t == 0) {
	  readQueuePlane0 = &Read_start[Index3D(i-1,0,0)];
	  readQueuePlane1 = &Read_start[Index3D(i,0,0)];
	  readQueuePlane2 = &Read_start[Index3D(i+1,0,0)];
	}
	else {
	  readQueuePlane0 = &queuePlane0[queuePlanesIndices[t-1]];
	  readQueuePlane1 = &queuePlane1[queuePlanesIndices[t-1]];
	  readQueuePlane2 = &queuePlane2[queuePlanesIndices[t-1]];
	}
	
	// determine the edges of the queues
	writeBlockMin_y = s * numThreadBlockCells_y - (numIter-t) + 2;
	writeBlockMax_y = (s+1) * numThreadBlockCells_y + (numIter-t);
	writeBlockRealMin_y = writeBlockMin_y;
	writeBlockRealMax_y = writeBlockMax_y;
	
	if (writeBlockMin_y < realMin_y) {
	  writeBlockMin_y = 0;
	  writeBlockRealMin_y = realMin_y;
	}
	if (writeBlockMax_y > realMax_y) {
	  writeBlockMax_y = ny;
	  writeBlockRealMax_y = realMax_y;
	}
	
	if (t == (numIter-1)) {
	  writeQueuePlane = Write_start;
	  writeOffset = 0;
	}
	else {
	  writeQueuePlane = &queuePlane2[queuePlanesIndices[t]];
	  writeOffset = Index3D(i-t,writeBlockMin_y, 0);
	}
	
	if ((writeBlockMin_y == 0) || (t == 0)) {
	  readOffset = Index3D(i-t,0,0);
	}
	else {
	  readOffset = Index3D(i-t,writeBlockMin_y-realMin_y,0);
	}
	
	// use ghost cells for the bottommost and topmost planes
	if (i == (t+1)) {
	  readQueuePlane0 = Read_start;
	}
	if (i == (realMax_x+t-1)) {
	  readQueuePlane2 = &Read_start[Index3D(realMax_x,0,0)];
	}
	
	// copy ghost cells
	if (t < (numIter-1)) {
	  for (j=(writeBlockMin_y+1); j < (writeBlockMax_y-1); j++) {
	    writeQueuePlane[Index3D(i-t,j,0) - writeOffset] = readQueuePlane1[Index3D(i-t,j,0) - readOffset];
	    writeQueuePlane[Index3D(i-t,j,realMax_z) - writeOffset] = readQueuePlane1[Index3D(i-t,j,realMax_z) - readOffset];
	  }
	  if (writeBlockMin_y == 0) {
	    for (k=realMin_z; k < realMax_z; k++) {
	      writeQueuePlane[Index3D(i-t,writeBlockMin_y,k) - writeOffset] = readQueuePlane1[Index3D(i-t,writeBlockMin_y,k) - readOffset];
	    }
	  }
	  if (writeBlockMax_y == ny) {
	    for (k=realMin_z; k < realMax_z; k++) {
	      writeQueuePlane[Index3D(i-t,writeBlockRealMax_y,k) - writeOffset] = readQueuePlane1[Index3D(i-t,writeBlockRealMax_y,k) - readOffset];
	    }
	  }
	}
	
	// actual calculations
	for (j=writeBlockRealMin_y; j < writeBlockRealMax_y; j++) {
	  for (k=realMin_z; k < realMax_z; k++) {
	    writeQueuePlane[Index3D(i-t,j,k) - writeOffset] = alpha * readQueuePlane1[Index3D(i-t,j,k) - readOffset] +
	      beta * (readQueuePlane0[Index3D(i-t,j,k) - readOffset] + readQueuePlane2[Index3D(i-t,j,k) - readOffset] + readQueuePlane1[Index3D(i-t,j-1,k) - readOffset] + readQueuePlane1[Index3D(i-t,j,k-1) - readOffset] + readQueuePlane1[Index3D(i-t,j,k+1) - readOffset] + readQueuePlane1[Index3D(i-t,j+1,k) - readOffset]);
	  }
	}
      }
    }
    if (t > 0) {
      tempQueuePlane = queuePlane0;
      queuePlane0 = queuePlane1;
      queuePlane1 = queuePlane2;
      queuePlane2 = tempQueuePlane;
    }
  }
}

void *circular_queue_all_threads(void *thread_id) {
  double *queuePlane0, *queuePlane1, *queuePlane2;
  int32_t *queuePlanesIndices;
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

  if (numIter > 1) {
    // create circular queue data structure
    
    double *queuePlanes;
    int32_t numPointsInQueuePlane, t;
    
    queuePlanesIndices = (int32_t *) malloc((numIter-1) * sizeof(int32_t));
    
    if (queuePlanesIndices==NULL) {
	printf("Error on array queuePlanesIndices malloc.\n");
	exit(EXIT_FAILURE);
    }
    
    int32_t queuePlanesIndexPtr = 0;
    
    for (t=1; t < numIter; t++) {
	queuePlanesIndices[t-1] = queuePlanesIndexPtr;
	numPointsInQueuePlane = (numThreadBlockCells_y+2*(numIter-t)) * nz;
	queuePlanesIndexPtr += numPointsInQueuePlane;
    }
    
    queuePlanes = (double *) malloc(3 * queuePlanesIndexPtr * sizeof(double));
    
    if (queuePlanes==NULL) {
	printf("Error on array queuePlanes malloc.\n");
	exit(EXIT_FAILURE);
    }
    
    queuePlane0 = queuePlanes;
    queuePlane1 = &queuePlanes[queuePlanesIndexPtr];
    queuePlane2 = &queuePlanes[2 * queuePlanesIndexPtr];
  }
  
#if defined(DEBUG)
  init_grids_per_thread(threadBlock, threadBlockMin, threadBlockMax);
  if (task_id == 0) {
    printf("\nGRID A BEFORE:");
    print_grid(A);
    printf("\nGRID B BEFORE:");
    print_grid(B);
  }
  barrier_wait(&my_barrier, task_id);
  circular_queue_per_thread(queuePlane0, queuePlane1, queuePlane2, queuePlanesIndices, threadBlockMin, threadBlockMax, task_id);
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
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, circular_queue_per_thread(queuePlane0, queuePlane1, queuePlane2, queuePlanesIndices, threadBlockMin, threadBlockMax, task_id), results, NUM_TRIALS*(papi_setnum*num_threads+task_id), NUM_TRIALS);
  }
  barrier_wait(&my_barrier, task_id);
  if (task_id == 0) {
    print_papi_measurements(event_sets, results, num_sets, num_threads, NUM_TRIALS);
  }
#else
  TIMER_MAKE_MEASUREMENTS(circular_queue_per_thread(queuePlane0, queuePlane1, queuePlane2, queuePlanesIndices, threadBlockMin, threadBlockMax, task_id), results, task_id, NUM_TRIALS);
  barrier_wait(&my_barrier, task_id);
  if (task_id == 0) {
    int32_t t;
    printf("TIME (IN SECONDS)\n");
#if defined(THREAD_PROFILING)
    for (t=0; t < num_threads; t++) {
      printf("Thread %d:\n", t);
      print_timer_measurements(&results[t * NUM_TRIALS], NUM_TRIALS, median_counts_per_sec);
    }
#endif
    printf("Max time over all threads:\n");
    print_max_timer_measurements(results, num_threads, NUM_TRIALS, median_counts_per_sec);
  }
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

  num_threads = numThreadBlocks_y;
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
    rc = pthread_create(&threads[t], &attr, circular_queue_all_threads, (void *) task_ids[t]);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }

  // wait on other threads
  for (t=0; t < num_threads; t++) {
    pthread_join(threads[t], &status);
  }

  printf("\nFinal interior values: A[%u, %u, %u] = %4.2e, B[%u, %u, %u] = %4.2e\n", nx/2, ny/2, nz/2, A[Index3D(nx/2, ny/2, nz/2)], nx/2, ny/2, nz/2, B[Index3D(nx/2, ny/2, nz/2)]);
  flush_cache_checksum();

#if defined(PAPI_ENABLED) && !defined(DEBUG)
  papi_cleanup(event_sets, num_sets);
#endif
  pthread_attr_destroy(&attr);
  pthread_exit(NULL);
  barrier_destroy(&my_barrier);
  free_grids();

  return EXIT_SUCCESS;
}
