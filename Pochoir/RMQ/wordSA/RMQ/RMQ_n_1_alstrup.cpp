#include "RMQ_n_1_alstrup.hpp"

const char RMQ_n_1_alstrup::LSBTable256[256] = 
	{
		0,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
		4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
	};

DTidx RMQ_n_1_alstrup::lsb(DTidx v) {
	DTidx c;          // c will be lsb(v)
	register DTidx t, tt; // temporaries

	if (tt = v & 0xFFFF) // tt now contains lower 16 bits of v
		c = (t = tt & 0xFF) ? LSBTable256[t] : 8 + LSBTable256[tt >> 8];
	else {
		tt = v >> 16;
		c = (t = tt & 0xFF) ? 16 + LSBTable256[t] : 24 + LSBTable256[tt >> 8];
	}
	return c;
}

DTidx RMQ_n_1_alstrup::query(DTidx i, DTidx j) {
	DTidx block_i = block(i);       // block where i is
	DTidx block_j = block(j);       // j's block
	DTidx i_start = block_i * bs;   // start of i's block
	DTidx i_pos = i - (i_start);    // position of i in block_i
	DTidx min, min_i, min_j; 		// min: to be returned

	if (block_j == block_i) {
		min_i = clearbits(Prec[j], i_pos);
		min = min_i == 0 ? j : i_start + lsb(min_i);
	}
	else {
		DTidx j_start = block_j * bs;   // start of j's block
		DTidx i_end = i_start + bs - 1; // end of i's block

		min = clearbits(Prec[i_end], i_pos);
		min_i = min == 0 ? i_end : i_start + lsb(min);
		min_j = Prec[j] == 0 ? j : j_start + lsb(Prec[j]);
		if (block_j > block_i + 1) { // out-of-block query:
			i_start = c[RMQ_ST->query(block_i+1, block_j-1)];
		}
		else i_start = min_i;

		// compare minima:
		if (a[min_i] <= a[i_start]) {
			min = a[min_i] <= a[min_j] ? min_i : min_j;
		}
		else {
			min = a[i_start] <= a[min_j] ? i_start : min_j;
		}
	}

	return min;
}

/**
 * Standard Constructor. a is the array to be prepared for RMQ.
 * n is the size of the array.
 */
RMQ_n_1_alstrup::RMQ_n_1_alstrup(DT* a, DTidx n) {
	this->a = a;
	this->n = n;
	bs = sizeof(DTidx) * 8; // calculate block size (=#bits per word)
	nb = block(n-1)+1;      // number of blocks

	// allocate and fill arrays for out-of-block-queries:
	c = new DTidx[nb];
	cout << nb*4 << " ";
	DTidx min;   // position of minimum in current block
	DTidx z=0;   // index in array a
	DTidx end;   // end of current block

	for (DTidx i = 0; i < nb; i++) { // step through blocks
		min = z;                 // init minimum
		end = z + bs;            // end of block
		if (end > n) end = n;    // last block could be smaller than bs!

		while (++z < end)   // step through current block
			if (a[z] < a[min]) min = z;   // update minimum
		c[i] = min; // store index of minimum
	}
	RMQ_ST = new RMQ_nlogn_1(a, c, nb); // construct sparse table on block-minima

	/* create integers for constant time rmq inside the blocks
	 * In each block:
	 * - g[i]: the first position to the left of i
	 * where a[g[i]] < a[i] (or -1 if there is no such position).
	 * - l[i]: the jth bit of l[i] is 1 iff j is the first
	 * position left of i where a[j] < a[i] */
	Prec = new DTidx[n];
	DTidx* gstack = new DTidx[bs];
	DTidx gstacksize;
	DTidx g;
	for(DTidx i = 0; i < n; i++) {
		if(i % bs == 0) gstacksize = 0;
		Prec[i] = 0;
		while(gstacksize > 0 && (a[i] < a[gstack[gstacksize-1]])) {
			gstacksize--;
		}
		if(gstacksize > 0) {
			g = gstack[gstacksize-1];
			Prec[i] = Prec[g] | (1 << (g % bs));
		}
		gstack[gstacksize++] = i;
	}
	delete[] gstack;
}

/**
 * Destructor. Deletes allocated space.
 */
RMQ_n_1_alstrup::~RMQ_n_1_alstrup() {
	delete RMQ_ST;
	delete[] c;
	delete[] Prec;
}
