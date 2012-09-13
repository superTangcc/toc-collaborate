//******************************************************************************
// Resource layer for Seismic Duck
// 
// Copyright 2009-2010 Arch D. Robison
//******************************************************************************

#include "BuiltFromResource.h"
#include "AssertLib.h"

BuiltFromResourcePixMap* BuiltFromResourcePixMap::theRoot;
BuiltFromResourcePixMap** BuiltFromResourcePixMap::theEnd = &BuiltFromResourcePixMap::theRoot;

BuiltFromResourcePixMap::BuiltFromResourcePixMap( const char* resourceName_ ) : 
    resourceName(resourceName_) 
{
	Assert( theRoot||theEnd==&theRoot );
    *theEnd = this;
	theEnd = &this->next;
}
