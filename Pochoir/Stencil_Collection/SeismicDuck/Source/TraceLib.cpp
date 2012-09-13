#include "TraceLib.h"
#include <stdio.h>
#include <stdarg.h>

#if TRACING
static FILE * TraceFile;
static int TraceLines = 0;

void WriteToTraceFile( const char * filename, int line, const char * format, ... ) {
    if( !TraceFile ) {
    	TraceFile = fopen("trace.txt","w");
    }
    if( TraceLines<1000 ) {
        ++TraceLines;
        fprintf( TraceFile, "%s(%d): ", filename, line );
        va_list ap;
        va_start( ap, format );
        vfprintf( TraceFile, format, ap );
        va_end( ap );
        fprintf( TraceFile, "\n" );
        fflush( TraceFile );
    }
}
#endif /* TRACING */
