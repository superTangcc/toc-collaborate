//******************************************************************************
// Airgun physics for Seismic Duck
// 
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

//! Airgun signatures
enum AirgunPulseKind {
    APK_square,
    APK_gaussian,
    APK_gaussian_slope,
    APK_ricker,
	APK_N_SIGNATURE
};

class AirgunParameters {
public:
    AirgunPulseKind pulseKind;
    float frequency;
    float amplitude;
    AirgunParameters() :
        pulseKind(APK_gaussian),
        frequency(1.0f),
        amplitude(1.0f)
    {}
};

void AirgunInitialize( const AirgunParameters& parameters );
void AirgunFire( int x, int y );
float AirgunGetImpulse( float rockFactor );

class GraphMeter;
extern GraphMeter AirgunMeter;