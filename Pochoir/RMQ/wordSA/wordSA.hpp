#ifndef _wordSA_hpp_
#define _wordSA_hpp_

// constants for different preprocessing techniques:
#define NO 0        // no preprocessing (for naive search)
#define BUCKET 1    // calculate table of bucket beginnings for small strings (for engineered search)
#define LLCP_RLCP 2 // calculate LLCP- and RLCP-values (for improved search)
#define LCP_RMQ 3   // calculate LCP-array with RMQ-preprocessing (for ESA-search)


#include "sa_for_ints_larsson.hpp"
#include "RMQ/RMQ_n_1_alstrup.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

/** 
 * The Word Suffix Array.
 */
class WordSA {
public:
	// construct word SA for "file" with given method (NO/BUCKET/LLCP_RLCP).
	// Text separators are passed in string "seps" of length nr_seps.
	WordSA(char* file, unsigned char* seps, int nr_seps, int method);

	// destructor
	virtual ~WordSA();

	// return range of pattern p (naive binary search)
	virtual pair<int, int> range_naive(unsigned char* p, int len);

	// return range of pattern p (improved binary search)
	virtual pair<int, int> range_improved(unsigned char* p, int len);

	// return range of pattern p (ESA-search with improvements from Fischer/Heun'07)
	virtual pair<int, int> range_esa(unsigned char* p, int len);

	// return range of pattern p (binary search with some heuristics)
	virtual pair<int, int> range_engineered(unsigned char* p, int len);

	// the word suffix array (for t)
	unsigned int* SA;

	// the text
	unsigned char* t;

	// the LCP-array:
	int* LCP;

	// length of text
	unsigned int n;

	// number of words
	unsigned int k;

private:
	// separator list
	unsigned char* sepList;

	// for preparing LCP for range minimum information:
	RMQ_n_1_alstrup* RMQ;

	// number of separators:
	int seps;

	// temporary variables for radix-sort (global for all recursion steps)
	int* BucketBegin;
	unsigned int bucketNr; // current bucket number

	// stores positions to be indexed:
	unsigned int* I;

	// the new text:
	int* t_new;

	// one step in the radix sort:
	void radixStep(int, int, int);

	// calculate LCP-table:
	void calculateLCP(int* invSA);

	// calculates the values that are needed for the O(|p|+log k)-search.
	void calculateLLCPandRLCP();

	// helper method for the above
	pair<int, int> calculateLLCPandRLCPrecursive(int L, int R, int M);

	// because LCP just stores one of LLCP and RLCP, this variable stores the
	// other value for the initial search itnerval [0:k-1]:
	int otherLCPatRoot;

	// LCP-value of two strings t1 and t2 up to max:
	int lcp(unsigned char* t1, unsigned char* t2, int max);

	// get the child interval of (l,r) starting with letter 'a'
	pair<int, int> getChild(int l, int r, unsigned char a);

	// for the engineered search algo: B is table of bucket beginnings,
	// K the length K of strings which are indexed by this table.
	int *B, K;
};

#endif
