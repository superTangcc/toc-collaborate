/*
 * Stanza Triad benchmark
 * Kaushik Datta and Shoaib Kamil
 * {kdatta, skamil}@cs.berkeley.edu
 * University of California Berkeley
 * February 21, 2008
 */
#include <stdint.h>

#define FLUSH_CACHE_ARRAY_LENGTH 8388608
double FC[FLUSH_CACHE_ARRAY_LENGTH];

void init_flush_cache_array() {
  uint64_t i;

  for (i=0; i < FLUSH_CACHE_ARRAY_LENGTH; i++) {
    FC[i] = 0.0;
  }
}

/* This function attempts to flush the cache by adding 1 to each element of the FC array */
void flush_cache() {
  uint64_t i;

  for (i=0; i < FLUSH_CACHE_ARRAY_LENGTH; i++) {
    FC[i] += 1.0;
  }
}

double flush_cache_checksum() {
  double checksum;
  uint64_t i;

  checksum = 0;
  for (i=0; i < FLUSH_CACHE_ARRAY_LENGTH; i++) {
    checksum += FC[i];
  }
  checksum /= FLUSH_CACHE_ARRAY_LENGTH;
  return checksum;
}
