#ifndef _RMQ_n_1_alstrup_hpp_
#define _RMQ_n_1_alstrup_hpp_

#include "RMQ.hpp"
#include "RMQ_nlogn_1.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;

class RMQ_n_1_alstrup : public RMQ {
public:
	// liefert RMQ[i,j]
	virtual DTidx query(DTidx, DTidx);

	RMQ_n_1_alstrup(DT* a, DTidx n);

	~RMQ_n_1_alstrup();

protected:
	// array
	DT *a;

	// index array for the out-of-block queries (contains indices of block-minima)
	DTidx *c;

	// precomputed in-block queries
	DTidx* Prec;

	// size of array a
	DTidx n;

	// block size
	DTidx bs;

	// number of blocks (always n/bs)
	DTidx nb;

	// return block of entry i:
	inline DTidx block(DTidx i) { return i/bs; }

	/* clear the least significant x-1 bits */
	inline DTidx clearbits(DTidx n, DTidx x){
		return((n >> x) << x);
	}

	// Least Significant Bits for 8-bit-numbers:
	static const char LSBTable256[256];

	virtual DTidx lsb(DTidx);

// 	/*
// 	 * return position of least significant set bit. This will loop infinitely if n is 0. 
// 	 * This is not implemented here in constant time as it should be, but is usually fast
// 	 * enough in practice. 
// 	 * (currently only implemented for 32 bit numbers)
// 	 */
// 	inline DTidx lsb (DTidx n){
// 		DTidx res = 0;
// 		while(n % 2 == 0){
// 			res++; n >>= 1;
// 		}
// 		return(res);
// 	}

	// nlogn_1-Algo for out-of-block-block-queries:
	RMQ_nlogn_1* RMQ_ST;
};

#endif
