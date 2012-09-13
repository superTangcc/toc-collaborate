/*
 *  file :  papi_util.h
 *  desc :  Slightly higher-level interface for PAPI.
 *
 *  Best viewed with tabstop=4.
 *
 *  $Header: /project/eecs/demmel/d/bebop/cvs_repo/chatterjee_blocking/papi/papi_util.h,v 1.11 2007/11/01 04:59:56 kdatta Exp $
 */

#include <papi.h>
#include "globals.h"
#if !defined(INC_PAPI_UTIL_H)
#define MAX_FILENAME_SIZE 1024
#if PAPI_VERSION_NUM == 3
#include <papiStdEventDefs.h>
#endif

/*
 *  PAPI_event_set_wrapper_t   W;
 *
 *  This structure is a wrapper for a PAPI event set W.set
 *  consisting of *one* PAPI event, and the event's associated
 *  descriptive data (name, string description, event code,
 *  ...).
 *
 */
typedef struct tagPAPI_event_set_wrapper_t
{
    int     set;       // event set id
#if PAPI_VERSION_NUM == 2
    PAPI_preset_info_t  info;  // event code information
#elif PAPI_VERSION_NUM == 3
    PAPI_event_info_t  info;  // event code information
#endif
} PAPI_event_set_wrapper_t;


void papi_enum_event_codes( int** p_event_codes, int* p_num_codes );
	/*
	 *  papi_enum_event_codes( &event_codes, &num_codes );
	 *
	 *  Input  : (none)
	 *  Output : event_codes, num_codes
	 *
	 *    Enumerates all PAPI event codes that are valid for the
	 *  current processor. Returns the number of such codes in
	 *  num_codes, and the list of the codes in
	 *  event_codes[0..num_codes-1].
	 */


void papi_filter_events( const int* event_codes, int num_codes,
	PAPI_event_set_wrapper_t** p_event_sets, int* p_num_sets );
	/*
	 *  papi_filter_events( events, num_events, &event_sets, &num_sets );
	 *
	 *  Input  : events, num_events
	 *  Output : event_sets, num_sets
	 *
	 *    Given a list of desired event codes (event_codes[0..num_codes-1]),
	 *  determines which correspond to legal events on the current
	 *  processor. Returns both the number of legal events in num_sets,
	 *  and a newly created batch of corresponding event sets
	 *  (event_sets[0..num_sets-1]).
	 */


void papi_init( const int* desired_events, int num_events,
	PAPI_event_set_wrapper_t** p_event_sets, int* p_num_sets );
	/*
	 *  papi_init( desired_events, num_events, &event_sets, &num_sets );
	 *
	 *  Input  : desired_events, num_events
	 *  Output : event_sets, num_sets
	 *
	 *    Initializes the PAPI system. The caller may specify a list
	 *  of event codes to monitor in the input array
	 *  desired_events[0..num_events-1]. This routine determines which
	 *  event codes are actually available for the given processor, and
	 *  allocates an array of new event sets, event_sets[0..num_sets-1].
	 *
	 *  If no desired event codes are given (i.e., desired_events == NULL
	 *  or num_events == 0), then this routine will create event sets for
	 *  all available hardware counters.
	 */

#if PAPI_VERSION_NUM == 2
void make_counter_filename( const char* outdir,
		       const PAPI_preset_info_t* info, char* filename );

FILE * create_counter_file( const char* outdir, const PAPI_preset_info_t* info,
		     int num_trials, const char* matfile );

FILE * reopen_counter_file( const char* outdir, const PAPI_preset_info_t* info );

void append_counter_file( FILE* fp, int r, int c,
		     int iter, const double* measurements );

void close_counter_file( FILE* fp );
#endif

void print_papi_measurements(PAPI_event_set_wrapper_t* event_sets, double* measurements,
			int num_measurements);
        /*
         *  print_papi_measurements( event_sets, measurements,
         *                      num_measurements );
         *
         *    Prints out the measurements associated with event set
         *  event_sets.
         */

void papi_cleanup( PAPI_event_set_wrapper_t* event_sets, int num_sets );
	/*
	 *  papi_cleanup( event_sets, num_sets );
	 *
	 *    Deallocates the event sets event_sets[0..num_sets-1] and
	 *  shuts the PAPI system down.
	 */

/* -----------------------------------------------------------------
 *  PAPI_MAKE_MEASUREMENTS( &set, CODE, num_trials, results );
 *
 *  Input  : set, CODE, num_trials, results
 *  Output : results
 *
 *    Runs the code fragment, CODE, a number of times (num_trials),
 *  each time monitoring the event codes given by "set."
 *
 *  For each trial run k, 0 <= k < num_trials, the count for the
 *  event is returned in the element results[k]. Note that results
 *  must be a pre-allocated double precision array of
 *  length >= num_trials.
 */
#define PAPI_MAKE_MEASUREMENTS( set, CODE, num_trials, results ) { \
		long_long _counter; \
		int _i, _retval; \
		for( _i = 0; _i < num_trials; _i++ ) { \
                        init_grids(); \
                        flush_cache(); \
			if ((_retval = PAPI_start(set)) != PAPI_OK ) { \
			   fprintf( stderr, "*** %s Error starting PAPI counter on trial #%d. ***\n", PAPI_strerror(_retval), _i ); \
			   exit(EXIT_FAILURE); \
			} \
                        CODE; \
			if ((_retval = PAPI_stop(set, &_counter)) != PAPI_OK ) { \
			   fprintf( stderr, "*** %s Error stopping PAPI counter on trial #%d. ***\n", PAPI_strerror(_retval), _i ); \
			   exit(EXIT_FAILURE); \
			} \
			results[_i] = (double)_counter; \
		} \
	}


#endif


/*
 *  $Log: papi_util.h,v $
 *  Revision 1.11  2007/11/01 04:59:56  kdatta
 *  Adding appropriate files for pthreaded-papi code.
 *
 *  Revision 1.10  2007/08/04 22:19:42  kdatta
 *  Small change in naming of print function.
 *
 *  Revision 1.9  2007/06/12 17:06:32  kdatta
 *  Small changes in several files.
 *
 *  Revision 1.8  2007/06/12 00:17:25  kdatta
 *  Many small changes to the code- the largest one being that we print the interior values of the grid as a sanity check (for time skewing, naive, naive threads).
 *
 *  Revision 1.7  2007/05/10 05:28:42  kdatta
 *  Corrected the placement of the flush_cache call.
 *
 *  Revision 1.6  2006/05/10 23:09:52  kdatta
 *  Changed the code slightly to make the papi version 3 case work.
 *
 *  Revision 1.5  2006/05/10 22:26:43  kdatta
 *  Changed the files to allow for PAPI version 2 or 3, which needs to be specified in globals.h.
 *
 *
 *
 *  eof
 *
 */














