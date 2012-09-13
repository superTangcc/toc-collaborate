#pragma once
#ifndef GAME_H
#define GAME_H

#include "NimbleDraw.h"

#define HAVE_GAME_FILES 0

#if HAVE_GAME_FILES
#include "BitFile.h"
#endif /* HAVE_GAME_FILES */

//! Initialize game-specific data structures
/** Return true if successful, otherwise false. */
bool GameInitialize();

//! Called when user presses keyboard key
/** Should return true if game should exit. */
bool GameKeyDown( int key );

//! Draw a frame of the game onto map
void GameDrawFrame( NimblePixMap& map );

//! Return null-terminated string with name of game and version.
/** Defined by client. */
const char* GameTitle();

//! Called when mouse moves to new coordinate
void GameMouseMove( const NimblePoint& point );

//! Kth mouse button was pressed
void GameMouseButtonDown( const NimblePoint& point, int k );

//! Kth mouse buttom was released
void GameMouseButtonUp( const NimblePoint& point, int k );

//! Update game state
void GameUpdateDraw( NimblePixMap& map, NimbleRequest request );	

//! Called when main window has been resized or moved.
/** map contains the new size and position of the window. */
void GameResizeOrMove( NimblePixMap& map );
	
//! Called by host when game needs to process a message.
/** Should return false if game should quit. 
    Not called if USE_HOST_MENU_SYSTEM==0. */
bool GameCommand( int message );
	
const size_t GameSamplesPerSec = 44100;
typedef short GameSoundSample;
void GamePlaySound( GameSoundSample* begin, size_t length, float relativePitch );

#if HAVE_GAME_FILES

//! File that can be written
class GameOutFile: public OutBitFile {
    HANDLE hFile;
    /*override*/ void write( const void* buffer, size_t nbyte );
public:
    bool open();
    void close();
};

//! File that can be read
class GameInFile: public InBitFile {
    HANDLE hFile;
    /*override*/ size_t read( void* buffer, size_t nbyte );
public:
    bool open();
    void close();
};

#endif /* HAVE_GAME_FILES */

#endif /* GAME_H */

