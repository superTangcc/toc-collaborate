void malloc_arrays(char *argv[]) {
  uint64_t singleArrayAllThreadsMemoryAllocationInB, singleArrayAllThreadsPaddingMemoryAllocationInB, singleArrayAllThreadsAlignmentMemoryAllocationInB;
  uint64_t temp_ptr;
  uint64_t mask = ARRAY_ALIGNMENT-1;
  uint32_t numReadArraysPerThread_param, numWriteArraysPerThread_param, threadPaddingLength_param;
  uint32_t parameters_set = 0;
  uint32_t job_num = 0;
  uint32_t a, t;

  numThreads = atoi(argv[1]);
  //  numReadArraysPerThread = atoi(argv[2]);
  //  numWriteArraysPerThread = atoi(argv[3]);
  for (numReadArraysPerThread_param=0; numReadArraysPerThread_param<8; numReadArraysPerThread_param++) {
    for (numWriteArraysPerThread_param=0; numWriteArraysPerThread_param<8; numWriteArraysPerThread_param++) {
      if (my_proc_num == (job_num % num_procs)) {
	numReadArraysPerThread = numReadArraysPerThread_param;
	numWriteArraysPerThread = numWriteArraysPerThread_param;

	if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 0) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 4;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 1) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 4;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 7;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 2) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 3;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 3) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 4;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 7;
	}
	else if ((numReadArraysPerThread == 4) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 3;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 4;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 4;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 5) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 7;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 1;
	}
	else if ((numReadArraysPerThread == 6) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 0)) {
	    threadPaddingLength = 2;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 1)) {
	    threadPaddingLength = 4;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 2)) {
	    threadPaddingLength = 3;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 3)) {
	    threadPaddingLength = 0;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 4)) {
	    threadPaddingLength = 6;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 5)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 6)) {
	    threadPaddingLength = 5;
	}
	else if ((numReadArraysPerThread == 7) && (numWriteArraysPerThread == 7)) {
	    threadPaddingLength = 3;
	}

	parameters_set = 1;
      }
      job_num++;
    }
  }
  if (!parameters_set) {
    exit(EXIT_SUCCESS);
  }

  memoryFootprintInB = atoi(argv[4]);
//  threadPaddingLength = atoi(argv[5]);

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
  char temp_str[20];

  strcpy(output_str, "num threads = ");
  sprintf(temp_str, "%u; ", numThreads);
  strcat(output_str, temp_str);
  strcat(output_str, "num read arrays per thread = ");
  sprintf(temp_str, "%u; ", numReadArraysPerThread);
  strcat(output_str, temp_str);
  strcat(output_str, "num write arrays per thread = ");
  sprintf(temp_str, "%u; ", numWriteArraysPerThread);
  strcat(output_str, temp_str);
  strcat(output_str, "thread array length = ");
  sprintf(temp_str, "%u; ", threadArrayLength);
  strcat(output_str, temp_str);
  strcat(output_str, "thread padding length = ");
  sprintf(temp_str, "%u; ", threadPaddingLength);
  strcat(output_str, temp_str);
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
