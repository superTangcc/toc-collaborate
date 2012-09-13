//******************************************************************************
// Wave physics and rendering for Seismic Duck
// 
// Copyright 1996-2010 Arch D. Robison
//******************************************************************************

#include "Config.h"
#include "NimbleDraw.h"
#include "ColorMatrix.h"
#include "ColorFunc.h"
#include "Geology.h"
#include "Wavefield.h"
#include "Airgun.h"
#include "Utility.h"
#include "SSE.h"
#include "Parallel.h"
#include <cmath>
#include <cfloat>
#include <memory>

//! Set to 1 do show tile boundaries (for debugging only).
#define DRAW_TILES 0

//! Set to 1 to show the color scale (used only when writing documentation)
#define DRAW_COLOR_SCALE 0

#define OPTIMIZE_HOMOGENEOUS_TILES 1

static const int NUM_PANEL_MAX = 16;

//! Set to 1 if experimenting with tiles bigger than 7x508
#define ALLOW_BIG_TILES 0

//! Number of panels
static int NumPanel = 5;
static int PumpFactor = 3;

static int TileHeight = 7;    // Must be <= 15.
static int TileWidth = 16*7;  // Must be multiple of 4 and <= 4*63 

//! Size of damping region, in pixels.
const int DampSize = 16;

//! Amount of damping per pixel
const float DampFraction = 1.0f/8;

//! Velocity of various materials.
/** The product of LFunc[k]*MFunc[k] must not exceed 0.5, otherwise runaway positive feedback occurs. 
    The values here are correctly proportioned for water and shale.
	The sandstone values are fictionally the geomean of the values for water and shale. */
//                                           WATER SANDSTONE  SHALE
static const float MofRock[RockTypeMax+1] = {0.50f,  0.3536f, 0.25f};
static const float LofRock[RockTypeMax+1] = {0.25f,  0.7071f, 2.00f};

static int WavefieldWidth;

//! Equal to viewable height plus 1 for free surface plus DampSize for bottom PML region
/** Does not inlude overlap zones. */
static int WavefieldHeight;

//! Maximum allowed width of wavefield, including left and right PML regions.
static const int WavefieldWidthMax = HIDDEN_BORDER_SIZE+WAVEFIELD_VISIBLE_WIDTH_MAX+HIDDEN_BORDER_SIZE;

//! Maximum allowed hight of wavefield, including PML region on bottom.  
/** The 1 is for the top read-only row of grid points. 
    The 4*NUM_REGION_MAX is for the overlap zones between adjacent regions. */
static const int WavefieldHeightMax = 1+WAVEFIELD_VISIBLE_HEIGHT_MAX+HIDDEN_BORDER_SIZE+4*NUM_PANEL_MAX;

//! Array of rock types, with two bits per element.
static __declspec(align(64)) byte RockMap[WavefieldHeightMax][WavefieldWidthMax>>2];

typedef __declspec(align(64)) float FieldType[WavefieldHeightMax][WavefieldWidthMax];

static FieldType Vx, Vy, U, A, B;

//! "Psi" fields for left and right PML regions.  
static __declspec(align(64)) float Pl[WavefieldHeightMax][DampSize], Pr[WavefieldHeightMax][DampSize];

//! "Psi" field for bottom PML region.  
/** Overlaps left and right PML regions on corners. */
static __declspec(align(64)) float Pb[DampSize][WavefieldWidthMax];

typedef __declspec(align(64)) float SigmaType[DampSize];

//! Coefficients for Uniaxial Perfectly Matched Layer (UPML)
static SigmaType D0, D1, D2, D3, D4, D5;
static const float D6=1.0f-FLT_EPSILON;

static short PanelIOfYPlus1[WavefieldHeightMax];
static int PanelFirstY[NUM_PANEL_MAX+1];
static int PanelFirstI[NUM_PANEL_MAX];
static int PanelLastI[NUM_PANEL_MAX];

static int PanelSrcI[(2*PUMP_FACTOR_MAX+1)*(NUM_PANEL_MAX-1)];
static int PanelDstI[(2*PUMP_FACTOR_MAX+1)*(NUM_PANEL_MAX-1)];
static int PanelMoveCount;

static inline int TrapezoidFirstI( int p, int k ) {
	Assert( 0<=p && p<NumPanel );
	Assert( 0<=k && k<PumpFactor );
	return p==0 ? PanelFirstI[p] : PanelFirstI[p]-(PumpFactor-k);
}

static inline int TrapezoidLastI( int p, int k ) {
	Assert( 0<=p && p<NumPanel );
    Assert( 0<=k && k<PumpFactor );
	return p==NumPanel-1 ? PanelLastI[p] : PanelLastI[p]+(PumpFactor-1-k);
}

inline int IofY( int y ) {
	Assert( -1<=y && y<=WavefieldHeight );
    return PanelIOfYPlus1[y+1];
}

static int TopIofBottomRegion;
static int LeftJofRightRegion;

static void InitializePanelMap() {
	Assert(1<=PumpFactor && PumpFactor<=PUMP_FACTOR_MAX);
	int h = WavefieldHeight;
	int w = WavefieldWidth;
	PanelFirstY[0] = -1;
	for( int p=1; p<NumPanel; ++p )
	    PanelFirstY[p] = WavefieldHeight*p/NumPanel;
	PanelFirstY[NumPanel] = WavefieldHeight-1;
	Assert( 0<h && h<=WavefieldHeightMax ); // FIXME - account for panel boundaries
	Assert( 0<w && w<=WavefieldWidthMax );
	Assert( NumPanel<=NUM_PANEL_MAX );
	int i=0;
	for( int p=0; p<NumPanel; ++p ) {
		PanelFirstI[p] = i;
        for( int y=PanelFirstY[p]; y<PanelFirstY[p+1]; ++y )
			PanelIOfYPlus1[y+1] = i++;
		PanelLastI[p] = i;
		// Allocate separation zone
		i+=2*PUMP_FACTOR_MAX+1;
	}
	TopIofBottomRegion = PanelLastI[NumPanel-1]-DampSize;
	LeftJofRightRegion = w-DampSize; 
}

static void InitializeZoneTranfers() {
	// Compute panel boundary transfers
	int k = 0;
	for( int p=0; p<NumPanel-1; ++p ) {
		for( int d=0; d<PumpFactor; ++d ) {
			// Copy from start of panel p+1 to end of panel p
		    PanelSrcI[k] = PanelFirstI[p+1]+d;
			PanelDstI[k] = PanelLastI[p]+d;
			++k;
		}
		for( int d=0; d<PumpFactor; ++d ) {
			// Copy from end of panel p to start of panel p+1
            PanelSrcI[k] = PanelLastI[p]-d-1;
            PanelDstI[k] = PanelFirstI[p+1]-d-1;
            ++k;
		}
	}
	PanelMoveCount = k;
}

//! Initialize RockMap and related wavefield propagation coefficients.
static void InitializeRockMap( const Geology& g ) {
	int h = WavefieldHeight;
	int w = WavefieldWidth;
	Assert( 4<=WavefieldHeight && WavefieldHeight<=WavefieldHeightMax );
    Assert( 4<=WavefieldWidth && WavefieldWidth<=WavefieldWidthMax ); 

    static const RockType typeOfLayer[GEOLOGY_N_LAYER] = {Water,Shale,Sandstone,Shale};
	for( int y=1; y<h; ++y ) {
		int i = IofY(y);
        for( int j=0; j<w>>2; ++j ) {
            unsigned packed = 0;
            for( int k=0; k<4; ++k ) { 
				// It is "y-1" here because the geology indices run from 0 to h-1
				GeologyLayer layer = g.layer(j*4+k,y-1);
                unsigned r=typeOfLayer[layer];
				if( layer!=TOP_SHALE && layer!=BOTTOM_SHALE ) {
					int x = 42;
				}
                packed += r<<(2*k);
            }
            RockMap[i][j] = (unsigned char)packed;
        }
	}
}

//! Initialize wave field arrays.
static void InitializeFDTD() {
	int h = WavefieldHeight;
	int w = WavefieldWidth;

	// Vy at surface must be cleared because it is used for surface boundary condition.
	for( int j=0; j<w; ++j ) {
		Vy[0][j] = 0;
		Assert(Vx[0][j]==0);
		Assert(U[0][j]==0);
	}

	// Clear the FTDT fields.  The initial value for U is a bit of noise that 
    // prevents performance losses from denormal floating-point values.
	for( int y=0; y<h-1; ++y ) {
		int i = IofY(y);
		for( int j=0; j<w; ++j ) {
			int r = RockMap[i][j>>2]>>(2*(j&3))&3;
			// Store M/2 in A, because we sum two A values to compute an average M.
            A[i][j] = MofRock[r]*0.5f;
            B[i][j] = LofRock[r]; 
			U[i][j] = sinf(i*.1f)*cosf(j*.1f)*1.E-6;
			Vx[i][j] = 0;
			Vy[i][j] = 0;
		}
	}
}

static inline float SigmaRamp( float k ) {
	const float kMax = (DampSize-0.5f);
	const float sigmaMax = .3f;
	Assert(k<=kMax);
	// Bring it on quadratically
	float s = k*k*(sigmaMax/(kMax*kMax));
	Assert(s<=sigmaMax);
	return s;
}

//! Initialize PML-related fields and coefficients.
static void InitializePML() {
 	int h = WavefieldHeight;
	int w = WavefieldWidth;

   // Clear left and right PML "psi".
	for( int y=0; y<h-1; ++y ) {
		int i = IofY(y);
        for( int j=0; j<DampSize; ++j )
            Pl[i][j] = Pr[i][j] = 0;
	}

    // Clear bottom PML "psi".
    for( int k=0; k<DampSize; ++k )
        for( int j=0; j<w; ++j )
            Pb[k][j] = 0;

    // Initialize UPML coefficients
	for( int k=0; k<DampSize; ++k ) {
		float s0 = SigmaRamp(k);
		float s1 = SigmaRamp(k+0.5f);
		D0[k] = (2-s0)/(2+s0);
		D1[k] = (2-s1)/(2+s1);
		D2[k] = 2/(2+s0);
		D3[k] = 2/(2+s1);
        D4[k] = s0;
        D5[k] = s1;
	}
}

static void ReplicateZones( bool all ) {
	int w = WavefieldWidth;
	Assert(w>0);
	Assert(NumPanel>0);
 	for( int k=0; k<PanelMoveCount; ++k ) {
		int i0 = PanelSrcI[k];
		int i1 = PanelDstI[k];
		if( all ) {
			memcpy( A[i1], A[i0], w*sizeof(float) );
		    memcpy( B[i1], B[i0], w*sizeof(float) );
		}
		memcpy( U[i1], U[i0], w*sizeof(float) );
		memcpy( Vx[i1], Vx[i0], w*sizeof(float) );
		memcpy( Vy[i1], Vy[i0], w*sizeof(float) );
		memcpy( Pl[i1], Pl[i0], DampSize*sizeof(float) );
		memcpy( Pr[i1], Pr[i0], DampSize*sizeof(float) );
	}
}

enum TileTag {
#if OPTIMIZE_HOMOGENEOUS_TILES
	TT_HomogeneousInterior,
#endif /* OPTIMIZE_HOMOGENEOUS_TILES */
	TT_HeterogeneousInterior,
	TT_Top,
	TT_Left,
	TT_Right,
	TT_BottomLeft,
	TT_Bottom,
	TT_BottomRight,
	TT_NumTileTag
};

struct Tile {
#if ALLOW_BIG_TILES
	unsigned tag:3;
	unsigned iFirst:10;
	unsigned iLen:10;
	unsigned jFirstOver4:9;
	unsigned jLenOver4:9;
#else
	unsigned tag:3;
	unsigned iFirst:10;
	unsigned iLen:4;
	unsigned jFirstOver4:9;
	unsigned jLenOver4:6;
#endif
};

// Fixme - estimate way to high in practice, and theoretically too low
static const int NUM_TILE_MAX = WavefieldWidthMax*WavefieldHeightMax*PUMP_FACTOR_MAX;

static const Tile* PanelFirstTile[NUM_PANEL_MAX];
static const Tile* PanelLastTile[NUM_PANEL_MAX];
static Tile TileArray[NUM_TILE_MAX];
static Tile* TileEnd;

static inline TileTag Classify( int i, int j ) {
	Assert(1<=TopIofBottomRegion);
	Assert(DampSize<=LeftJofRightRegion);
	static const TileTag matrix[3][3] = {
		{TT_NumTileTag,TT_Top,                  TT_NumTileTag},
		{TT_Left,      TT_HeterogeneousInterior,TT_Right},
		{TT_BottomLeft,TT_Bottom,               TT_BottomRight}
	};
	return matrix[(1<=i)+(TopIofBottomRegion<=i)][(DampSize<=j)+(LeftJofRightRegion<=j)];
}

#if ASSERTIONS
static void CheckTiles( int p ) {
	Assert(sizeof(Tile)==4);
    static unsigned char TileDepth[WavefieldHeightMax][WavefieldWidthMax];
	int i0 = TrapezoidFirstI(p,0); 
	int i1 = TrapezoidLastI(p,0);
	for( int i=i0; i<i1; ++i )
		for( int j=0; j<WavefieldWidth; ++j )
			TileDepth[i][j]=0;
    const Tile* tFirst = PanelFirstTile[p];
	const Tile* tLast = PanelLastTile[p];
	for( const Tile* ptr=tFirst; ptr<tLast; ++ptr ) {
		Tile t = *ptr;
		int iFirst = t.iFirst;
		int iLast = iFirst+t.iLen;
		int jFirst = t.jFirstOver4*4;
		int jLast = jFirst+t.jLenOver4*4;
		Assert( i0<=iFirst );
		Assert( iLast<=i1 );
		Assert( 0<=jFirst );
		Assert( jLast<=WavefieldWidth );
		for( int i=iFirst; i<iLast; ++i ) {
			int j0 = i==0 ? DampSize : 0;
			int j1 = i==0 ? WavefieldWidth-DampSize : WavefieldWidth;
			for( int j=jFirst; j<jLast; ++j ) { 
			    Assert( Classify(i,j)<TT_NumTileTag );
				int d = TileDepth[i][j];
				Assert( d<PumpFactor );
				Assert( TrapezoidFirstI(p,d)<=i );
				Assert( i<TrapezoidLastI(p,d) );
				if( TrapezoidFirstI(p,d)<i ) 
					Assert( i-1==0 || TileDepth[i-1][j]==d+1 );
				if( i+1<TrapezoidLastI(p,d) )
					Assert(TileDepth[i+1][j]==d);
				if( j0<j )
					Assert(TileDepth[i][j-1]==d+1);
				if( j+1<j1 ) 
					Assert(d==TileDepth[i][j+1]);
				TileDepth[i][j] = d+1;
			}
		}
	}
	for( int i=i0; i<i1; ++i ) {
		// Compute correct depth of trapezoid
		int depth = 0;
		for( int k=0; k<PumpFactor; ++k )
			if( TrapezoidFirstI(p,k)<=i && i<TrapezoidLastI(p,k) )
				++depth;
		// Check that trapezoid is tiled to correct depth.
		for( int j=0; j<WavefieldWidth; ++j ) 
			if( i!=0 || (DampSize<=j && j<WavefieldWidth-DampSize ) )
			    Assert( TileDepth[i][j]==depth );
	}
}
#endif /* ASSERTIONS */

static bool IsHomogeneous( int iFirst, int iLast, int jFirst, int jLast ) {
	// Load values that are used for a homogenous tile.
    float a = A[iFirst][jFirst];
	float b = B[iFirst][jFirst];
	for( int i=iFirst; i<iLast; ++i )
		for( int j=jFirst; j<jLast; ++j )
			// Check that values that would be loaded for a heterogenous tile match.
			if( A[i][j]!=a || A[i+1][j]!=a || A[i][j+1]!=a || B[i][j]!=b )
				return false;
	return true;
}

static void AddTile( int iFirst, int iLast, int jFirst, int jLast ) {
	// Caller is responsible for ensuring that tile is non-empty.
	Assert( iFirst<iLast );
	Assert( jFirst<jLast );
	// Caller is responsible for ensuring that tile is in bounds
	Assert( 0<=iFirst && iLast<=TopIofBottomRegion+DampSize );
	Assert( 0<=jFirst && jLast<=WavefieldWidth );
	TileTag tag = Classify(iFirst,jFirst);
#if ASSERTIONS
	// Caller is responsible for ensuring that tile has uniform tag.
	for( int i=iFirst; i<iLast; ++i )
		for( int j=jFirst; j<jLast; ++j )
			Assert(tag==Classify(i,j));
#endif /* ASSERTIONS */
	if( tag==TT_NumTileTag ) return;
#if OPTIMIZE_HOMOGENEOUS_TILES
	if( tag==TT_HeterogeneousInterior )
		if( IsHomogeneous( iFirst, iLast, jFirst, jLast ) )
            tag = TT_HomogeneousInterior;
#endif /* OPTIMIZE_HOMOGENEOUS_TILES */
	Tile t;
	t.tag=tag;
	Assert(t.tag==tag);
	t.iFirst=iFirst;
	Assert(t.iFirst==iFirst);
	t.iLen=iLast-iFirst;
	Assert(t.iFirst+t.iLen==iLast);
	t.jFirstOver4=jFirst/4;
	Assert(t.jFirstOver4*4==jFirst);
	t.jLenOver4=(jLast-jFirst)/4;
	Assert(4*t.jFirstOver4+4*t.jLenOver4==jLast);
	Assert( TileEnd<TileArray+NUM_TILE_MAX );
	*TileEnd++ = t;
}

static void SplitHorizontal( int iFirst, int iLast, int jFirst, int jLast ) {
 	Assert( iFirst<iLast );
	Assert( jFirst<jLast );
	if( jFirst<DampSize && DampSize<jLast ) {
		AddTile( iFirst, iLast, jFirst, DampSize );
		AddTile( iFirst, iLast, DampSize, jLast );
	} else if( jFirst<LeftJofRightRegion && LeftJofRightRegion<jLast ) {
		AddTile( iFirst, iLast, jFirst, LeftJofRightRegion );
		AddTile( iFirst, iLast, LeftJofRightRegion, jLast );
	} else {
		AddTile( iFirst, iLast, jFirst, jLast );
	}
}

static void SplitVertical( int iFirst, int iLast, int jFirst, int jLast ) {
    Assert( DampSize<=TopIofBottomRegion ); 
	if( iFirst<iLast && jFirst<jLast ) {
		if( iFirst<1 && 1<iLast ) {
			SplitHorizontal( iFirst, 1, jFirst, jLast );
			SplitHorizontal( 1, iLast, jFirst, jLast );
		} else if( iFirst<TopIofBottomRegion && TopIofBottomRegion<iLast ) {
			SplitHorizontal( iFirst, TopIofBottomRegion, jFirst, jLast );
			SplitHorizontal( TopIofBottomRegion, iLast, jFirst, jLast );
		} else {
			SplitHorizontal( iFirst, iLast, jFirst, jLast );
		}
	}
}

static void MakeTilesForPanel( int p ) {
	Assert(TileWidth%4==0);
	PanelFirstTile[p] = TileEnd;
	int w = WavefieldWidth;
	int d = PumpFactor-1;
	int i0=TrapezoidFirstI(p,0);
	int i1=TrapezoidLastI(p,0);
	for( int i=i0; i-d<i1; i+=TileHeight ) 
		for( int j=0; j-4*d<w; j+=TileWidth )
			for( int k=0; k<=d; ++k )
				SplitVertical( Max(i-k,TrapezoidFirstI(p,k)), Min(i-k+TileHeight,TrapezoidLastI(p,k)),
					           Max(j-4*k,0), Min(j-4*k+TileWidth,w) );
    PanelLastTile[p] = TileEnd;
#if ASSERTIONS
	CheckTiles(p);
#endif /* ASSERTIONS */
}

static void InitializeTiles() {
	TileEnd=TileArray;
	for( int p=0; p<NumPanel; ++p ) {
		int yFirst=PanelFirstY[p];
		int yLast=PanelFirstY[p+1];
		if( p>0 ) yFirst-=PumpFactor;
		if( p+1<NumPanel ) yLast+=PumpFactor-1;
		MakeTilesForPanel(p);
	}
}

void WavefieldInitialize( const Geology& g ) {
	WavefieldHeight = g.height()+1;
	WavefieldWidth = g.width();
	InitializePanelMap();
    InitializeRockMap(g);
	InitializeFDTD();
    InitializePML();
	InitializeZoneTranfers();
	ReplicateZones(/*all=*/true);
	InitializeTiles();
}

int WavefieldGetPumpFactor() {return PumpFactor;}

void WavefieldSetPumpFactor( int d ) {
	Assert(1<=d && d<=PUMP_FACTOR_MAX);
	if( PumpFactor!=d ) {
		PumpFactor = d;
		InitializeZoneTranfers();
		ReplicateZones(/*all=*/true);
 	    InitializeTiles();  
	}
}

static int AirgunY, AirgunX;
static float AirgunImpulseValue[PUMP_FACTOR_MAX];
static int AirgunImpulseCounter[NUM_PANEL_MAX];

void WavefieldSetImpulseLocation( int x, int y ) {
	AirgunY = y;
    AirgunX = x;
}

#if USE_SSE
#define CAST(x) (*(__m128*)&(x))        /* for aligned load or store */
#define LOAD(x) _mm_loadu_ps(&(x))      /* for unaligned load */
//#define STORE(y,a) _mm_store_ps(&(y),a)
#define ADD _mm_add_ps
#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#endif /* USE_SSE */


static void WavefieldUpdatePanel( int p ) {
	const int h = WavefieldHeight;
	const int w = WavefieldWidth; 
	const int topIofBottomRegion = TopIofBottomRegion;
	const int leftJofRightRegion = LeftJofRightRegion;
    const int airgunJ = AirgunX+HIDDEN_BORDER_SIZE;
    const int airgunI = (AirgunY-PanelFirstY[p])+PanelFirstI[p];
    const Tile* tFirst = PanelFirstTile[p];
	const Tile* tLast = PanelLastTile[p];
    for( const Tile* ptr=tFirst; ptr<tLast; ++ptr ) {
        Tile t = *ptr;
		int iFirst = t.iFirst;
		int iLast = iFirst+t.iLen;
		int jFirst = t.jFirstOver4*4;
		int jLast = jFirst+t.jLenOver4*4;
		switch( t.tag ) {
            case TT_Top:
				// Reflection boundary condition at top.
				Assert(iFirst==0);
				Assert(iLast==1);
				for( int j=jFirst; j<jLast; ++j ) {
					Assert(Vx[0][j]==0);
		            Assert(U[0][j]==0);
					Vy[0][j] += 4*A[1][j]*(U[1][j]/*-U[0][j]*/);
				}
				break;
			case TT_Left: 
				// Left border
				for( int i=iFirst; i<iLast; ++i ) {
					for( int j=jFirst, l=DampSize-1-jFirst; j<jLast; ++j, --l ) {
						// Uniaxial PML along X axis
						float u = U[i][j];		
						Vx[i][j] = D0[l]*Vx[i][j]+D2[l]*(A[i][j+1]+A[i][j])*(U[i][j+1]-u);	
						Vy[i][j] =       Vy[i][j]+      (A[i+1][j]+A[i][j])*(U[i+1][j]-u);
						U [i][j] = D1[l]*u       +B[i][j]*(D3[l]*((Vx[i][j]-Vx[i][j-1])+Pl[i][l]) + (Vy[i][j]-Vy[i-1][j]));	
						Pl[i][l] = D6   *Pl[i][l]+         D5[l]*                                   (Vy[i][j]-Vy[i-1][j]);
					}
				}
				break;
#if OPTIMIZE_HOMOGENEOUS_TILES
			case TT_HomogeneousInterior:  {
				// Interior
#if USE_SSE
                __m128 a = CAST(A[iFirst][jFirst]);
                a = ADD(a,a);
                __m128 b = CAST(B[iFirst][jFirst]); 
                for( int i=iFirst; i<iLast; ++i ) {
				    for( int j=jFirst; j<jLast; j+=4 ) {
                        __m128 u = CAST(U[i][j]);	
                        CAST(Vx[i][j]) = ADD(CAST(Vx[i][j]),MUL(a,SUB(LOAD(U[i][j+1]),u)));
                        CAST(Vy[i][j]) = ADD(CAST(Vy[i][j]),MUL(a,SUB(CAST(U[i+1][j]),u)));	
                        CAST(U[i][j]) = ADD(u,MUL(b,ADD(SUB(CAST(Vx[i][j]),LOAD(Vx[i][j-1])),SUB(CAST(Vy[i][j]),CAST(Vy[i-1][j])))));	
					}
				}
#else
#error NOT FINISHED
					float a = 2*A[i][jFirst];
					float b = B[i][jFirst];
					for( int j=jFirst; j<jLast; ++j ) {
						float u = U[i][j];
						Vx[i][j] += a*(U[i][j+1]-u);
						Vy[i][j] += a*(U[i+1][j]-u);
						U[i][j] = u + b*((Vx[i][j]-Vx[i][j-1])+(Vy[i][j]-Vy[i-1][j]));
					}
#endif
				break;
			}
#endif /* OPTIMIZE_HOMOGENEOUS_TILES */
			case TT_HeterogeneousInterior:
				// Interior
				for( int i=iFirst; i<iLast; ++i ) {
#if USE_SSE
					for( int j=jFirst; j<jLast; j+=4 ) {
						__m128 u = CAST(U[i][j]);	
						__m128 a = CAST(A[i][j]); 
						CAST(Vx[i][j]) = ADD(CAST(Vx[i][j]),MUL(ADD(LOAD(A[i][j+1]),a),SUB(LOAD(U[i][j+1]),u)));
						CAST(Vy[i][j]) = ADD(CAST(Vy[i][j]),MUL(ADD(CAST(A[i+1][j]),a),SUB(CAST(U[i+1][j]),u)));	
						CAST(U[i][j]) = ADD(u,MUL(CAST(B[i][j]),ADD(SUB(CAST(Vx[i][j]),LOAD(Vx[i][j-1])),SUB(CAST(Vy[i][j]),CAST(Vy[i-1][j])))));							
					}
#else
					for( int j=jFirst; j<jLast; ++j ) {
						float u = U[i][j];	
						Vx[i][j] += (A[i][j+1]+A[i][j])*(U[i][j+1]-u);	
						Vy[i][j] += (A[i+1][j]+A[i][j])*(U[i+1][j]-u);
						U [i][j] = u + B[i][j]*((Vx[i][j]-Vx[i][j-1]) + (Vy[i][j]-Vy[i-1][j]));	
					}
#endif
		        }
				break;
			case TT_Right:
				// PML region on right side.
				for( int i=iFirst; i<iLast; ++i ) {
					for( int j=jFirst, l=j-leftJofRightRegion; j<jLast; ++j, ++l ) {
						// Uniaxial PML along X axis
						float u = U[i][j];		
						Vx[i][j] = D1[l]*Vx[i][j]+D3[l]*(A[i][j+1]+A[i][j])*(U[i][j+1]-u);	
						Vy[i][j] =       Vy[i][j]+      (A[i+1][j]+A[i][j])*(U[i+1][j]-u);
						U [i][j] = D0[l]*u       +B[i][j]*(D2[l]*((Vx[i][j]-Vx[i][j-1])+Pr[i][l]) + (Vy[i][j]-Vy[i-1][j]));	
						Pr[i][l] = D6   *Pr[i][l]+         D4[l]*                                   (Vy[i][j]-Vy[i-1][j]);
					}
				}
				break;
			case TT_BottomLeft: 
				// PML region for bottom left corner.
				for( int i=iFirst, k=i-topIofBottomRegion; i<iLast; ++i, ++k ) {
					for( int j=jFirst, l=DampSize-1-jFirst; j<jLast; ++j, --l ) {
						Assert(0<=k && k<DampSize);
						// Uniaxial PML along X and Y axis
						float u = U[i][j];		
						Vx[i][j] = D0[l]*Vx[i][j]+D2[l]*(A[i][j+1]+A[i][j])*(U[i][j+1]-u);	
						Vy[i][j] = D1[k]*Vy[i][j]+D3[k]*(A[i+1][j]+A[i][j])*(U[i+1][j]-u);	
						U [i][j] = D0[k]*D1[l]*u       +B[i][j]*(D3[l]*((Vx[i][j]-Vx[i][j-1])+Pl[i][l]) + D2[k]*((Vy[i][j]-Vy[i-1][j])+Pb[k][j]));	
						Pb[k][j] = D6   *Pb[k][j]+D4[k]*(Vx[i][j]-Vx[i][j-1]);
						Pl[i][l] = D6   *Pl[i][l]+D5[l]*(Vy[i][j]-Vy[i-1][j]);	                         
					}
				}
				break;
			case TT_Bottom: 
				// PML region on bottom.
				for( int i=iFirst, k=i-topIofBottomRegion; i<iLast; ++i, ++k ) {
					for( int j=jFirst; j<jLast; ++j ) {
						Assert(0<=k && k<DampSize);
						Assert(A[i][j]!=0);
						// FIXME - does not damp very high frequencies.
						// Uniaxial PML along Y axis
						float u = U[i][j];		
						Vx[i][j] =       Vx[i][j]+      (A[i][j+1]+A[i][j])*(U[i][j+1]-u);
						Vy[i][j] = D1[k]*Vy[i][j]+D3[k]*(A[i+1][j]+A[i][j])*(U[i+1][j]-u);	
						U [i][j] = D0[k]*u       +B[i][j]*((Vx[i][j]-Vx[i][j-1])+D2[k]*((Vy[i][j]-Vy[i-1][j])+Pb[k][j]));	
						Pb[k][j] = D6   *Pb[k][j]+D4[k]*   (Vx[i][j]-Vx[i][j-1]);
					}
				}
				break;
			case TT_BottomRight: {
				// PML region for bottom right corner.
				for( int i=iFirst, k=i-topIofBottomRegion; i<iLast; ++i, ++k ) {
					for( int j=jFirst, l=j-leftJofRightRegion; j<jLast; ++j, ++l ) {
						Assert(0<=k && k<DampSize);
						// Uniaxial PML along X and Y axis
						float u = U[i][j];		
						Vx[i][j] = D1[l]*Vx[i][j]+D3[l]*(A[i][j+1]+A[i][j])*(U[i][j+1]-u);	
						Vy[i][j] = D1[k]*Vy[i][j]+D3[k]*(A[i+1][j]+A[i][j])*(U[i+1][j]-u);	
						U [i][j] = D0[k]*D0[l]*u       +B[i][j]*(D2[l]*((Vx[i][j]-Vx[i][j-1])+Pr[i][l]) + D2[k]*((Vy[i][j]-Vy[i-1][j])+Pb[k][j]));	
						Pb[k][j] = D6   *Pb[k][j]+D4[k]*(Vx[i][j]-Vx[i][j-1]);
						Pr[i][l] = D6   *Pr[i][l]+D4[l]*(Vy[i][j]-Vy[i-1][j]);	        
					}
				}
				break;
			}
	    }
		if( iFirst<=airgunI && airgunI<iLast && jFirst<=airgunJ && airgunJ<jLast ) {
			Assert( 0<=AirgunImpulseCounter[p] && AirgunImpulseCounter[p]<PumpFactor );
		    U[airgunI][airgunJ] += AirgunImpulseValue[AirgunImpulseCounter[p]++];
		} 
	}
}

void WavefieldCopySurface( float* output, int w ) {
	Assert(w==WavefieldWidth-2*HIDDEN_BORDER_SIZE);
	for( int j=HIDDEN_BORDER_SIZE; j<w+HIDDEN_BORDER_SIZE; ++j )
		*output++ = Vy[1][j];
}

static float WaveClutShowsGeology;
static float WaveClutShowsSeismic;
static ColorFunc WaveClutColorFunc;

static NimblePixel WaveClut[RockTypeMax+2][SAMPLE_CLUT_SIZE];

static void ComputeWaveClut( const NimblePixMap& map, float showGeology, float showSeismic, ColorFunc colorFunc ) {
	Assert(0<=showGeology && showGeology<=1);
	Assert(0<=showSeismic && showSeismic<=1);
    // Check against current CLUT
	if( showGeology==WaveClutShowsGeology && showSeismic==WaveClutShowsSeismic && colorFunc==WaveClutColorFunc ) 
		// Use existing CLUT
		return;
    
    // Need to recompute CLUT
	WaveClutShowsGeology = showGeology;
    WaveClutShowsSeismic = showSeismic;
    WaveClutColorFunc = colorFunc;
	for( int r=0; r<=RockTypeMax; ++r ) 
		ColorFuncMakeClut( WaveClut[r], r, map, showGeology, showSeismic, colorFunc ); 
}

static void WavefieldDrawPanel( int p, const NimblePixMap& map ) { 
    const int w = map.width();
    const int h = map.height();
    Assert( h>0 );
    Assert( w>=4 );
#if USE_SSE
	Assert( w%4==0 );
	const __m128 upperLimit=_mm_set_ps1(SAMPLE_CLUT_SIZE/2-1);
	const __m128 lowerLimit=_mm_set_ps1(-SAMPLE_CLUT_SIZE/2);
#else
	const float upperLimit=SAMPLE_CLUT_SIZE/2-1;
	const float lowerLimit=-SAMPLE_CLUT_SIZE/2;
#endif /* USE_SSE */

    const NimblePixel* clut = WaveClut[0]+SAMPLE_CLUT_SIZE/2;
	int firstY = Max(0,PanelFirstY[p]);
	int lastY = Min(PanelFirstY[p+1],h);
    for( int y=firstY; y<lastY; ++y ) {
		int i = IofY(y);
        const byte* rock = &RockMap[i][HIDDEN_BORDER_SIZE>>2];
#if USE_SSE
		const __m128* in = (__m128*)&U[i][HIDDEN_BORDER_SIZE];
#else
        const float* in = &U[i][HIDDEN_BORDER_SIZE];
#endif
        NimblePixel* out = (NimblePixel*)map.at(0,y);
#pragma ivdep
        for( int j=0; j<w; j+=4, ++rock ) {
            unsigned r = *rock<<SAMPLE_CLUT_LG_SIZE;
			const unsigned SUBCLUT_MASK = 3<<SAMPLE_CLUT_LG_SIZE;
#if USE_SSE 
			__m128 v = _mm_max_ps(_mm_min_ps(*in++,upperLimit),lowerLimit);
#define STEP(k) out[k] = clut[_mm_cvt_ss2si(_mm_shuffle_ps(v,v,k))+(r>>(2*k)&SUBCLUT_MASK)]
			STEP(0);
			STEP(1);
			STEP(2);
			STEP(3);
			out+=4;
#else
            for( int k=0; k<4; ++k ) {
                float v = *in++;
				if( v>upperLimit ) v=upperLimit;
				if( v<lowerLimit ) v=lowerLimit;
				int u=int(v)+(r&SUBCLUT_MASK);
                *out++ = clut[u];
                r>>=2;
            }
#endif
        }
    }
}

#if DRAW_TILES
static void WavefieldDrawTiles( int p, const NimblePixMap& map ) {
	const int h = WavefieldHeight;
	const int w = WavefieldWidth; 
	Assert(w==map.width()+2*HIDDEN_BORDER_SIZE);
	NimblePixel red = map.pixel( NimbleColor(255,0,0));
	NimblePixel yellow = map.pixel( NimbleColor(255,255,0));
	NimblePixel green = map.pixel( NimbleColor(0,255,0) );
	NimblePixel purple = map.pixel( NimbleColor(255,0,255) );

	for( int x=0; x<map.width(); x+=4 )
		*(NimblePixel*)map.at(x,PanelFirstY[1]) = purple;

    const Tile* tFirst = PanelFirstTile[p];
	const Tile* tLast = PanelLastTile[p];
	for( const Tile* ptr=tFirst; ptr<tLast; ++ptr ) {
		Tile t = *ptr;
		int iFirst = t.iFirst;
		int iLast = iFirst+t.iLen;
		int jFirst = t.jFirstOver4*4;
		int jLast = jFirst+t.jLenOver4*4;
		int yFirst=PanelFirstY[p]+(iFirst-PanelFirstI[p]);
		int yLast=PanelFirstY[p]+(iLast-PanelFirstI[p]);
		int xFirst=jFirst-HIDDEN_BORDER_SIZE;
		int xLast=jLast-HIDDEN_BORDER_SIZE;
		if( 0<=yFirst && yLast<=map.height() )
			if( 0<=xFirst && xLast<=map.width() ) {
			    NimblePixel pixel;
				switch( t.tag ) {
					default:
						pixel = red;
						break;
#if OPTIMIZE_HOMOGENEOUS_TILES
					case TT_HomogeneousInterior:
						pixel = green;
						break;
#endif /* OPTIMIZE_HOMOGENEOUS_TILES */
					case TT_HeterogeneousInterior:
						pixel = yellow;
				}
				for( int x=xFirst; x<xLast; ++x )
					*(NimblePixel*)map.at(x,yFirst) = pixel;
				for( int y=yFirst; y<yLast; ++y )
					*(NimblePixel*)map.at(xFirst,y) = pixel;
			}
	}
}
#endif /* DRAW_TILES */

#if PARALLEL
tbb::task_scheduler_init init;

class Loop {
	const NimblePixMap& map; 
	const NimbleRequest request;
public:
	void operator()( tbb::blocked_range<int> r ) const {
		for( int p=r.begin(); p!=r.end(); ++p ) {
		    if( request&NimbleUpdate ) 
				WavefieldUpdatePanel( p );    
			if( request&NimbleDraw ) { 
			    WavefieldDrawPanel( p, map );
#if DRAW_TILES
				WavefieldDrawTiles( p, map );
#endif /* DRAW_TILES */
			}
		}
	}
	Loop( const NimblePixMap& map_, NimbleRequest request_ ) : map(map_), request(request_) {}
};
#endif

#if DRAW_COLOR_SCALE
static void DrawColorScale( const NimblePixMap& map ) {
	int xScale = 3;
	int xLimit = Min(SAMPLE_CLUT_SIZE/xScale,map.width());
	for( int y=0; y<24; ++y ) {
		int i = y/6;
		for( int x=0; x<xLimit; ++x ) 
			*(NimblePixel*)map.at(x,y) = WaveClut[i][x*xScale];
	}
}
#endif /* DRAW_COLOR_SCALE */

void WavefieldUpdateDraw( const NimblePixMap& map, NimbleRequest request, float showGeology, float showSeismic, ColorFunc colorFunc ) {
	ComputeWaveClut( map, showGeology, showSeismic, colorFunc );
	if( request&NimbleUpdate ) {
		int i = IofY(AirgunY);
		int j = AirgunX+HIDDEN_BORDER_SIZE;
		float a = A[i][j];
		for( int k=0; k<PumpFactor; ++k )
			AirgunImpulseValue[k] = AirgunGetImpulse( a );
		for( int p=0; p<NumPanel; ++p )
			AirgunImpulseCounter[p] = 0;
	}
	ReplicateZones(/*all=*/false);
#if PARALLEL
	tbb::parallel_for( tbb::blocked_range<int>(0,NumPanel,1), Loop(map,request) );
#else
	for( int p=0; p<NumPanel; ++p ) {
		if( request&NimbleUpdate ) 
		    WavefieldUpdatePanel( p );    
	    if( request&NimbleDraw ) 
			WavefieldDrawPanel( p, map );
	}
#endif
#if DRAW_COLOR_SCALE
    if( request&NimbleDraw )
		DrawColorScale(map);
#endif /* DRAW_COLOR_SCALE */
}
