/* This function initializes global variables as well as the arrays */
void malloc_grids(char *argv[]) {
  int32_t numCells, ghostCellDepth;
  int32_t nreals_x, nreals_y, nreals_z;
  int32_t padding_z_param;
  int32_t numCoreBlockCells_x_param, numCoreBlockCells_y_param, numCoreBlockCells_z_param, numCoreBlocksPerChunk_param;
  int32_t parameters_set = 0;
  int32_t job_num = 0;

  // number of iterations
  numIter = atoi(argv[1]);

  // the grid's x, y, and z dimensions EXCLUDING ghost cells
  nreals_x = atoi(argv[2]);
  nreals_y = atoi(argv[3]);
  nreals_z = atoi(argv[4]);

  numThreads = atoi(argv[5]);

  // grid padding in the z (unit-stride) dimension
  for (padding_z_param=0; padding_z_param<32; padding_z_param++) {
    if (my_proc_num == (job_num % num_procs)) {
      padding_z = padding_z_param;
      parameters_set = 1;
    }
    job_num++;
  }
  if (!parameters_set) {
    exit(EXIT_SUCCESS);
  }
//  padding_z = atoi(argv[6]);
  
  for (numCoreBlockCells_x_param=4; numCoreBlockCells_x_param <= 256; numCoreBlockCells_x_param*=2) {
      for (numCoreBlockCells_y_param=4; numCoreBlockCells_y_param <= 256; numCoreBlockCells_y_param*=2) {
	  for (numCoreBlockCells_z_param=256; numCoreBlockCells_z_param <= 256; numCoreBlockCells_z_param*=2) {
	      for (numCoreBlocksPerChunk_param=1; numCoreBlocksPerChunk_param <= ((nreals_x * nreals_y * nreals_z) / (numCoreBlockCells_x_param * numCoreBlockCells_y_param * numCoreBlockCells_z_param * numThreads)); numCoreBlocksPerChunk_param*=2) {
		  if (my_proc_num == (job_num % num_procs)) {
		      numCoreBlockCells_x = numCoreBlockCells_x_param;
		      numCoreBlockCells_y = numCoreBlockCells_y_param;
		      numCoreBlockCells_z = numCoreBlockCells_z_param;
		      numCoreBlocksPerChunk = numCoreBlocksPerChunk_param;
		      parameters_set = 1;
		  }
		  job_num++;
	      }
	  }
      }
  }
  if (!parameters_set) {
    exit(EXIT_SUCCESS);
  }
//  numCoreBlockCells_x = atoi(argv[7]);
//  numCoreBlockCells_y = atoi(argv[8]);
//  numCoreBlockCells_z = atoi(argv[9]);

//  numCoreBlocksPerChunk = atoi(argv[10]);

#if defined(COLLABORATIVE_THREADING)
  numThreadBlockCells_y = atoi(argv[11]);
  numThreadBlockCells_z = atoi(argv[12]);
#endif

#if defined(NONPERIODIC)
  ghostCellDepth = 1;
#endif
#if defined(PERIODIC)
  ghostCellDepth = numIter;
#endif

  nx = nreals_x + 2 * ghostCellDepth;
  ny = nreals_y + 2 * ghostCellDepth;
  nz = nreals_z + 2 * ghostCellDepth + padding_z;
  
  numCells = nx * ny * nz;

  A = (CALC_DATA_TYPE *) malloc(2 * numCells * sizeof(CALC_DATA_TYPE));

  if (A==NULL) {
    printf("Error on array A (and B) malloc.\n");
    exit(EXIT_FAILURE);
  }

  B = &A[numCells];

  numCoreBlocks_x = nreals_x/numCoreBlockCells_x;
  numCoreBlocks_y = nreals_y/numCoreBlockCells_y;
  numCoreBlocks_z = nreals_z/numCoreBlockCells_z;

#if defined(COLLABORATIVE_THREADING)
  numThreadBlocks_y = nreals_y/numThreadBlockCells_y;
  numThreadBlocks_z = nreals_z/numThreadBlockCells_z;

  numThreadBlocksPerCoreBlock_y = numCoreBlockCells_y/numThreadBlockCells_y;
  numThreadBlocksPerCoreBlock_z = numCoreBlockCells_z/numThreadBlockCells_z;
  numThreadBlocksPerCoreBlock = numThreadBlocksPerCoreBlock_y * numThreadBlocksPerCoreBlock_z;
#endif

  // compute loop bounds for "real" grid (excludes ghost cells)
  realMin_x = ghostCellDepth;
  realMin_y = ghostCellDepth;
  realMin_z = ghostCellDepth;
  realMax_x = realMin_x + nreals_x;
  realMax_y = realMin_y + nreals_y;
  realMax_z = realMin_z + nreals_z;
}

void free_grids() {
  free(A);
}

void init_grids(int32_t rank) {
#if defined(NUMA_AWARE)
  int32_t cbi, cbj, cbk, cbn;
#if !defined(COLLABORATIVE_THREADING)
  int32_t coreBlock[3], coreBlockMin[3], coreBlockMax[3];

  cbn = 0;

  for (cbi=0; cbi < numCoreBlocks_x; cbi++) {
    for (cbj=0; cbj < numCoreBlocks_y; cbj++) {
      for (cbk=0; cbk < numCoreBlocks_z; cbk++) {
	if (((cbn/numCoreBlocksPerChunk) % numThreads) == rank) {
	  coreBlock[0] = cbi;
	  coreBlock[1] = cbj;
	  coreBlock[2] = cbk;
	  coreBlockMin[0] = realMin_x + coreBlock[0] * numCoreBlockCells_x;
	  coreBlockMax[0] = coreBlockMin[0] + numCoreBlockCells_x;
	  coreBlockMin[1] = realMin_y + coreBlock[1] * numCoreBlockCells_y;
	  coreBlockMax[1] = coreBlockMin[1] + numCoreBlockCells_y;
	  coreBlockMin[2] = realMin_z + coreBlock[2] * numCoreBlockCells_z;
	  coreBlockMax[2] = coreBlockMin[2] + numCoreBlockCells_z;

	  init_blocks(coreBlock, coreBlockMin, coreBlockMax);

#if defined(DEBUG)
	  printf("Thread %d: coreBlock = [%d, %d, %d]\n", rank, coreBlock[0], coreBlock[1], coreBlock[2]);
	  printf("Thread %d: coreBlockMin = [%d, %d, %d]\n", rank, coreBlockMin[0], coreBlockMin[1], coreBlockMin[2]);
	  printf("Thread %d: coreBlockMax = [%d, %d, %d]\n", rank, coreBlockMax[0], coreBlockMax[1], coreBlockMax[2]);
#endif
	}
	cbn++;
      }
    }
  }
#else
  int32_t threadBlock[3], threadBlockMin[3], threadBlockMax[3];
  int32_t tbj, tbk, tbn;

  cbn = 0;

  for (cbi=0; cbi < numCoreBlocks_x; cbi++) {
    threadBlock[0] = cbi;
    threadBlockMin[0] = realMin_x + threadBlock[0] * numCoreBlockCells_x;
    threadBlockMax[0] = threadBlockMin[0] + numCoreBlockCells_x;
    for (cbj=0; cbj < numCoreBlocks_y; cbj++) {
      for (cbk=0; cbk < numCoreBlocks_z; cbk++) {
	if (((cbn/numCoreBlocksPerChunk) % (numThreads/numThreadBlocksPerCoreBlock)) == (rank/numThreadBlocksPerCoreBlock)) {
	  tbn = 0;
	  
	  for (tbj=0; tbj < numThreadBlocksPerCoreBlock_y; tbj++) {
	    for (tbk=0; tbk < numThreadBlocksPerCoreBlock_z; tbk++) {
              if ((rank % numThreadBlocksPerCoreBlock) == tbn) {
		threadBlock[1] = cbj * numThreadBlocksPerCoreBlock_y + tbj;
		threadBlock[2] = cbk * numThreadBlocksPerCoreBlock_z + tbk;
		threadBlockMin[1] = realMin_y + threadBlock[1] * numThreadBlockCells_y;
		threadBlockMax[1] = threadBlockMin[1] + numThreadBlockCells_y;
		threadBlockMin[2] = realMin_z + threadBlock[2] * numThreadBlockCells_z;
		threadBlockMax[2] = threadBlockMin[2] + numThreadBlockCells_z;

		init_blocks(threadBlock, threadBlockMin, threadBlockMax);

#if defined(DEBUG)
		printf("Thread %d: threadBlock = [%d, %d, %d]\n", rank, threadBlock[0], threadBlock[1], threadBlock[2]);
		printf("Thread %d: threadBlockMin = [%d, %d, %d]\n", rank, threadBlockMin[0], threadBlockMin[1], threadBlockMin[2]);
		printf("Thread %d: threadBlockMax = [%d, %d, %d]\n", rank, threadBlockMax[0], threadBlockMax[1], threadBlockMax[2]);
#endif
	      }
	      tbn++;
	    }
	  }
	}
	cbn++;
      }
    }
  }
#endif
#else
  int32_t i, j, k;

  if (rank == 0) {
    for (i=0; i < nx; i++) {
      for (j=0; j < ny; j++) {
	for (k=0; k < nz; k++) {
	  A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	  B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	}
      }
    }

    for (i=realMin_x; i < realMax_x; i++) {
      for (j=realMin_y; j < realMax_y; j++) {
	for (k=realMin_y; k < realMax_z; k++) {
	  A[Index3D(i,j,k)] = INIT_REAL_VALUE;
	}
      }
    }
  }
#endif
}

#if defined(NUMA_AWARE)
void init_blocks(int32_t *block, int32_t *blockMin, int32_t *blockMax) {
  int32_t numBlocks_y, numBlocks_z;
  int32_t i, j, k;
#if !defined(COLLABORATIVE_THREADING)
  numBlocks_y = numCoreBlocks_y;
  numBlocks_z = numCoreBlocks_z;
#else
  numBlocks_y = numThreadBlocks_y;
  numBlocks_z = numThreadBlocks_z;
#endif

  for (i=blockMin[0]; i < blockMax[0]; i++) {
    for (j=blockMin[1]; j < blockMax[1]; j++) {
      for (k=blockMin[2]; k < blockMax[2]; k++) {
	A[Index3D(i,j,k)] = INIT_REAL_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  if (block[0] == 0) {
    i=blockMin[0]-1;
    for (j=blockMin[1]; j < blockMax[1]; j++) {
      for (k=blockMin[2]; k < blockMax[2]; k++) {
	A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  if (block[0] == (numCoreBlocks_x-1)) {
    i=blockMax[0];
    for (j=blockMin[1]; j < blockMax[1]; j++) {
      for (k=blockMin[2]; k < blockMax[2]; k++) {
	A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  if (block[1] == 0) {
    j=blockMin[1]-1;
    for (i=blockMin[0]; i < blockMax[0]; i++) {
      for (k=blockMin[2]; k < blockMax[2]; k++) {
	A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  if (block[1] == (numBlocks_y-1)) {
    j=blockMax[1];
    for (i=blockMin[0]; i < blockMax[0]; i++) {
      for (k=blockMin[2]; k < blockMax[2]; k++) {
	A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  if (block[2] == 0) {
    k=blockMin[2]-1;
    for (i=blockMin[0]; i < blockMax[0]; i++) {
      for (j=blockMin[1]; j < blockMax[1]; j++) {
	A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  if (block[2] == (numBlocks_z-1)) {
    k=blockMax[2];
    for (i=blockMin[0]; i < blockMax[0]; i++) {
      for (j=blockMin[1]; j < blockMax[1]; j++) {
        A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
        B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }
}
#endif

void print_grid_parameters() {
  char temp_str[20];

  strcpy(output_str, "numa aware (0=false, 1=true) = ");
#if !defined(NUMA_AWARE)
  strcat(output_str, "0; ");
#else
  strcat(output_str, "1; ");
#endif
  strcat(output_str, "num iter = ");
  sprintf(temp_str, "%d; ", numIter);
  strcat(output_str, temp_str);
  strcat(output_str, "full grid size = ");
  sprintf(temp_str, "%d, %d, %d; ", nx, ny, nz);
  strcat(output_str, temp_str);
  strcat(output_str, "real grid size = ");
  sprintf(temp_str, "%d, %d, %d; ", (realMax_x-realMin_x), (realMax_y-realMin_y), (realMax_z-realMin_z));
  strcat(output_str, temp_str);
  strcat(output_str, "num threads = ");
  sprintf(temp_str, "%d; ", numThreads);
  strcat(output_str, temp_str);
  strcat(output_str, "padding size = ");
  sprintf(temp_str, "0, 0, %d; ", padding_z);
  strcat(output_str, temp_str);
  strcat(output_str, "core block size = ");
  sprintf(temp_str, "%d, %d, %d; ", numCoreBlockCells_x, numCoreBlockCells_y, numCoreBlockCells_z);
  strcat(output_str, temp_str);
  strcat(output_str, "num core blocks per chunk = ");
  sprintf(temp_str, "%d; ", numCoreBlocksPerChunk);
  strcat(output_str, temp_str);
#if defined(COLLABORATIVE_THREADING)
  strcat(output_str, "thread block size = ");
  sprintf(temp_str, "%d, %d, %d; ", numCoreBlockCells_x, numThreadBlockCells_y, numThreadBlockCells_z);
  strcat(output_str, temp_str);
#endif
}

#if defined(DEBUG)
void print_grid(CALC_DATA_TYPE *C) {
  int32_t x_planeCount;
  int32_t i, j, k;

  x_planeCount = 0;

  for (i=0; i < nx; i++) {
    printf("\n\nx-plane count = %d", x_planeCount);
    x_planeCount++;
    for (j=0; j < ny; j++) {
      printf("\n");
      for (k=0; k < nz; k++) {
	printf("%lf\t", C[Index3D(i,j,k)]);
      }
    }
  }
  printf("\n");
}
#endif
