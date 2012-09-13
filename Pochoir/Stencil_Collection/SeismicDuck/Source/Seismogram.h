//******************************************************************************
// Seismogram layer for Seismic Duck
// 
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

enum SeismogramKind {
    SK_CONTINUOUS,
    SK_SQUIGGLE
};

void SeismogramUpdateDraw( const NimblePixMap& map, NimbleRequest request, ColorFunc colorFunc, bool autogain );
void SeismogramReset( int width, int height );
