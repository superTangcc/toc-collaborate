void stencil_per_thread_co_ar_fi_re_noFMA_no_0_1x1x1RB(int32_t rank) {
  CALC_DATA_TYPE * __restrict__ temp_ptr;
  int32_t coreBlockMin_x, coreBlockMin_y, coreBlockMin_z, coreBlockMax_x, coreBlockMax_y, coreBlockMax_z;
  int32_t cb_n, cb_i, cb_j, cb_k;
  int32_t i, j, k, t;

  const CALC_DATA_TYPE c0 = C0;
  const CALC_DATA_TYPE c1 = C1;

  CALC_DATA_TYPE * Read_start_unrestrict = A;
  CALC_DATA_TYPE * Write_start_unrestrict = B;

  const int32_t plane_size = ny * nz;

  for (t=0; t < numIter; t++) {
    CALC_DATA_TYPE * __restrict__ Read_start_restrict = Read_start_unrestrict;
    CALC_DATA_TYPE * __restrict__ Write_start_restrict = Write_start_unrestrict;
    cb_n = 0;

    for (cb_i=0; cb_i < numCoreBlocks_x; cb_i++) {
      for (cb_j=0; cb_j < numCoreBlocks_y; cb_j++) {
        for (cb_k=0; cb_k < numCoreBlocks_z; cb_k++) {
          if (((cb_n/numCoreBlocksPerChunk) % numThreads) == rank) {
            coreBlockMin_x = realMin_x + cb_i * numCoreBlockCells_x;
            coreBlockMax_x = coreBlockMin_x + numCoreBlockCells_x;
            coreBlockMin_y = realMin_y + cb_j * numCoreBlockCells_y;
            coreBlockMax_y = coreBlockMin_y + numCoreBlockCells_y;
            coreBlockMin_z = realMin_z + cb_k * numCoreBlockCells_z;
            coreBlockMax_z = coreBlockMin_z + numCoreBlockCells_z;
            for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
              for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
                int32_t i_m1_0_0 = Index3D(i-1,j,coreBlockMin_z);

                for (k=coreBlockMin_z; k < coreBlockMax_z; k++) {
                  Write_start_restrict[i_m1_0_0+plane_size] = c0 * (Read_start_restrict[i_m1_0_0+plane_size])
			 + c1 * (Read_start_restrict[i_m1_0_0] + Read_start_restrict[i_m1_0_0+plane_size-nz] + Read_start_restrict[i_m1_0_0+plane_size-1] + Read_start_restrict[i_m1_0_0+plane_size+1] + Read_start_restrict[i_m1_0_0+plane_size+nz] + Read_start_restrict[i_m1_0_0+2*plane_size]);

                  i_m1_0_0++;
                }
              }
            }
          }
          cb_n++;
        }
      }
    }
    temp_ptr = Read_start_unrestrict;
    Read_start_unrestrict = Write_start_unrestrict;
    Write_start_unrestrict = temp_ptr;

    // barrier after each iteration (except the last iteration)
    if (t < (numIter-1)) {
      barrier_wait(&my_barrier, rank);
    }
  }
}

void stencil_per_thread_co_ar_fi_re_noFMA_no_0_1x1x2RB(int32_t rank) {
  CALC_DATA_TYPE * __restrict__ temp_ptr;
  int32_t coreBlockMin_x, coreBlockMin_y, coreBlockMin_z, coreBlockMax_x, coreBlockMax_y, coreBlockMax_z;
  int32_t cb_n, cb_i, cb_j, cb_k;
  int32_t i, j, k, t;

  const CALC_DATA_TYPE c0 = C0;
  const CALC_DATA_TYPE c1 = C1;

  CALC_DATA_TYPE * Read_start_unrestrict = A;
  CALC_DATA_TYPE * Write_start_unrestrict = B;

  const int32_t plane_size = ny * nz;

  for (t=0; t < numIter; t++) {
    CALC_DATA_TYPE * __restrict__ Read_start_restrict = Read_start_unrestrict;
    CALC_DATA_TYPE * __restrict__ Write_start_restrict = Write_start_unrestrict;
    cb_n = 0;

    for (cb_i=0; cb_i < numCoreBlocks_x; cb_i++) {
      for (cb_j=0; cb_j < numCoreBlocks_y; cb_j++) {
        for (cb_k=0; cb_k < numCoreBlocks_z; cb_k++) {
          if (((cb_n/numCoreBlocksPerChunk) % numThreads) == rank) {
            coreBlockMin_x = realMin_x + cb_i * numCoreBlockCells_x;
            coreBlockMax_x = coreBlockMin_x + numCoreBlockCells_x;
            coreBlockMin_y = realMin_y + cb_j * numCoreBlockCells_y;
            coreBlockMax_y = coreBlockMin_y + numCoreBlockCells_y;
            coreBlockMin_z = realMin_z + cb_k * numCoreBlockCells_z;
            coreBlockMax_z = coreBlockMin_z + numCoreBlockCells_z;
            for (i=coreBlockMin_x; i < coreBlockMax_x; i++) {
              for (j=coreBlockMin_y; j < coreBlockMax_y; j++) {
                int32_t i_m1_0_0 = Index3D(i-1,j,coreBlockMin_z);

                for (k=coreBlockMin_z; k < (coreBlockMax_z-1); k+=2) {
                  Write_start_restrict[i_m1_0_0+plane_size] = c0 * (Read_start_restrict[i_m1_0_0+plane_size])
			 + c1 * (Read_start_restrict[i_m1_0_0] + Read_start_restrict[i_m1_0_0+plane_size-nz] + Read_start_restrict[i_m1_0_0+plane_size-1] + Read_start_restrict[i_m1_0_0+plane_size+1] + Read_start_restrict[i_m1_0_0+plane_size+nz] + Read_start_restrict[i_m1_0_0+2*plane_size]);

                  Write_start_restrict[i_m1_0_0+plane_size+1] = c0 * (Read_start_restrict[i_m1_0_0+plane_size+1])
			 + c1 * (Read_start_restrict[i_m1_0_0+1] + Read_start_restrict[i_m1_0_0+plane_size-nz+1] + Read_start_restrict[i_m1_0_0+plane_size] + Read_start_restrict[i_m1_0_0+plane_size+2] + Read_start_restrict[i_m1_0_0+plane_size+nz+1] + Read_start_restrict[i_m1_0_0+2*plane_size+1]);

                  i_m1_0_0 += 2;
                }
              }
            }
          }
          cb_n++;
        }
      }
    }
    temp_ptr = Read_start_unrestrict;
    Read_start_unrestrict = Write_start_unrestrict;
    Write_start_unrestrict = temp_ptr;

    // barrier after each iteration (except the last iteration)
    if (t < (numIter-1)) {
      barrier_wait(&my_barrier, rank);
    }
  }
}

