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
#include "globals.h"
#include "../common/flush_cache.h"
#include "../common/helper_functions.h"
#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
#include "../../papi/papi_util.c"
#else
#include <unistd.h>
#include "../../cycle_time/cycle_time.h"
#include "../../cycle_time/cycle_time.c"
#endif
#endif
#include "grid.c"
#include "../common/flush_cache.c"
#include "../common/helper_functions.c"

double *queuePlanes, *queuePlane0, *queuePlane1, *queuePlane2;
int32_t *queuePlanesIndices;

/* This method creates the circular queues that will be needed for the
   circular_queue() method.  It is only called when more than one iteration
   is being performed. */
void init_circular_queue() {
  int32_t numPointsInQueuePlane, t;
  
  queuePlanesIndices = (int32_t *) malloc((numIter-1) * sizeof(int32_t));
  
  if (queuePlanesIndices==NULL) {
    printf("Error on array queuePlanesIndices malloc.\n");
    exit(EXIT_FAILURE);
  }
  
  int32_t queuePlanesIndexPtr = 0;
  
  for (t=1; t < numIter; t++) {
    queuePlanesIndices[t-1] = queuePlanesIndexPtr;
    numPointsInQueuePlane = (numBlockCells_y+2*(numIter-t)) * nz;
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

/* This method traverses each slab and uses the circular queues to perform the
   specified number of iterations.  The circular queue at a given timestep is
   shrunken in the y-dimension from the circular queue at the previous timestep. */
void circular_queue() {
  double *readQueuePlane0, *readQueuePlane1, *readQueuePlane2, *writeQueuePlane, *tempQueuePlane;
  int32_t blockMin_y, blockMax_y;
  int32_t writeBlockMin_y, writeBlockMax_y;
  int32_t writeBlockRealMin_y, writeBlockRealMax_y;
  int32_t readBlockUnitStride_y, writeBlockUnitStride_y;
  int32_t readOffset, writeOffset;
  int32_t i, j, k, s, t;
  
  double * __restrict__ Read_start = A;
  double * __restrict__ Write_start = B;

  for (s=0; s < numBlocks_y; s++) {
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
	  writeBlockMin_y = s * numBlockCells_y - (numIter-t) + 2;
	  writeBlockMax_y = (s+1) * numBlockCells_y + (numIter-t);
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
	      writeQueuePlane[Index3D(i-t,j,k) - writeOffset] = S0 * readQueuePlane1[Index3D(i-t,j,k) - readOffset] +
		S1 * (readQueuePlane0[Index3D(i-t,j,k) - readOffset] + readQueuePlane2[Index3D(i-t,j,k) - readOffset] + readQueuePlane1[Index3D(i-t,j-1,k) - readOffset] + readQueuePlane1[Index3D(i-t,j,k-1) - readOffset] + readQueuePlane1[Index3D(i-t,j,k+1) - readOffset] + readQueuePlane1[Index3D(i-t,j+1,k) - readOffset]);
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
}

int main(int argc, char *argv[]) {
  double results[NUM_TRIALS];
#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
  int papi_setnum, num_desired, num_sets;
#else
  double median_counts_per_sec;
#endif
#endif

  printf("\n7-point stencil, no add, circular queue C code with non-periodic boundary conditions\n");

  // initialize arrays
  init_flush_cache_array();
  malloc_grids(argv);
  if (numIter > 1) {
    init_circular_queue();
  }

#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
  // initialize papi
  int desired_events[] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS};
  num_desired = 9;
  PAPI_event_set_wrapper_t* event_sets;
  papi_init(desired_events, num_desired, &event_sets, &num_sets);
#else
  // calculate clock rate
  GET_CLOCK_RATE(results, NUM_TRIALS);
  median_counts_per_sec = find_median(results, NUM_TRIALS);
  printf("Median ticks per second = %e\n", median_counts_per_sec);
#endif
#endif

  printf("\n");

#if defined(DEBUG)
  init_grids();
  
  printf("Circular queue:\n");
  printf("\nGRID A BEFORE:");
  print_grid(A);
  printf("\nGRID B BEFORE:");
  print_grid(B);

  circular_queue();

  printf("\nGRID A AFTER:");
  print_grid(A);
  printf("\nGRID B AFTER:");
  print_grid(B);
#else
#if defined(PAPI_ENABLED)
  printf("Circular queue:\n");
  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, circular_queue(), NUM_TRIALS, results);
    print_papi_measurements(&(event_sets[papi_setnum]), results, NUM_TRIALS);
  }
  printf("\n");
#else
  printf("Circular queue:\n");
  TIMER_MAKE_MEASUREMENTS(circular_queue(), results, NUM_TRIALS);
  print_timer_measurements(results, NUM_TRIALS, median_counts_per_sec);
  printf("\n");
#endif
#endif

  printf("\nFinal interior values: A[%d, %d, %d] = %lf, B[%d, %d, %d] = %lf\n", nx/2, ny/2, nz/2, A[Index3D(nx/2, ny/2, nz/2)], nx/2, ny/2, nz/2, B[Index3D(nx/2, ny/2, nz/2)]);
  flush_cache_checksum();
  free_grids();
  return EXIT_SUCCESS;
}
