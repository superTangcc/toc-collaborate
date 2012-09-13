#include "NimbleDraw.h"
#include "ColorMatrix.h"

ColorMatrix::ColorMatrix( const char* resourceName ) : 
    BuiltFromResourcePixMap(resourceName),
	myColors(NULL),
	myHeight(0),
	myWidth(0)
{}

void ColorMatrix::buildFrom( const NimblePixMap& map ) {
	Assert(!myColors);
	int w = myWidth = map.width();
	int h = myHeight = map.height();
	myColors = new NimbleColor[myWidth*myHeight];
    for( int i=0; i<h; ++i )
		for( int j=0; j<w; ++j )
			myColors[i*w+j] = map.colorAt(j,i);
}


