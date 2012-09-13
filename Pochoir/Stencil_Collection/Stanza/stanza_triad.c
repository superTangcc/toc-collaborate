/*
 * Stanza Triad benchmark
 * Kaushik Datta and Shoaib Kamil
 * {kdatta, skamil}@cs.berkeley.edu
 * University of California Berkeley
 * February 21, 2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "flush_cache.h"
#include "stanza_triad.h"
#include "cycle.h"
#include "flush_cache.c"

#define CONVERT_B_PER_SEC_TO_GB_PER_SEC 1E-9
#define BYTES_PER_TRIAD 24
#define SCALAR 0.125
#define NUM_TRIALS 5
#define cycle_time getticks

// the following constants are in doubles
#define ARRAY_PADDING_LENGTH 19
#define ARRAY_JUMP_LENGTH 2048

double *A, *X, *Y;
uint64_t array_length;

double find_median(double *measurements, int num_measurements) {
  double median, temp;
  int i, j, min_idx;

  // sort the array first
  for (i=0; i < num_measurements; i++) {
    min_idx = i;
    for (j=(i+1); j < num_measurements; j++) {
      if (measurements[j] < measurements[min_idx]) {
	min_idx = j;
      }
    }
    temp = measurements[i];
    measurements[i] = measurements[min_idx];
    measurements[min_idx] = temp;
  }

  if ((num_measurements % 2) == 1) {
    median = measurements[num_measurements/2];
  }
  else {
    median = (measurements[num_measurements/2 - 1] + measurements[num_measurements/2])/2.0;
  }

  return median;
}

void init_read_arrays() {
  uint64_t i;

  for (i=0; i<array_length; i++) {
    X[i] = 4.0;
    Y[i] = 0.5;
  }
}

void init_write_array() {
  uint64_t i;

  for (i=0; i<array_length; i++) {
    A[i] = 0.0;
  }
}

double stanza_triad_checksum() {
  double checksum;
  uint64_t i;

  checksum = 0.0;
  for (i=0; i<array_length; i++) {
    checksum += A[i];
  }
  return checksum;
}

void stanza_triad(uint64_t stanza_length) {
  uint64_t idx_start, idx_end, i;

  idx_start = 0;
  idx_end = stanza_length;

  while (idx_end <= array_length) {
    for (i=idx_start; i<idx_end; i++) {
      A[i] = SCALAR * X[i] + Y[i];
    }
    idx_start = idx_end + ARRAY_JUMP_LENGTH;
    idx_end = idx_start + stanza_length;
  }
}

int main(int argc, char *argv[]) {
  double timings[NUM_TRIALS];
  double ticks_per_second;
  uint64_t t_start, t_end;
  uint64_t stanza_length, num_stanzas;
  int log2_min_stanza_length, log2_max_stanza_length, log2_array_length;
  int i, j;

  printf("\nSTANZA TRIAD BENCHMARK\n\n");

  if (argc < 4) {
    printf("Usage: %s [log2 of min stanza length] [log2 of max stanza length] [log2 of array length]\nExiting.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  log2_min_stanza_length = atoi(argv[1]);
  log2_max_stanza_length = atoi(argv[2]);
  log2_array_length = atoi(argv[3]);

  if ((log2_min_stanza_length < 0) || (log2_max_stanza_length < 0) || (log2_array_length < 0)) {
    printf("All three inputs must be nonnegative.  Exiting.\n");
    exit(EXIT_FAILURE);
  }

  if (log2_min_stanza_length > log2_max_stanza_length) {
    printf("The minimum stanza length must be less than or equal to the maximum stanza length.  Exiting.\n");
    exit(EXIT_FAILURE);
  }
  
  if (log2_max_stanza_length > log2_array_length) {
    printf("The maximum stanza length must be less than or equal to the array length.  Exiting.\n");
    exit(EXIT_FAILURE);
  }

  array_length = ((uint64_t)1 << log2_array_length);
  
  A = (double *) malloc((array_length+ARRAY_PADDING_LENGTH) * sizeof(double));
  X = (double *) malloc((array_length+ARRAY_PADDING_LENGTH) * sizeof(double));
  Y = (double *) malloc((array_length+ARRAY_PADDING_LENGTH) * sizeof(double));

  if ((A == NULL) || (X == NULL) || (Y == NULL)) {
    printf("Error on array malloc.  Exiting.\n");
    exit(EXIT_FAILURE);
  }

  printf("Minimum stanza length = 2^%d doubles\n", log2_min_stanza_length);
  printf("Maximum stanza length = 2^%d doubles\n", log2_max_stanza_length);
  printf("Length of each array (excluding padding) = 2^%d doubles\n", log2_array_length);
  printf("Number of trials (for both timer calibration and benchmark) = %d\n", NUM_TRIALS);

  printf("\nPERFORMING TIMER CALIBRATION...\n");
  for (i=0; i < NUM_TRIALS; i++) {
    t_start = cycle_time();
    sleep(1);
    t_end = cycle_time();
    timings[i] = 1.0 * (t_end-t_start);
  }
  ticks_per_second = find_median(timings, NUM_TRIALS);
  printf("\nUsing timer: %s", TIMER_DESC);
  printf("\nMedian ticks per second: %10.0f\n", ticks_per_second);

  init_read_arrays();
  init_flush_cache_array();

  printf("\nRUNNING STANZA TRIAD BENCHMARK...\n");
  printf("\nStanza Size\t# Stanzas\tMedian Time (sec)\tMemory BW (GB/sec)\n");
  for (i=log2_min_stanza_length; i<=log2_max_stanza_length; i++) {
    double median_time_in_seconds, memory_bandwidth;

    stanza_length = ((uint64_t)1 << i);
    num_stanzas = (array_length-stanza_length) / (stanza_length+ARRAY_JUMP_LENGTH) + 1;

    for (j=0; j < NUM_TRIALS; j++) {
      init_write_array();
      flush_cache();
      t_start = cycle_time();
      stanza_triad(stanza_length);
      t_end = cycle_time();
      timings[j] = 1.0 * (t_end-t_start);
    }

    if ((stanza_length*num_stanzas) != (int)(stanza_triad_checksum())) {
      printf("Error in stanza triad checksum.  Exiting.\n");
      exit(EXIT_FAILURE);
    }

    median_time_in_seconds = find_median(timings, NUM_TRIALS) / ticks_per_second;
    memory_bandwidth = stanza_length*num_stanzas*BYTES_PER_TRIAD*CONVERT_B_PER_SEC_TO_GB_PER_SEC/median_time_in_seconds;
    printf("2^%d doubles\t%llu\t\t%2.4f\t\t\t%2.3f\n", i, num_stanzas, median_time_in_seconds, memory_bandwidth);
  }

  if ((NUM_TRIALS*(log2_max_stanza_length-log2_min_stanza_length+1)) != (int)(flush_cache_checksum())) {
    printf("Error in flush cache checksum.  Exiting.\n");
    exit(EXIT_FAILURE);
  }
  else {
    printf("\nBoth the stanza triad checksum and the flush cache checksum were correct.\n\n");
  }

  free(A);
  free(X);
  free(Y);
  return EXIT_SUCCESS;
}
