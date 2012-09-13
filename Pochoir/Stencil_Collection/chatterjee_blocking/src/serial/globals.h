#define Index3D(_i,_j,_k) (_k+nz*(_j+ny*(_i)))

// number of trials
#define NUM_TRIALS 5

// boundary conditions
#define NONPERIODIC
// #define PERIODIC

// debugging
// #define DEBUG

// stencil weights
#if defined(DEBUG)
#define S0 4.0
#define S1 2.0
#else
#define S0 2.5
#define S1 -0.25
#endif

// initial grid values
#if defined(DEBUG)
#define INIT_REAL_VALUE 1.0
#define INIT_GHOST_VALUE 0.0
#else
#define INIT_REAL_VALUE 1.5
#define INIT_GHOST_VALUE 1.5
#endif
