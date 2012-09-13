double **phi_grids, **rhs_grids, **aCoef_grids, **bCoef0_grids, **bCoef1_grids, **bCoef2_grids, **lambda_grids;
uint32_t numGrids, niter;
uint32_t nx_rhs, ny_rhs, nz_rhs;
uint32_t numThreads, numThreadsPerGrid;
uint32_t nreals_z_rhs, padding_z;
uint32_t numCoreBlockCells_x, numCoreBlockCells_y, numCoreBlockCells_z;
uint32_t numCoreBlocks_x, numCoreBlocks_y, numCoreBlocks_z;
uint32_t numCoreBlocksPerChunk;

void malloc_grids(char *argv[]);
void free_grids(void);
void init_grids(uint32_t rank);
void print_grid_parameters(void);
#if defined(DEBUG)
void print_grid(double *grid, uint32_t dim_x, uint32_t dim_y, uint32_t dim_z);
#endif
