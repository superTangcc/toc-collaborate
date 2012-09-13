//******************************************************************************
// Reservoir model for Seismic Duck
//
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

//! Reservoir coordinate system uses u for horizonal and v for vertical.
/** The grid is coarser than the pixel (x,y) coordinates by factor RESERVOIR_SCALE.
    The origin is the upper left corner of the hidden border. */
const int RESERVOIR_U_MAX = (WAVEFIELD_VISIBLE_WIDTH_MAX+2*HIDDEN_BORDER_SIZE) / RESERVOIR_SCALE;
const int RESERVOIR_V_MAX = (WAVEFIELD_VISIBLE_HEIGHT_MAX+2*HIDDEN_BORDER_SIZE) / RESERVOIR_SCALE; 

//! Phase subscripts for ReservoirColumn::phase_top
enum ReservoirPhase {
    GAS=0,
    OIL=1,
    WATER=2,
    N_Phase = 3
};

const int H_MAX = RESERVOIR_U_MAX*RESERVOIR_SCALE;

struct ReservoirStats {
	//! Number of traps
	int numTrap;
	//! Amount of oil and gas, in grid blocks.
    int volume[2];
};

void ReservoirInitialize( ReservoirStats& stats, const Geology& geology );

//! Update reservoir and report how much fluid was extracted.
void ReservoirUpdate( float fluidExtracted[N_Phase] );

void ReservoirDraw( const NimblePixMap& map );

//! Select x coordinate to start drilling a new hole, or redrill an old hole.
/** If the x is close to an existing hole, then the old hole is used. 
    Returns x coordinate of the hole. */
int ReservoirStartHole( int x );

//! Returns how much hole became deeper. 
int ReservoirUpdateHole( int& y, int direction );

void ReservoirDrawHoles( NimblePixMap& subsurface ); 
