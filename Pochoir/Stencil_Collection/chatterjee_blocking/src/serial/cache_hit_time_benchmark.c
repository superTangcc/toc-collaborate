#include <stdio.h>
#include <stdlib.h>
#include "../papi/papi_util.h"
#include "flush_cache.h"

#define NUM_TRIALS 10
#define S0 1.0001

double *A, *B;
int stanzaLength, arrayLength;
int numIterations;

void initArrays() {
  int i;

  for (i=0; i<arrayLength; i++) {
    A[i] = 2.0;
    B[i] = 3.0;
  }
}

void cacheBenchmark() {
  int i, j;

  for (i=0; i<numIterations; i++) {
    for (j=0; j<stanzaLength; j++) {
      A[j] = S0 * B[j];
    }
  }
}

int main(int argc, char *argv[]) {
  double results[NUM_TRIALS];
  int i, papi_setnum;
  
  // initialize papi
  int desired_events[] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_L2_DCA, PAPI_L2_DCM, PAPI_L3_DCA, PAPI_L3_DCM, PAPI_TLB_DM, PAPI_LD_INS, PAPI_SR_INS};
  int num_desired = 9;
  PAPI_event_set_wrapper_t* event_sets;
  int num_sets;
  papi_init(desired_events, num_desired, &event_sets, &num_sets);

  // input parameters
  int log2_stanzaLength = atoi(argv[1]);
  int log2_numIterations = atoi(argv[2]);

  // compute actual values from base 2 logs
  stanzaLength = 1;
  for (i=0; i<log2_stanzaLength; i++) {
    stanzaLength *= 2;
  }

  numIterations = 1;
  for (i=0; i<log2_numIterations; i++) {
    numIterations *= 2;
  }
  
  int arrayLength = stanzaLength;

  printf("\nstanzaLength = %d\n", stanzaLength);
  printf("arrayLength = %d\n", arrayLength);
  printf("numIterations = %d\n", numIterations);
  printf("num_sets = %d\n\n", num_sets);
  
  // allocate working arrays
  A = (double *) malloc(arrayLength * sizeof(double));
  B = (double *) malloc(arrayLength * sizeof(double));

  if (A==NULL) {
    printf("Error on array A malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (B==NULL) {
    printf("Error on array B malloc.\n");
    exit(EXIT_FAILURE);
  }

  // initialize arrays
  init_flush_cache_array();
  initArrays();

  for (papi_setnum=0; papi_setnum < num_sets; papi_setnum++) {
    PAPI_MAKE_MEASUREMENTS(event_sets[papi_setnum].set, cacheBenchmark(), NUM_TRIALS, results);
    print_measurements(&(event_sets[papi_setnum]), results, NUM_TRIALS);
  }

  papi_cleanup(event_sets, num_sets);

  return 0;
}
