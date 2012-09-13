//******************************************************************************
// Wave physics for Seismic Duck
// 
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#include "ColorFunc.h"
#include "NimbleDraw.h"

class Geology;

enum RockType {
	Water,
    Sandstone,
    Shale,
	RockTypeMax = Shale
};

//! Initialize fields for wave simulation.
void WavefieldInitialize( const Geology& g );

//! Update the wavefield and/or draw it.
void WavefieldUpdateDraw( const NimblePixMap& map, NimbleRequest request, float showGeology, float showSeismic, ColorFunc colorFunc );

//! Copy values for use in seismogram.
void WavefieldCopySurface( float v[], int w );

/** Coordinates (x,y) are in the coordinate system of the "map" argument to WavefieldUpdateDraw. */
void WavefieldSetImpulseLocation( int x, int y );

int WavefieldGetPumpFactor();
void WavefieldSetPumpFactor( int d );
static const int PUMP_FACTOR_MAX = 5;
