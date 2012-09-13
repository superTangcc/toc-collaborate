void malloc_arrays(char *argv[]) {
  uint64_t singleArrayAllThreadsMemoryAllocationInB, singleArrayAllThreadsPaddingMemoryAllocationInB, singleArrayAllThreadsAlignmentMemoryAllocationInB;
  uint64_t temp_ptr;
  uint64_t mask = ARRAY_ALIGNMENT-1;
  uint32_t a, t;

  numThreads = atoi(argv[1]);
  numReadArraysPerThread = atoi(argv[2]);
  numWriteArraysPerThread = atoi(argv[3]);
  memoryFootprintInB = atoi(argv[4]);
  threadPaddingLength = atoi(argv[5]);

  singleArrayAllThreadsMemoryAllocationInB = (memoryFootprintInB) / (numReadArraysPerThread + numWriteArraysPerThread);
  singleArrayAllThreadsPaddingMemoryAllocationInB = ((numThreads * (numThreads-1))/2) * threadPaddingLength * sizeof(double);
  singleArrayAllThreadsAlignmentMemoryAllocationInB = numThreads * ARRAY_ALIGNMENT;
  threadArrayLength = ((singleArrayAllThreadsMemoryAllocationInB - singleArrayAllThreadsPaddingMemoryAllocationInB - singleArrayAllThreadsAlignmentMemoryAllocationInB) / sizeof(double)) / numThreads;
  AllArrays = (double *) malloc((numReadArraysPerThread + numWriteArraysPerThread) * singleArrayAllThreadsMemoryAllocationInB);

  if (AllArrays == NULL) {
    printf("Error on AllArrays malloc.\n");
    exit(EXIT_FAILURE);
  }

  Arrays = (double ***) malloc((numReadArraysPerThread + numWriteArraysPerThread) * sizeof(double **));

  if (Arrays == NULL) {
    printf("Error on Arrays malloc.\n");
    exit(EXIT_FAILURE);
  }

  for (a=0; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    Arrays[a] = (double **) malloc(numThreads * sizeof(double *));

    if (Arrays[a] == NULL) {
      printf("Error on Arrays[%u] malloc.\n", a);
      exit(EXIT_FAILURE);
    }
  }

  for (a=0; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    Arrays[a][0] = (double *)((uint64_t)AllArrays + a * singleArrayAllThreadsMemoryAllocationInB);
  }

  for (a=0; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    for (t=1; t < numThreads; t++) {
      Arrays[a][t] = (double *)((uint64_t)&(Arrays[a][t-1][0]) + (threadArrayLength + (t-1) * threadPaddingLength) * sizeof(double) + ARRAY_ALIGNMENT);
    }
  }

  for (a=0; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    for (t=0; t < numThreads; t++) {
      temp_ptr = (uint64_t)&(Arrays[a][t][0]);
      Arrays[a][t] = (double *)(temp_ptr + (ARRAY_ALIGNMENT - (temp_ptr & mask)) + t * threadPaddingLength * sizeof(double));
    }
  }

#if defined(DEBUG)
  printf("Array alignment = %d\n", ARRAY_ALIGNMENT);

  for (a=0; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    for (t=0; t < numThreads; t++) {
      printf("Address of Arrays[%u][%u][0] = 0x%llx\n", a, t, (uint64_t)&(Arrays[a][t][0]));
    }
  }
#endif
}

void free_arrays() {
  uint32_t a;

  for (a=0; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    free(Arrays[a]);
  }

  free(Arrays);
  free(AllArrays);
}

void init_arrays(uint32_t rank) {
  double *Array_local;
  uint32_t a, i;

  for (a=0; a < numReadArraysPerThread; a++) {
    Array_local = (double *) Arrays[a][rank];
    for (i=0; i < threadArrayLength; i++) {
      Array_local[i] = INIT_READ_VALUE;
    }
  }

  for (a=numReadArraysPerThread; a < (numReadArraysPerThread+numWriteArraysPerThread); a++) {
    Array_local = (double *) Arrays[a][rank];
    for (i=0; i < threadArrayLength; i++) {
      Array_local[i] = INIT_WRITE_VALUE;
    }
  }
}

void print_array_parameters() {
  printf("num threads = \n%u,\n", numThreads);
  printf("num read arrays per thread = \n%u,\n", numReadArraysPerThread);
  printf("num write arrays per thread = \n%u,\n", numWriteArraysPerThread);
  printf("thread array length = \n%u,\n", threadArrayLength);
  printf("thread padding length = \n%u,\n", threadPaddingLength);
}

#if defined(DEBUG)
void print_arrays() {
  uint32_t a, t, i;

  for (a=0; a < numReadArraysPerThread; a++) {
    printf("\n\n\nREADARRAY%u:", a);
    for (t=0; t < numThreads; t++) {
      printf("\n\nThread %u:\n", t);
      for (i=0; i < threadArrayLength; i++) {
	printf("%lf\t", Arrays[a][t][i]);
      }
    }
  }

  for (a=numReadArraysPerThread; a < (numReadArraysPerThread + numWriteArraysPerThread); a++) {
    printf("\n\n\nWRITEARRAY%u:", (a - numReadArraysPerThread));
    for (t=0; t < numThreads; t++) {
      printf("\n\nThread %u:\n", t);
      for (i=0; i < threadArrayLength; i++) {
	printf("%lf\t", Arrays[a][t][i]);
      }
    }
  }
  printf("\n\n");
}
#endif
