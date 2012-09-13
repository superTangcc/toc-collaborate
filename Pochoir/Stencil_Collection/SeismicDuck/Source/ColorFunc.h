//******************************************************************************
// Color transfer functions for Seismic Duck
//
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#pragma once

#ifndef ColorFunc_H
#define ColorFunc_H

#include "Config.h"
#include "NimbleDraw.h"

//! Mapping of magnitudes onto colors
enum ColorFunc {
    CF_Linear,
    CF_Log,
    CF_SignOnly
};

void ColorFuncMakeClut( NimblePixel clut[SAMPLE_CLUT_SIZE], int rockType, const NimblePixMap& map, float showGeology, float showSeismic, ColorFunc colorFunc ); 

#endif /* ColorFunc_H */
