CALC_DATA_TYPE *A, *B;
int32_t numIter;

int32_t nx, ny, nz;

// the REAL grid includes all non-ghost cells, but no ghost cells
// the max values are unattainable upper limits
int32_t realMin_x, realMin_y, realMin_z;
int32_t realMax_x, realMax_y, realMax_z;

int32_t numCoreBlockCells_x, numCoreBlockCells_y, numCoreBlockCells_z;
int32_t numCoreBlocks_x, numCoreBlocks_y, numCoreBlocks_z;

int32_t padding_z;

int32_t numThreads;

int32_t numCoreBlocksPerChunk;

#if defined(COLLABORATIVE_THREADING)
int32_t numThreadBlockCells_y, numThreadBlockCells_z;
int32_t numThreadBlocks_y, numThreadBlocks_z;
int32_t numThreadBlocksPerCoreBlock_y, numThreadBlocksPerCoreBlock_z, numThreadBlocksPerCoreBlock;
#endif

void malloc_grids(char *argv[]);
void free_grids(void);
void init_grids(int32_t rank);
#if defined(NUMA_AWARE)
void init_blocks(int32_t *block, int32_t *blockMin, int32_t *blockMax);
#endif
void print_grid_parameters(void);
#if defined(DEBUG)
void print_grid(CALC_DATA_TYPE *C);
#endif
