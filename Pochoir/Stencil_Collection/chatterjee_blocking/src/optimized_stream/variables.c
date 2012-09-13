#if !defined(DEBUG)
double *results;
#if defined(PAPI_ENABLED)
int num_desired = 10;
int desired_events[] = {PAPI_TOT_CYC, PAPI_TOT_INS, PAPI_FP_INS, PAPI_VEC_INS, PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM, PAPI_CA_SHR, PAPI_CA_CLN, PAPI_CA_ITV};
#endif
#endif

barrier_t my_barrier;
double median_counts_per_sec;

