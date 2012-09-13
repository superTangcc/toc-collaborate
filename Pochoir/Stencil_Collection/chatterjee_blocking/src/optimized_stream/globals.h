//#define DEBUG

// number of trials
#define NUM_TRIALS 5

// alignment of thread arrays (e.g. KB-aligned=0x400, MB-aligned=0x100000)
#define ARRAY_ALIGNMENT 0x400

// initial grid values
#if defined(DEBUG)
#define INIT_READ_VALUE 4.0
#define INIT_WRITE_VALUE 0.0
#else
#define INIT_READ_VALUE 4.0
#define INIT_WRITE_VALUE 0.0
#endif

// constants
#define NUM_BYTES_PER_DOUBLE 8
