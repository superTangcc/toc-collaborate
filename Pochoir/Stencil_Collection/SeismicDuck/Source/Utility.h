template<typename T>
inline T Min( T a, T b ) {
    return a<b ? a : b;
}

template<typename T>
inline T Max( T a, T b ) {
    return !(a<b) ? a : b;
}

template<typename T>
inline T Clip( T a, T b, T x ) {
	Assert(!(b<a));
	return x<a ? a : b<x ? b : x;
}

template<typename T>
inline void Swap( T& x, T& y ) {
	T tmp(x);
	x = y;
	y = tmp;
}

inline int Round( float x ) {
	x += x<0 ? -0.5f : 0.5f;	// FIXME add SSE version
	return int(x);
}

class NoCopy {
	NoCopy( const NoCopy& );
	void operator=( const NoCopy& );
public:
	NoCopy() {}
};



