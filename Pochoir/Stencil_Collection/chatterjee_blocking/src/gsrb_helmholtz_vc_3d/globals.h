#define Iphi(_i,_j,_k) (_k+(nz_rhs+2)*(_j+(ny_rhs+2)*(_i)))
#define Irhs(_i,_j,_k) ((_k-1)+nz_rhs*((_j-1)+ny_rhs*((_i-1))))
#define IaCoef(_i,_j,_k) ((_k-1)+nz_rhs*((_j-1)+ny_rhs*((_i-1))))
#define IbCoef0(_i,_j,_k) ((_k-1)+nz_rhs*((_j-1)+ny_rhs*((_i-1))))
#define IbCoef1(_i,_j,_k) ((_k-1)+nz_rhs*((_j-1)+(ny_rhs+1)*((_i-1))))
#define IbCoef2(_i,_j,_k) ((_k-1)+(nz_rhs+1)*((_j-1)+ny_rhs*((_i-1))))
#define Ilambda(_i,_j,_k) ((_k-1)+nz_rhs*((_j-1)+ny_rhs*((_i-1))))
#define Index3D(_i,_j,_k) (_k+dim_z*(_j+dim_y*(_i)))

// #define DEBUG
// #define THREAD_PROFILING

// number of trials
#define NUM_TRIALS 5

// NUMA-aware?
#define NUMA_AWARE

// initial grid values
#if defined(DEBUG)
#define INIT_PHI_VALUE 1.5
#define INIT_RHS_VALUE 2.0
#define INIT_ACOEF_VALUE 2.0
#define INIT_BCOEF0_VALUE 2.0
#define INIT_BCOEF1_VALUE 2.0
#define INIT_BCOEF2_VALUE 2.0
#define INIT_LAMBDA_VALUE 2.0
#else
#define INIT_PHI_VALUE 1.5
#define INIT_RHS_VALUE 2.0
#define INIT_ACOEF_VALUE 2.0
#define INIT_BCOEF0_VALUE 2.0
#define INIT_BCOEF1_VALUE 2.0
#define INIT_BCOEF2_VALUE 2.0
#define INIT_LAMBDA_VALUE 2.0
#endif
