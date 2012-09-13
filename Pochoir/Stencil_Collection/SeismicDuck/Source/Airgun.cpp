//******************************************************************************
// Airgun physics for Seismic Duck
// 
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#include "AssertLib.h"
#include "Airgun.h"
#include "Wavefield.h"
#include "Widget.h"
#include <cmath>

using namespace std;

const int AirgunPulseSizeMax = 256;
static int AirgunPulseSize = 0;
static float AirgunPulse[AirgunPulseSizeMax];
static int AirgunCounter = AirgunPulseSizeMax;
static int AirgunX;
static int AirgunY;
GraphMeter AirgunMeter(PANEL_MIN_WIDTH-36,100);

void AirgunInitialize( const AirgunParameters& parameters) {
	AirgunMeter.setLimits(-80000,80000);
	int j=-1;
    for( int i=0; i<AirgunPulseSizeMax; ++i ) {
        double t = (i-AirgunPulseSizeMax/2)*0.075*parameters.frequency;
		double value = 0;
		switch( parameters.pulseKind ) {
		    case APK_square: value = -1<=t && t<=1; break;
			case APK_gaussian: value = exp(-0.5*t*t); break;
			case APK_gaussian_slope: value = -t*exp(-0.5*t*t); break;
			case APK_ricker: value = (1-t*t)*exp(-0.5*t*t); break;
		}
		if( j<0 && fabs(value)>=0.001 ) 
			j=0;
        if( j>=0 )
			// The 100 was found by trial and error.  The intent is to have a big enough
			// amplitude that reflections show nicely.
			AirgunPulse[j++] = float(25*SAMPLE_CLUT_SIZE*parameters.amplitude*value);
    }
    AirgunPulseSize=j;
}

void AirgunFire( int x, int y ) {
	if( AirgunCounter<AirgunPulseSize ) 
		// Ignore attempt to prematurely fire airgun
		return;
    AirgunCounter = 0;
    AirgunY = y;
    AirgunX = x;
	WavefieldSetImpulseLocation(x,y);
}

float AirgunGetImpulse( float rockFactor ) {
 	float a = 0;
    if( AirgunCounter<AirgunPulseSize )  {
        Assert( AirgunCounter<=sizeof(AirgunPulse)/sizeof(AirgunPulse[0]));
		a = AirgunPulse[AirgunCounter++]*powf(rockFactor,-1.5f)*0.1f;
    }
	AirgunMeter.update(a);
	return a;
}