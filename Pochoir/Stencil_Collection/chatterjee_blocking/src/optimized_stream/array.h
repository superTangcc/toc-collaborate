double * AllArrays;
double *** Arrays;
uint32_t numThreads, numReadArraysPerThread, numWriteArraysPerThread, memoryFootprintInB, threadPaddingLength, threadArrayLength;

void malloc_arrays(char *argv[]);
void free_arrays(void);
void init_arrays(uint32_t rank);
void print_array_parameters(void);
#if defined(DEBUG)
void print_arrays(void);
#endif
