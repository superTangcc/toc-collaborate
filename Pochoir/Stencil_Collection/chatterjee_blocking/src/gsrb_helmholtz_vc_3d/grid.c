/* This function initializes global variables as well as the arrays */
void malloc_grids(char *argv[]) {
  uint32_t g;

  // number of grids
  numGrids = atoi(argv[1]);

  // number of iterations
  niter = atoi(argv[2]);

  // the rhs grid's x, y, and z dimensions (z-dim is without padding)
  nx_rhs = atoi(argv[3]);
  ny_rhs = atoi(argv[4]);
  nreals_z_rhs = atoi(argv[5]);

  numThreads = atoi(argv[6]);
  numThreadsPerGrid = atoi(argv[7]);

  // grid padding in the z (unit-stride) dimension
  padding_z = atoi(argv[8]);

  numCoreBlockCells_x = atoi(argv[9]);
  numCoreBlockCells_y = atoi(argv[10]);
  numCoreBlockCells_z = atoi(argv[11]);

  numCoreBlocksPerChunk = atoi(argv[12]);

  nz_rhs = nreals_z_rhs + padding_z;
  numCoreBlocks_x = nx_rhs/numCoreBlockCells_x;
  numCoreBlocks_y = ny_rhs/numCoreBlockCells_y;
  numCoreBlocks_z = nreals_z_rhs/numCoreBlockCells_z;

  phi_grids = (double **) malloc(numGrids * sizeof(double *));
  rhs_grids = (double **) malloc(numGrids * sizeof(double *));
  aCoef_grids = (double **) malloc(numGrids * sizeof(double *));
  bCoef0_grids = (double **) malloc(numGrids * sizeof(double *));
  bCoef1_grids = (double **) malloc(numGrids * sizeof(double *));
  bCoef2_grids = (double **) malloc(numGrids * sizeof(double *));
  lambda_grids = (double **) malloc(numGrids * sizeof(double *));

  if ((phi_grids==NULL) || (rhs_grids==NULL) || (aCoef_grids==NULL) || (bCoef0_grids==NULL) || (bCoef1_grids==NULL) || (bCoef2_grids==NULL) || (lambda_grids==NULL)) {
    printf("Error on array of pointers to grids malloc.\n");
    exit(EXIT_FAILURE);
  }

  for (g=0; g < numGrids; g++) {
    phi_grids[g] = (double *) malloc((nx_rhs+2) * (ny_rhs+2) * (nz_rhs+2) * sizeof(double));
    rhs_grids[g] = (double *) malloc(nx_rhs * ny_rhs * nz_rhs * sizeof(double));
    aCoef_grids[g] = (double *) malloc(nx_rhs * ny_rhs * nz_rhs * sizeof(double));
    bCoef0_grids[g] = (double *) malloc((nx_rhs+1) * ny_rhs * nz_rhs * sizeof(double));
    bCoef1_grids[g] = (double *) malloc(nx_rhs * (ny_rhs+1) * nz_rhs * sizeof(double));
    bCoef2_grids[g] = (double *) malloc(nx_rhs * ny_rhs * (nz_rhs+1) * sizeof(double));
    lambda_grids[g] = (double *) malloc(nx_rhs * ny_rhs * nz_rhs * sizeof(double));

    if ((phi_grids[g]==NULL) || (rhs_grids[g]==NULL) || (aCoef_grids[g]==NULL) || (bCoef0_grids[g]==NULL) || (bCoef1_grids[g]==NULL) || (bCoef2_grids[g]==NULL) || (lambda_grids[g]==NULL)) {
      printf("Error on grids malloc.\n");
      exit(EXIT_FAILURE);
    }
  }
}

void free_grids() {
  uint32_t g;

  for (g=0; g < numGrids; g++) {
    free(phi_grids[g]);
    free(aCoef_grids[g]);
    free(bCoef0_grids[g]);
    free(bCoef1_grids[g]);
    free(bCoef2_grids[g]);
    free(lambda_grids[g]);
    free(rhs_grids[g]);
  }

  free(phi_grids);
  free(aCoef_grids);
  free(bCoef0_grids);
  free(bCoef1_grids);
  free(bCoef2_grids);
  free(lambda_grids);
  free(rhs_grids);
}

void init_grids(uint32_t rank) {
  double *phi, *rhs, *aCoef, *bCoef0, *bCoef1, *bCoef2, *lambda;
  uint32_t g, i, j ,k;

#if defined(NUMA_AWARE)
  uint32_t coreBlockMin_x, coreBlockMin_y, coreBlockMin_z, coreBlockMax_x, coreBlockMax_y, coreBlockMax_z;
  uint32_t cb_n, cb_i, cb_j, cb_k;

#if defined(DEBUG)
  printf("Thread %u initializes grids: ", rank);
#endif

  for (g=(rank/numThreadsPerGrid); g < numGrids; g+=(numThreads/numThreadsPerGrid)) {
#if defined(DEBUG)
    printf("%u, ", g);
#endif

    phi = (double *) phi_grids[g];
    rhs = (double *) rhs_grids[g];
    aCoef = (double *) aCoef_grids[g];
    bCoef0 = (double *) bCoef0_grids[g];
    bCoef1 = (double *) bCoef1_grids[g];
    bCoef2 = (double *) bCoef2_grids[g];
    lambda = (double *) lambda_grids[g];

    cb_n = 0;
    for (cb_i=0; cb_i < numCoreBlocks_x; cb_i++) {
      for (cb_j=0; cb_j < numCoreBlocks_y; cb_j++) {
        for (cb_k=0; cb_k < numCoreBlocks_z; cb_k++) {
          if (((cb_n/numCoreBlocksPerChunk) % numThreadsPerGrid) == (rank % numThreadsPerGrid)) {
            coreBlockMin_x = 1 + cb_i * numCoreBlockCells_x;
            coreBlockMax_x = coreBlockMin_x + numCoreBlockCells_x;
            coreBlockMin_y = 1 + cb_j * numCoreBlockCells_y;
            coreBlockMax_y = coreBlockMin_y + numCoreBlockCells_y;
            coreBlockMin_z = 1 + cb_k * numCoreBlockCells_z;
            coreBlockMax_z = coreBlockMin_z + numCoreBlockCells_z;

            for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
              for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
		for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		  rhs[Irhs(i,j,k)] = INIT_RHS_VALUE;
		  aCoef[IaCoef(i,j,k)] = INIT_ACOEF_VALUE;
		  lambda[Ilambda(i,j,k)] = INIT_LAMBDA_VALUE;
		  bCoef0[IbCoef0(i,j,k)] = INIT_BCOEF0_VALUE;
		  bCoef1[IbCoef1(i,j,k)] = INIT_BCOEF1_VALUE;
		  bCoef2[IbCoef2(i,j,k)] = INIT_BCOEF2_VALUE;
		}
	      }
	    }

	    if (cb_i == 0) {
	      i=coreBlockMin_x-1;
              for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
		for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		}
	      }
	    }

	    if (cb_i == (numCoreBlocks_x-1)) {
	      i=coreBlockMax_x;
              for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
		for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		  bCoef0[IbCoef0(i,j,k)] = INIT_BCOEF0_VALUE;
		}
	      }
	    }

	    if (cb_j == 0) {
	      j=coreBlockMin_y-1;
              for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
		for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		}
	      }
	    }

	    if (cb_j == (numCoreBlocks_y-1)) {
	      j=coreBlockMax_y;
              for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
		for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		  bCoef1[IbCoef1(i,j,k)] = INIT_BCOEF1_VALUE;
		}
	      }
	    }

	    if (cb_k == 0) {
	      k=coreBlockMin_z-1;
	      for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
		for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		}
	      }
	    }

	    if (cb_k == (numCoreBlocks_z-1)) {
	      k=coreBlockMax_z;
	      for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
		for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
		  phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
		  bCoef2[IbCoef2(i,j,k)] = INIT_BCOEF2_VALUE;
		}
	      }
	    }

	  }
	  cb_n++;
	}
      }
    }
  }
#if defined(DEBUG)
    printf("\n");
#endif
#else
  if (rank == 0) {
#if defined(DEBUG)
    printf("Thread 0 initializes grids: ");
#endif
    for (g=0; g < numGrids; g++) {
#if defined(DEBUG)
      printf("%u, ", g);
#endif

      phi = (double *) phi_grids[g];
      rhs = (double *) rhs_grids[g];
      aCoef = (double *) aCoef_grids[g];
      bCoef0 = (double *) bCoef0_grids[g];
      bCoef1 = (double *) bCoef1_grids[g];
      bCoef2 = (double *) bCoef2_grids[g];
      lambda = (double *) lambda_grids[g];
      
      for (i=0; i <= (nx_rhs+1); i++) {
	for (j=0; j <= (ny_rhs+1); j++) {
	  for (k=0; k <= (nreals_z_rhs+1); k++) {
	    phi[Iphi(i,j,k)] = INIT_PHI_VALUE;
	  }
	}
      }
      
      for (i=1; i <= nx_rhs; i++) {
	for (j=1; j <= ny_rhs; j++) {
	  for (k=1; k <= nreals_z_rhs; k++) {
	    rhs[Irhs(i,j,k)] = INIT_RHS_VALUE;
	    aCoef[IaCoef(i,j,k)] = INIT_ACOEF_VALUE;
	    lambda[Ilambda(i,j,k)] = INIT_LAMBDA_VALUE;
	  }
	}
      }
      
      for (i=1; i <= (nx_rhs+1); i++) {
	for (j=1; j <= ny_rhs; j++) {
	  for (k=1; k <= nreals_z_rhs; k++) {
	    bCoef0[IbCoef0(i,j,k)] = INIT_BCOEF0_VALUE;
	  }
	}
      }
      
      for (i=1; i <= nx_rhs; i++) {
	for (j=1; j <= (ny_rhs+1); j++) {
	  for (k=1; k <= nreals_z_rhs; k++) {
	    bCoef1[IbCoef1(i,j,k)] = INIT_BCOEF1_VALUE;
	  }
	}
      }
      
      for (i=1; i <= nx_rhs; i++) {
	for (j=1; j <= ny_rhs; j++) {
	  for (k=1; k <= (nreals_z_rhs+1); k++) {
	    bCoef2[IbCoef2(i,j,k)] = INIT_BCOEF2_VALUE;
	  }
	}
      }
    }
  }
#if defined(DEBUG)
    printf("\n");
#endif
#endif
}

void print_grid_parameters() {
  printf("numa aware (0=false, 1=true) = \n");
#if !defined(NUMA_AWARE)
  printf("0, \n");
#else
  printf("1, \n");
#endif
  printf("num grids = \n%u,\n", numGrids);
  printf("num iter = \n%u,\n", niter);
  printf("real rhs grid size = \n%u, %u, %u,\n", nx_rhs, ny_rhs, nreals_z_rhs);
  printf("full rhs grid size = \n%u, %u, %u,\n", nx_rhs, ny_rhs, nz_rhs);
  printf("num threads = \n%u,\n", numThreads);
  printf("num threads per grid = \n%u,\n", numThreadsPerGrid);
  printf("padding size = \n0, 0, %u,\n", padding_z);
  printf("core block size = \n%u, %u, %u,\n", numCoreBlockCells_x, numCoreBlockCells_y, numCoreBlockCells_z);
  printf("num core blocks per chunk = \n%u,\n", numCoreBlocksPerChunk);
}

#if defined(DEBUG)
void print_grid(double *grid, uint32_t dim_x, uint32_t dim_y, uint32_t dim_z) {
  uint32_t i, j, k;

  for (i=0; i < dim_x; i++) {
    printf("\n\nx_rhs-plane count = %u", i);
    for (j=0; j < dim_y; j++) {
      printf("\n");
      for (k=0; k < dim_z; k++) {
	printf("%lf\t", grid[Index3D(i,j,k)]);
      }
    }
  }
  printf("\n");
}
#endif
