//******************************************************************************
// Two dimensional color table.
//
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#include "BuiltFromResource.h"
#include "NimbleDraw.h"

class ColorMatrix: BuiltFromResourcePixMap {
public:
	ColorMatrix( const char* resourceName );
	~ColorMatrix() {delete[] myColors;}
	int width() const {return myWidth;}
	int height() const {return myHeight;}
	NimbleColor* operator[]( int k ) const {
		Assert(k<height());
		return myColors+k*myWidth;
	}
private:
	/*override*/ void buildFrom( const NimblePixMap& map ); 
	void operator=( const ColorMatrix& );
	ColorMatrix( const ColorMatrix& );
	//! Array [*myHeight*myWidth] of colors
	NimbleColor* myColors;
	int myWidth;
	int myHeight;
};