1) Matteo's cache oblivious algorithm:
    a) Just simple 2D heat equation
    b) boundary:
    kernel() {
    /* kernel for a one single time step */
    if (x == 0 || x == X-1 || y == 0 || y == Y-1)
    {
      U(t+1,x,y) = 0.0;
    }
    else/**/
    U(t+1,x,y) =   DTDXDX * (U(t,x+1,y) - 2.0 * U(t,x,y) + U(t,x-1,y))
                 + DTDYDY * (U(t,x,y+1) - 2.0 * U(t,x,y) + U(t,x,y-1))
                 + U(t,x,y);
    }
    So, there's only 1 SArray involved, and its full area is the commonly overlapped region.

2) 3dfd:

    ds = 4 /* slope */
    It's a 3D, ds*2*3+1=25 point stencil
    each time cutting into space, it cuts into exactly NPIECES(=2) pieces.
    only 1 SArray gets involved!
    for this benchmark, they just directly exclude the boundary from computing,
    so they just start from (0, T,   
                             ds, 0, Nx-ds, 0, 
                             ds, 0, Ny-ds, 0,
                             ds, 0, Nz-ds, 0);
    void basecase(int t0, int t1,
              int x0, int dx0, int x1, int dx1,
              int y0, int dy0, int y1, int dy1,
              int z0, int dz0, int z1, int dz1 )
    {
      /* kernel for a one single time step 
       * in this kernel, it doesn't consider the boundary conditions
       * it seems it can be re-written by 'obase'
       */
      //printf("enter basecase\n");
      float c0 = coef[0], c1 = coef[1], c2 = coef[2], c3 = coef[3], c4 = coef[4];
      /* Nx, Ny, Nz are global variables which stores the size of each dimension
       */
      int Nxy = Nx * Ny;
      int sx2 = Nx * 2;
      int sx3 = Nx * 3;
      int sx4 = Nx * 4;
      int sxy2 = Nxy * 2;
      int sxy3 = Nxy * 3;
      int sxy4 = Nxy * 4;
      for(int t = t0; t < t1; ++t) {
        for(int z = z0; z < z1; ++z) {
          for(int y = y0; y < y1; ++y) {
        for(int x = x0; x < x1; ++x) {
          int s = z * Nxy + y * Nx + x;
          float *A_cur = &A[t & 1][s];
          float *A_next = &A[(t + 1) & 1][s];
          float div = c0 * A_cur[0]
            + c1 * ((A_cur[0 + 1] + A_cur[0 - 1])
                + (A_cur[0 + Nx] + A_cur[0 - Nx])
                + (A_cur[0 + Nxy] + A_cur[0 - Nxy]))
            + c2 * ((A_cur[0 + 2] + A_cur[0 - 2])
                + (A_cur[0 + sx2] + A_cur[0 - sx2])
                + (A_cur[0 + sxy2] + A_cur[0 - sxy2]))
            + c3 * ((A_cur[0 + 3] + A_cur[0 - 3])
                + (A_cur[0 + sx3] + A_cur[0 - sx3])
                + (A_cur[0 + sxy3] + A_cur[0 - sxy3]))
            + c4 * ((A_cur[0 + 4] + A_cur[0 - 4])
                + (A_cur[0 + sx4] + A_cur[0 - sx4])
                + (A_cur[0 + sxy4] + A_cur[0 - sxy4]));
          A_next[0] = 2 * A_cur[0] - A_next[0] + vsq[s] * div;
        }
          }
        }
        x0 += dx0; x1 += dx1;
        y0 += dy0; y1 += dy1;
        z0 += dz0; z1 += dz1;
      }
      //printf("exit basecase\n");
    }

3) Stencil_probe:
    a) It has some self-tuning facility: find_best_block.sh as following:

    for tj in 16 32 64 128 256 512
    do
        for ti in 16 32 64 128 256 512
        do
            echo "#define SIZE 512" > run.h
            echo "#define NUM_TRIALS 5" >> run.h
            echo "#define TI $ti" >> run.h
            echo "#define TJ $tj" >> run.h
            make blocked_probe
            ./probe > out-$ti\-$tj\.out
            echo "done with $ti $tj"
        done
    done

    It's mainly a 2D heat equation stencil.
    a 7 point stencil from Chombo's heattut example.
    In stencil probe, the cache oblivious code is the most naive serial
    version of cache oblivious code, it steps into the base case only when 
    (dt == 1 || dx*dy*dz < CUTOFF)
    Only 1 SArray gets involved.
    It doesn't deal with the boundary conditions, it just directly exclude it
    from the very begining:
      walk3(A, nx, ny, nz,
        0, timesteps,
        1, 0, nx-1, 0,
        1, 0, ny-1, 0,
        1, 0, nz-1, 0);

    This code implements the circular queue algorithm for stencil codes.
    Intermediate queues, each with three revolving planes, store temporary
    results until the final result is written to the target array.  Unlike
    the time skewing algorithm, this algorithm will perform redundant
    computation between adjacent slabs.
  
    NOTE: Only the cache block's y-dimension is used in this code; it
    specifies the size of the circular queue's y-dimension.  The grid's
    y-dimension needs to be a multiple of the cache block's y-dimension.

    This code implements the time skewing method.  The cache blocks need to be
    traversed in a specific order for the algorithm to work properly.

    They also have a cache-blocked version.

4) Seismic Duck:
    The basic stencil:
    /* M(i, j) and L(i, j) are read-only arrays */
    S(i, j) += (M(i, j+1) + M(i, j)) * (V(i, j+1) - V(i, j));
    T(i, j) += (M(i+1, j) + M(i, j)) * (V(i+1, j) - V(i, j));
    V(i, j) += L(i, j) * (S(i, j) - S(i, j-1) + T(i, j) - T(i-1, j))
    Boundary conditions: PML
