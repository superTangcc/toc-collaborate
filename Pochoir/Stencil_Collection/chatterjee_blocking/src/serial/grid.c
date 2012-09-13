double *A, *B;

int32_t numIter;
int32_t nx, ny, nz;
int32_t nreals_x, nreals_y, nreals_z;

// the REAL grid includes all non-ghost cells, but no ghost cells
// the max values are unattainable upper limits
int32_t realMin_x, realMin_y, realMin_z;
int32_t realMax_x, realMax_y, realMax_z;

int32_t numBlockCells_x, numBlockCells_y, numBlockCells_z;
int32_t numBlocks_x, numBlocks_y, numBlocks_z;

/* This function initializes global variables as well as the arrays */
void malloc_grids(char *argv[]) {
  int32_t numCells, ghostCellDepth;
  
  numIter = atoi(argv[1]);
  
  nreals_x = atoi(argv[2]);
  nreals_y = atoi(argv[3]);
  nreals_z = atoi(argv[4]);

  ghostCellDepth = 1;

  nx = nreals_x + 2 * ghostCellDepth;
  ny = nreals_y + 2 * ghostCellDepth;
  nz = nreals_z + 2 * ghostCellDepth;
  
  numCells = nx * ny * nz;
  
  numBlockCells_x = atoi(argv[5]);
  numBlockCells_y = atoi(argv[6]);
  numBlockCells_z = atoi(argv[7]);
  
  printf("numIter = \n%u,\n", numIter);
  printf("full grid size = \n%u, %u, %u,\n", nx, ny, nz);
  printf("real grid size = \n%u, %u, %u,\n", nreals_x, nreals_y, nreals_z);
  printf("cache block size = \n%u, %u, %u,\n", numBlockCells_x, numBlockCells_y, numBlockCells_z);

  A = (double *) malloc(2 * numCells * sizeof(double));

  if (A==NULL) {
    printf("Error on array A (and B) malloc.\n");
    exit(EXIT_FAILURE);
  }

  B = &A[numCells];

  numBlocks_x = nreals_x/numBlockCells_x;
  numBlocks_y = nreals_y/numBlockCells_y;
  numBlocks_z = nreals_z/numBlockCells_z;

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

void init_grids() {
  int32_t i, j, k;

  // initialize FULL arrays (with ghost cells)
  for (i=0; i < nx; i++) {
    for (j=0; j < ny; j++) {
      for (k=0; k < nz; k++) {
	A[Index3D(i,j,k)] = INIT_GHOST_VALUE;
	B[Index3D(i,j,k)] = INIT_GHOST_VALUE;
      }
    }
  }

  // initialize REAL arrays (only non-ghost cells)
  for (i=realMin_x; i < realMax_x; i++) {
    for (j=realMin_y; j < realMax_y; j++) {
      for (k = realMin_z; k < realMax_z; k++) {
	A[Index3D(i,j,k)] = INIT_REAL_VALUE;
      }
    }
  }
}

#ifdef DEBUG
void print_grid(double *C) {
  int32_t x_planeCount;
  int32_t i, j, k;

  x_planeCount = 0;

  for (i=0; i < nx; i++) {
    printf("\n\nx-plane count = %u", x_planeCount);
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
