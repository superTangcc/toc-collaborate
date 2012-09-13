//******************************************************************************
// Image with transparent portion
//
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#include "BuiltFromResource.h"

//! Compressed representation of bitmap with transparency.
class SpriteRep {
    //! Header for sequence of consecutive non-transparent NimblePixel.
    /** Assumed to have same alignment as a NimblePixel */
    struct header {	
        //! Length of pixels array.
        /** Zero for last item in sequence. */
        unsigned int length:10;			
        signed int x:10;
        /** Always non-decreasing for successive headers. */
        signed int y:10;
        //! Really a variable-length array.
        NimblePixel pixels[1];  
    };
    /** Data format consists of sequence of items.  Each item is a header followed by 
        header::length occurrences of NimblePixel. 
        NULL if not initialized. */
    header* myData;
public:
	SpriteRep() : myData(0) {}
	~SpriteRep() {operator delete(myData);}
	void buildFrom( const NimblePixMap& map, int top, int bottom, bool flip=false );
	void drawOn( const NimblePixMap& map, int x, int y ) const; 
};

class Sprite: public BuiltFromResourcePixMap {
public:
    Sprite( const char* resourceName, bool flip=false ) : 
	    BuiltFromResourcePixMap(resourceName),
		myFlip(flip)
	{}

	//! Draw sprite
	void drawOn( const NimblePixMap& map, int x, int y ) const {
		myRep.drawOn(map,x,y);
	}

    int width() const {return myWidth;}
    int height() const {return myHeight;}
private:
    short myWidth;
    short myHeight;
    SpriteRep myRep;
    const bool myFlip;
 	/*override*/ void buildFrom( const NimblePixMap& map );
};

class AnimatedSprite: public BuiltFromResourcePixMap {
public:
	AnimatedSprite( const char* resourceName, int frameHeight ) :
        BuiltFromResourcePixMap(resourceName),
		myFrameHeight(frameHeight),
		myNumFrames(0),
		myCurrentFrame(0),
		myRep(0)
	{}
    ~AnimatedSprite() {delete[] myRep;}

	int width() const {return myWidth;}

	//! Draw animated sprite
	void drawOn( const NimblePixMap& map, int x, int y ) const {
		myRep[myCurrentFrame].drawOn(map,x,y);
	}

	void update() {
		if(++myCurrentFrame>=myNumFrames) 
			myCurrentFrame=0;
	}

private:
	const short myFrameHeight;
	short myWidth;
	unsigned short myNumFrames;
	unsigned short myCurrentFrame;

	//! Pointer to SpriteRep[myNumFrames]
	SpriteRep* myRep;
    
 	/*override*/ void buildFrom( const NimblePixMap& map );
};

