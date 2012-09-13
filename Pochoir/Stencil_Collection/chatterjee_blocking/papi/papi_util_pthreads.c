#include "globals.h"
#include <assert.h>
#if PAPI_VERSION_NUM == 3
#include <papiStdEventDefs.h>
#include <errno.h>
#include <string.h>
#endif

#include "papi_util_pthreads.h"

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
void papi_enum_event_codes( int** p_event_codes, int* p_num_codes ) {
#if PAPI_VERSION_NUM == 2
    const PAPI_preset_info_t* events;
    
    assert( p_event_codes != NULL );
    assert( p_num_codes != NULL );
    
    *p_event_codes = NULL;
    *p_num_codes = 0;
    
    events = PAPI_query_all_events_verbose();
    if( events )
	{
	    int k, i;
	    
	    /* count number of available events */
	    
	    for( i = 0; i < PAPI_MAX_PRESET_EVENTS; i++ )
		{
		    if( events[i].avail )
			(*p_num_codes)++;
		}
	    
	    /* create and return list of available events */
	    
	    *p_event_codes = (int *)malloc( sizeof(int) * (*p_num_codes) );
	    
	    for( k = 0, i = 0; i < PAPI_MAX_PRESET_EVENTS; i++ )
		{
		    if( events[i].avail )
			{
			    (*p_event_codes)[k] = events[i].event_code;
			    k++;
			}
		}
	}
#elif PAPI_VERSION_NUM == 3
  int i, k;

  assert( p_event_codes != NULL );
  assert( p_num_codes != NULL );

  // look for the first PRESET event
  i = PAPI_PRESET_MASK;

  // count the number of available events
  do {
    if (PAPI_query_event(i) == PAPI_OK) {
      (*p_num_codes)++;
    }
  } while (PAPI_enum_event(&i, PAPI_ENUM_ALL) == PAPI_OK);

  *p_event_codes = (int *) malloc((*p_num_codes) * sizeof(int));

  i = PAPI_PRESET_MASK;  /* look for the first PRESET event */
  k = 0;
  
  // create and return list of available events
  do {
    if (PAPI_query_event(i) == PAPI_OK) {
      (*p_event_codes)[k] = i;
      k++;
    }
  } while (PAPI_enum_event(&i, PAPI_ENUM_ALL) == PAPI_OK);
#endif
}

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
void papi_filter_events( const int* event_codes, int num_codes,
	PAPI_event_set_wrapper_t** p_event_sets, int* p_num_sets ) {
#if PAPI_VERSION_NUM == 2
	int i, k;

	assert( p_event_sets != NULL );
	assert( p_num_sets != NULL );

	*p_num_sets = 0;
	for( i = 0; i < num_codes; i++ )
	{
		PAPI_preset_info_t info;
		PAPI_query_event_verbose( event_codes[i], &info );

		if( info.avail )
			(*p_num_sets)++;
	}

	if( *p_num_sets == 0 )
	{
		*p_event_sets = NULL;
		return;
	}

	*p_event_sets = (PAPI_event_set_wrapper_t *)
		malloc(
			sizeof(PAPI_event_set_wrapper_t) * (*p_num_sets)
		);
	assert( *p_event_sets != NULL );

	for( k = 0, i = 0; i < num_codes; i++ )
	{
		PAPI_query_event_verbose(
				event_codes[i], &((*p_event_sets)[k].info)
			);

		if( (*p_event_sets)[k].info.avail )
		{
			int* p_set = &( (*p_event_sets)[k].set );

			*p_set = PAPI_NULL;
			PAPI_create_eventset( p_set );
			PAPI_add_event( p_set, event_codes[i] );

			k++;
		}
	}
#elif PAPI_VERSION_NUM == 3
  int i, k;
  
  assert( p_event_sets != NULL );
  assert( p_num_sets != NULL );
  
  // determine number of valid event sets
  *p_num_sets = 0;
  for (i=0; i < num_codes; i++) {
    if (PAPI_query_event(event_codes[i]) == PAPI_OK) {
      (*p_num_sets)++;
    }
  }
  
  if( *p_num_sets == 0 ) {
    *p_event_sets = NULL;
    return;
  }
  
  *p_event_sets = (PAPI_event_set_wrapper_t *)
    malloc((*p_num_sets) * sizeof(PAPI_event_set_wrapper_t));
  
  assert( *p_event_sets != NULL );

  k = 0;

  // add valid event sets to p_event_sets
  for (i=0; i < num_codes; i++) {
    if (PAPI_query_event(event_codes[i]) == PAPI_OK) {
      PAPI_get_event_info(event_codes[i], &((*p_event_sets)[k].info));

      int* p_set = &((*p_event_sets)[k].set);
      k++;
      
      *p_set = PAPI_NULL;
      if (PAPI_create_eventset(p_set) != PAPI_OK) {
	fprintf(stderr, "*** Error creating PAPI eventset. ***\n");
	exit(1);
      }
      if (PAPI_add_event(*p_set, event_codes[i]) != PAPI_OK) {
	fprintf(stderr, "*** Error adding PAPI event. ***\n");
	exit(1);
      }
    }
  }
#endif
}

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
void papi_init( const int* desired_events, int num_events,
	PAPI_event_set_wrapper_t** p_event_sets, int* p_num_sets ) {
        int retval;

	assert( p_event_sets != NULL );
	assert( p_num_sets != NULL );
	assert( num_events >= 0 );

	/* initialize the PAPI library */
	retval = PAPI_library_init(PAPI_VER_CURRENT);
#if PAPI_VERSION_NUM == 2
	if( retval != PAPI_VER_CURRENT )
	{
		fprintf( stderr, "An error occurred while initializing PAPI.\n" );
		fprintf( stderr, "  (code = %d)\n", retval );
		exit( -1 );
	}
#elif PAPI_VERSION_NUM == 3
  if ( retval != PAPI_VER_CURRENT ) {
    fprintf( stderr, "An error occurred while initializing PAPI.\n" );
    fprintf( stderr, "Error: %s (code =%d)\n", PAPI_strerror(retval), retval);
    fprintf( stderr, "  Errno: %d\n", errno);
    fprintf( stderr, " %s\n", strerror(errno));
    exit( -1 );
  }
#endif

  /* create event sets for *legal* desired events */
  if ((num_events == 0) || (desired_events == NULL))
    {
      int* codes;
      int  num_codes;
      
      papi_enum_event_codes( &codes, &num_codes );
      papi_filter_events( codes, num_codes, p_event_sets, p_num_sets );
      free( codes );
    }
  else
    papi_filter_events( desired_events, num_events,
			p_event_sets, p_num_sets );

}

/*
 *  print_papi_measurements( event_sets, measurements, num_sets,
 *                      num_threads, num_measurements );
 *
 *    Prints out the measurements associated with event set
 *  event_sets.
 */
void print_papi_measurements(PAPI_event_set_wrapper_t* event_sets, double* measurements,
		   int num_sets, int num_threads, int num_measurements) {
  char EventName[PAPI_MAX_STR_LEN];
  uint32_t i, j, k;

  for (i=0; i < num_sets; i++) {
    PAPI_event_code_to_name(event_sets[i].info.event_code, EventName);
    printf("\n%s:\n", EventName);
    for (j=0; j < num_threads; j++) {
      printf("\nThread %u:\n", j);
      for (k=0; k < num_measurements; k++) {
	printf( "%g, ", measurements[i*num_threads*num_measurements+j*num_measurements+k] );
      }
    }
    printf("\n");
  }
}

/*
 *  papi_cleanup( event_sets, num_sets );
 *
 *    Deallocates the event sets event_sets[0..num_sets-1] and
 *  shuts the PAPI system down.
 */
void papi_cleanup( PAPI_event_set_wrapper_t* event_sets, int num_sets) {
#if PAPI_VERSION_NUM == 2
	int i;

	if( (event_sets == NULL) || (num_sets == 0) )
		return;

	for( i = 0; i < num_sets; i++ )
	{
		int* p_set = &(event_sets[i].set);
		PAPI_cleanup_eventset( p_set );
		PAPI_destroy_eventset( p_set );
	}

	PAPI_shutdown();
#elif PAPI_VERSION_NUM == 3
  int i;
  
  if( (event_sets == NULL) || (num_sets == 0) )
    return;
  
  for( i = 0; i < num_sets; i++ ) {
    int* p_set = &(event_sets[i].set);
    PAPI_cleanup_eventset( *p_set );
    PAPI_destroy_eventset( p_set );
  }
  
  PAPI_shutdown();
#endif
}

#if PAPI_VERSION_NUM == 2
void make_counter_filename( const char* outdir,
	const PAPI_preset_info_t* info, char* filename ) {
	if( outdir == NULL )
		sprintf( filename, "%s.dat", info->event_name );
	else
		sprintf( filename, "%s/%s.dat", outdir, info->event_name );
}

/*
 *  fp = create_counter_file( outdir, event_info, num_trials );
 *
 *    Creates an output file, fp, for an event described by
 *  event_info. "outdir" is the directory in which to create
 *  the file, and "num_trials" is the number of times the
 *  event will be executed.
 */
FILE * create_counter_file( const char* outdir, const PAPI_preset_info_t* info,
	int num_trials, const char* matfile ) {
	FILE* fp;
	char filename[MAX_FILENAME_SIZE];

	assert( info != NULL );
	assert( info->event_name != NULL );

	make_counter_filename( outdir, info, filename );

	fp = fopen( filename, "wt" );
	if( fp == NULL )
	{
		fprintf( stderr, "*** Can't open output file '%s' ***\n", filename );
		exit( 2 );
	}
	else
	{
		fprintf( stderr, "... recording event '%s' [%s] ...\n",
			info->event_label, info->event_name );
	}

	fprintf( fp, "%% ----------------------------------------- \n" );
	fprintf( fp, "%%   Matrix : %s\n", matfile );
	fprintf( fp, "%% ----------------------------------------- \n" );
	fprintf( fp, "%%    Event : %s\n", info->event_label );
	fprintf( fp, "%%          : %s\n", info->event_descr );
	fprintf( fp, "%%     Name : %s\n", info->event_name );
	fprintf( fp, "%%     Code : 0x%x\n", info->event_code );
	fprintf( fp, "%% Derived? : %s\n",
		(info->flags & PAPI_DERIVED) ? "Yes" : "No" );
	fprintf( fp, "%%    Notes : %s\n", info->event_note );
	fprintf( fp, "%%\n" );
	fprintf( fp, "%% Number of trials: %d\n", num_trials );
	fprintf( fp, "%%\n" );
	fprintf( fp, "%% r c trial_1 ... trial_k\n" );
	fprintf( fp, "%%\n" );

	return fp;
}

FILE * reopen_counter_file( const char* outdir, const PAPI_preset_info_t* info )
{
	FILE* fp;
	char filename[MAX_FILENAME_SIZE];

	assert( info != NULL );
	assert( info->event_name != NULL );

	make_counter_filename( outdir, info, filename );

	fp = fopen( filename, "at" );
	if( fp == NULL )
	{
		fprintf( stderr, "*** Can't open output file '%s' ***\n", filename );
		exit( 2 );
	}

	return fp;
}

void append_counter_file( FILE* fp, int r, int c,
	int iter, const double* measurements ) {
	int k;

	fprintf( fp, "%d %d", r, c );
	for( k = 0; k < iter; k++ )
	{
		fprintf( fp, " %g", measurements[k] );
	}
	fprintf( fp, "\n" );
}

void close_counter_file( FILE* fp ) {
	if( fp != NULL )
		fclose( fp );
}
#endif
