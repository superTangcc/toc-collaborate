#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "globals.h"
#if !defined(DEBUG)
#if defined(PAPI_ENABLED)
#include "../papi/papi_util.h"
#else
#include <unistd.h>
#include "cycle_time.h"
#include "cycle_time.c"
#endif
#endif
#include "grid.c"
#include "flush_cache.c"

void naive_singly_nested_loop() {
  double * __restrict__ temp_ptr;
  uint_fast32_t i, loop_start, loop_end, t;

  double * __restrict__ Read_start = A;
  double * __restrict__ Write_start = B;

  loop_start = Index3D(realMin_x, realMin_y, realMin_z);
  loop_end = Index3D(realMax_x-1, realMax_y-1, realMax_z-1);

  for (t=0; t < numIter; t++) {
    for (i=loop_start; i <= loop_end; i++) {
      Write_start[i] = S1 * (Read_start[i-ny*nz] + Read_start[i-ny] + Read_start[i-1] + Read_start[i+1] + Read_start[i+ny] + Read_start[i+ny*nz]) + S0 * Read_start[i];
    }
    temp_ptr = Read_start;
    Read_start = Write_start;
    Write_start = temp_ptr;
  }
}

void naive_triply_nested_loops() {
  double * __restrict__ temp_ptr;
  uint_fast32_t i, j, k, t;

  double * __restrict__ Read_start = A;
  double * __restrict__ Write_start = B;

  for (t=0; t < numIter; t++) {
    for (i=realMin_x; i < realMax_x; i++) {
      for (j=realMin_y; j < realMax_y; j++) {
        for (k=realMin_z; k < realMax_z; k++) {
          Write_start[Index3D(i,j,k)] = S1 * (Read_start[Index3D(i-1,j,k)] + Read_start[Index3D(i,j-1,k)] + Read_start[Index3D(i,j,k-1)] + Read_start[Index3D(i,j,k+1)] + Read_start[Index3D(i,j+1,k)] + Read_start[Index3D(i+1,j,k)]) + S0 * Read_start[Index3D(i,j,k)];
        }
      }
    }
    temp_ptr = Read_start;
    Read_start = Write_start;
    Write_start = temp_ptr;
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
  int i;

  printf("7-point stencil, no add, naive C code with non-periodic boundary conditions\n");

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
#endif
#endif

  // initialize arrays
  init_flush_cache_array();
  malloc_grids(argv);
  printf("\n");

#if defined(DEBUG)
  init_grids();
  printf("SINGLY NESTED LOOP:\n");
  printf("\nGRID A BEFORE:");
  print_grid(A);
  printf("\nGRID B BEFORE:");
  print_grid(B);

  naive_singly_nested_loop();

  printf("\nGRID A AFTER:");
  print_grid(A);
  printf("\nGRID B AFTER:");
  print_grid(B);

  init_grids();
  printf("TRIPLY NESTED LOOPS:\n");
  printf("\nGRID A BEFORE:");
  print_grid(A);
  printf("\nGRID B BEFORE:");
  print_grid(B);

  naive_triply_nested_loops();

  printf("\nGRID A AFTER:");
  print_grid(A);
  printf("\nGRID B AFTER:");
  print_grid(B);
#else
#if defined(PAPI_ENABLED)
  printf("SINGLY NESTED LOOP:\n");
  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, naive_singly_nested_loop(), NUM_TRIALS, results);
    print_papi_measurements(&(event_sets[papi_setnum]), results, NUM_TRIALS);
  }
  printf("\n");
  printf("TRIPLY NESTED LOOPS:\n");
  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, naive_triply_nested_loops(), NUM_TRIALS, results);
    print_papi_measurements(&(event_sets[papi_setnum]), results, NUM_TRIALS);
  }
  printf("\n");
  papi_cleanup(event_sets, num_sets);
#else
  printf("SINGLY NESTED LOOP:\n");
  TIMER_MAKE_MEASUREMENTS(naive_singly_nested_loop(), results, NUM_TRIALS);
  print_timer_measurements(results, NUM_TRIALS, median_counts_per_sec);
  printf("\n");
  printf("TRIPLY NESTED LOOPS:\n");
  TIMER_MAKE_MEASUREMENTS(naive_triply_nested_loops(), results, NUM_TRIALS);
  print_timer_measurements(results, NUM_TRIALS, median_counts_per_sec);
  printf("\n");
  printf("\n");
#endif
#endif

  printf("\nFinal interior values: A[%lu, %lu, %lu] = %4.2e, B[%lu, %lu, %lu] = %4.2e\n", nx/2, ny/2, nz/2, A[Index3D(nx/2, ny/2, nz/2)], nx/2, ny/2, nz/2, B[Index3D(nx/2, ny/2, nz/2)]);
  fc_checksum();
  free(A);
  free(B);

  return EXIT_SUCCESS;
}
