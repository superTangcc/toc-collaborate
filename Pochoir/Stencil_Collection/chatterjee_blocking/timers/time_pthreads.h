/* -----------------------------------------------------------------
 *  GET_CLOCK_RATE( results, num_trials );
 *
 *  Input  : results, num_trials
 *  Output : results
 *
 *  Determines the clock rate of the processor.
 *  For each trial run k, 0 <= k < num_trials, the cycle count for
 *  the code is returned in the element results[k]. Note that
 *  results must be a pre-allocated double precision array of
 *  length >= num_trials.
 */
#ifdef CYCLE_TIME
#define GET_CLOCK_RATE( results, num_trials ) { \
		int _i; \
                uint64_t _t_start, _t_end; \
		for ( _i = 0; _i < num_trials; _i++ ) { \
                        _t_start = cycle_time(); \
                        sleep(1); \
                        _t_end = cycle_time(); \
			results[_i] = 1.0 * (_t_end-_t_start); \
		} \
	}
#endif

/* -----------------------------------------------------------------
 *  TIMER_MAKE_MEASUREMENTS( CODE, results, rank, num_trials );
 *
 *  Input  : CODE, results, rank, num_trials
 *  Output : results
 *
 *  Runs the code fragment, CODE, a number of times (num_trials).
 *  For each trial run k, 0 <= k < num_trials, the cycle count for
 *  the code is returned in the element results[k]. Note that
 *  results must be a pre-allocated double precision array of
 *  length >= num_trials.
 */
#ifdef CYCLE_TIME
#define TIMER_MAKE_MEASUREMENTS( CODE, results, rank, num_trials ) { \
		uint32_t _i; \
                uint64_t _t_start, _t_end; \
		for ( _i = 0; _i < num_trials; _i++ ) { \
                        init_grids(rank); \
                        flush_cache(); \
                        barrier_wait(&my_barrier, rank); \
                        _t_start = cycle_time(); \
                        CODE; \
                        _t_end = cycle_time(); \
			results[num_trials * rank + _i] = 1.0 * (_t_end-_t_start); \
		} \
	}
#else
#define TIMER_MAKE_MEASUREMENTS( CODE, results, rank, num_trials ) { \
		uint32_t _i; \
                double _t_start, _t_end; \
		for ( _i = 0; _i < num_trials; _i++ ) { \
                        init_grids(rank); \
                        flush_cache(); \
                        barrier_wait(&my_barrier, rank); \
                        _t_start = timer_time(); \
                        CODE; \
                        _t_end = timer_time(); \
			results[num_trials * rank + _i] = _t_end-_t_start; \
		} \
	}
#endif
