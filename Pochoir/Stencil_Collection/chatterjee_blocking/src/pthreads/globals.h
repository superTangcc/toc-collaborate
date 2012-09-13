#define Index3D(_i,_j,_k) (_k+nz*(_j+ny*(_i)))

// #define DEBUG
// #define THREAD_PROFILING

// number of trials
#define NUM_TRIALS 5

// boundary conditions
#define NONPERIODIC
// #define PERIODIC

// NUMA-aware?
#define NUMA_AWARE

// stencil weights
#if defined(DEBUG)
#define C0 8.0
#define C1 7.0
#define C2 6.0
#define C3 5.0
#else
#define C0 8.0
#define C1 7.0
#define C2 6.0
#define C3 5.0
#endif

// initial grid values
#if defined(DEBUG)
#define INIT_REAL_VALUE 1.0
#define INIT_GHOST_VALUE 0.0
#else
#define INIT_REAL_VALUE 1.5
#define INIT_GHOST_VALUE 1.5
#endif
