#ifndef BuiltFromResource_H
#define BuiltFromResource_H

//******************************************************************************
// Resource layer for Seismic Duck
// 
// Copyright 2009-2010 Arch D. Robison
//******************************************************************************

class NimblePixMap;

class BuiltFromResourcePixMap {
	friend class HostResourceLoader;
	static BuiltFromResourcePixMap* theRoot;
	static BuiltFromResourcePixMap** theEnd;
    BuiltFromResourcePixMap* next;
    const char* const resourceName;
    void operator=( const BuiltFromResourcePixMap& );          //!< Deny assignment
    BuiltFromResourcePixMap( const BuiltFromResourcePixMap& ); //!< Deny copy construction
    virtual void buildFrom( const NimblePixMap& map ) = 0;
public:
    BuiltFromResourcePixMap( const char* resourceName_ );
};

#endif /* BuiltFromResource_H */