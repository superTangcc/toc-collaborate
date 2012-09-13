//! Interface to platform specific host services that can be called from game.

//! Return current absolute time in seconds.
/** Only differences between two calls are meaningful, because the definition
    of 0 is platform dependent. */
double HostClockTime();

//! Sleep until given absolute time is reached, and return actual absolute time.
double HostSleepUntil( double absoluteTime );

/** 0 = no limit
    1 = one per frame
    2 = every two frames */
void HostSetFrameIntervalRate( int limit );

//! Enumeration of keys corresponding to non-printing characters. 
enum {
	HOST_KEY_RETURN=0xD,
	HOST_KEY_ESCAPE=0x1B,
	HOST_KEY_LEFT = 256,
    HOST_KEY_RIGHT,
    HOST_KEY_UP, 
    HOST_KEY_DOWN,
};

//! Return true if specified key is down, false otherwise.
/** Use one of the HOST_KEY_* enumeration for keys that do not correspond to printable characters. */
bool HostIsKeyDown( int key );

//! Called by client game to either show (show=true) or hide (show=false) the cursor
void HostShowCursor( bool show );

void HostWarning(const char* message);

//! Request termination of the game.
void HostExit();