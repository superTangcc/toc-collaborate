/* This function initializes global variables as well as the arrays */
void malloc_grids(char *argv[]) {
  int32_t numCells, ghostCellDepth;
  int32_t nreals_x, nreals_y, nreals_z;
  int32_t numOffAlignment_z;
  
  // number of iterations
  numIter = atoi(argv[1]);
  
  // the grid's x, y, and z dimensions EXCLUDING ghost cells
  nreals_x = atoi(argv[2]);
  nreals_y = atoi(argv[3]);
  nreals_z = atoi(argv[4]);

  numThreads = atoi(argv[5]);

  // amount each pencil is front-shifted in the z (unit-stride) dimension (must be <= padding_z)
  numOffAlignment_z = atoi(argv[6]);

  numCoreBlockCells_x = atoi(argv[7]);
  numCoreBlockCells_y = atoi(argv[8]);
  numCoreBlockCells_z = atoi(argv[9]);

  numCoreBlocksPerChunk = atoi(argv[10]);

#ifdef NONPERIODIC
  ghostCellDepth = 1;
#endif
#ifdef PERIODIC
  ghostCellDepth = numIter;
#endif

#if defined(SINGLE_PRECISION)
  switch ((nreals_z + 2 * ghostCellDepth) % 4) {
  case 0: padding_z = 4;
      break;
  case 1: padding_z = 3;
      break;
  case 2: padding_z = 6;
      break;
  case 3: padding_z = 5;
      break;
  }
#endif
#if defined(DOUBLE_PRECISION)
  if (numOffAlignment_z == 0) {
      switch ((nreals_z + 2 * ghostCellDepth) % 2) {
      case 0: padding_z = 2;
	  break;
      case 1: padding_z = 1;
	  break;
      }
  }
  else {
      switch ((nreals_z + 2 * ghostCellDepth) % 2) {
      case 0: padding_z = 0;
	  break;
      case 1: padding_z = 1;
	  break;
      }
  }
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
  
  // compute loop bounds for "real" grid (excludes ghost cells and pencil padding)
  realMin_x = ghostCellDepth;
  realMin_y = ghostCellDepth;
  realMin_z = ghostCellDepth;

#if defined(SINGLE_PRECISION)
  if (((uint64_t)&A[Index3D(1,1,1)] & (uint64_t)0xc) == (uint64_t)0x4) {
    realMin_z += (3 - numOffAlignment_z);
  }
  else if (((uint64_t)&A[Index3D(1,1,1)] & (uint64_t)0xc) == (uint64_t)0x8) {
    realMin_z += (2 - numOffAlignment_z);
  }
  else if (((uint64_t)&A[Index3D(1,1,1)] & (uint64_t)0xc) == (uint64_t)0xc) {
    realMin_z += (1 - numOffAlignment_z);
  }
#endif
#if defined(DOUBLE_PRECISION)
  if (((uint64_t)&A[Index3D(1,1,1)] & (uint64_t)0x8) == (uint64_t)0x8) {
    realMin_z += (1 - numOffAlignment_z);
  }
#endif

  realMax_x = realMin_x + nreals_x;
  realMax_y = realMin_y + nreals_y;
  realMax_z = realMin_z + nreals_z;
}

void free_grids() {
  free(A);
}

void init_grids(int32_t rank) {
#if defined(NUMA_AWARE)
  int32_t block[3], blockMin[3], blockMax[3];
  int32_t bi, bj, bk, bn;

  bn = 0;

  for (bi=0; bi < numCoreBlocks_x; bi++) {
    for (bj=0; bj < numCoreBlocks_y; bj++) {
      for (bk=0; bk < numCoreBlocks_z; bk++) {
	if (((bn/numCoreBlocksPerChunk) % numThreads) == rank) {
	  block[0] = bi;
	  block[1] = bj;
	  block[2] = bk;
	  blockMin[0] = realMin_x + block[0] * numCoreBlockCells_x;
	  blockMax[0] = blockMin[0] + numCoreBlockCells_x;
	  blockMin[1] = realMin_y + block[1] * numCoreBlockCells_y;
	  blockMax[1] = blockMin[1] + numCoreBlockCells_y;
	  blockMin[2] = realMin_z + block[2] * numCoreBlockCells_z;
	  blockMax[2] = blockMin[2] + numCoreBlockCells_z;

	  init_blocks(block, blockMin, blockMax);

#if defined(DEBUG)
	  printf("Thread %d: block = [%d, %d, %d]\n", rank, block[0], block[1], block[2]);
	  printf("Thread %d: blockMin = [%d, %d, %d]\n", rank, blockMin[0], blockMin[1], blockMin[2]);
	  printf("Thread %d: blockMax = [%d, %d, %d]\n", rank, blockMax[0], blockMax[1], blockMax[2]);
#endif
	}
	bn++;
      }
    }
  }
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
  int32_t i, j, k;

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

  if (block[1] == (numCoreBlocks_y-1)) {
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

  if (block[2] == (numCoreBlocks_z-1)) {
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
  printf("numa aware (0=false, 1=true) = \n");
#if !defined(NUMA_AWARE)
  printf("0, \n");
#else
  printf("1, \n");
#endif
  printf("numIter = \n%d,\n", numIter);
  printf("full grid size = \n%d, %d, %d,\n", nx, ny, nz);
  printf("real grid size = \n%d, %d, %d,\n", (realMax_x-realMin_x), (realMax_y-realMin_y), (realMax_z-realMin_z));
  printf("padding size (required) = \n0, 0, %d,\n", padding_z);
  printf("num threads = \n%d,\n", numThreads);
  printf("core block size = \n%d, %d, %d,\n", numCoreBlockCells_x, numCoreBlockCells_y, numCoreBlockCells_z);
  printf("num core blocks per chunk = \n%d\n", numCoreBlocksPerChunk);
}

#ifdef DEBUG
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
