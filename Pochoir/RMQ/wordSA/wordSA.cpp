#include "wordSA.hpp"
using namespace std;

/*
 * Construct the word suffix array. Uses suffix array construction algorithm
 * from Larsson and Sadakane (1999).
 */
WordSA::WordSA(char* filename, unsigned char* separatorList, int numSeps, int preproc) {
	sepList = separatorList;
	seps = numSeps;

	FILE *fd;
	struct stat fdstat;
	int stat_res;
	fd = fopen(filename, "r");
	stat_res = stat(filename, &fdstat);
	if(fd && !stat_res) {
		// read file:
		n = fdstat.st_size;
		t = (unsigned char*) malloc(n + 1); // add "\0" to end of text
		if (t == NULL) {
			SA = NULL;
			cerr << "NOT ENOUGH MEMORY TO LOAD TEXT...EXIT!\n";
			return;
		}
		fread(((char*) t), sizeof(char), n, fd);
		fclose(fd);
		t[n] = 0; // terminate text

		// determine k, the number of words
		k = 1; // number of words (init with 1 to account for first word)
		for (int x = 0; x < n-1; x++) { // -1: don't count last delimiter (if there is any)
			for (int i = 0; i < seps; i++) {
				if (t[x] == sepList[i]) {
					k++;
				}
			}
		}

		// allocate space needed for sorting:
		try {
			I = new unsigned int[k];    // stores index points (=pos.'s after blanks in t)
			SA = new unsigned int[k+1]; // will finally contain the sparse SA
			t_new = new int[k+1];       // the newly constructed text
			BucketBegin = new int[256]; // global array to save current bucket beginnings
		}
		catch(bad_alloc) {
			SA = NULL;
			cerr << "NOT ENOUGH MEMORY...EXIT!\n";
			return;
		}

		// init the list of indexing points and the sparse SA:
		I[0] = 0; // always index the first text position (=first word)
		SA[0] = 0;
		int current = 1; // current word
		for (int x = 0; x < n-1; x++ ) {
			for (int i = 0; i < seps; i++) {
				if (t[x] == sepList[i]) {
					I[current] = x+1; // +1 because we are indexing AFTER the blanks!
					SA[current] = current; // init SA with id
					current++;
				}
			}
		}

		// now radix-sort the words occurring in t and simultaneousley build new text:
		bucketNr = 0; // global variable which counts #of already assigned bucket nr's
		radixStep(0, k-1, 0); // start radix sort
		delete[] BucketBegin;
		t_new[k] = 0; // terminate text

		// print some statistics:
// 		cerr << "Number of words to be indexed:\t" << k << endl;
// 		cerr << "Number of different words:\t" << bucketNr << endl;

	    // build (full-text) suffix array for new next
		SAforIntsLarsson* constructSA = new SAforIntsLarsson();
		constructSA->construct(t_new, k+1, bucketNr+1, (int*) SA);
		// 'SA' now contains the suffix array for t_new
 		delete constructSA;

		// finally, calculate inverse SA & transform indexes in t_new to indexes in t:
		int* invSA = t_new;
	    if (preproc >= LLCP_RLCP)
			for (int i=0; i<k; i++) invSA[SA[i+1]] = i; // construct inverse SA
	    for (int i=0; i<k; i++) SA[i] = I[SA[i+1]];

		LCP = NULL; RMQ = NULL; B = NULL;
		if (preproc <= BUCKET) {
			delete[] t_new; delete[] I; // free space if LCP not desired

			if (preproc == BUCKET) {
				K = (int) (log(k/4 + 1) / 5.545177); // 5.5... = ln(256) = ln(|Sigma|)
				if (K == 0) K = 1;

				bucketNr = 1; for (int i = 0; i < K; i++) bucketNr *= 256; // |Sigma|^K
				B = new int[bucketNr]; unsigned char* p = new unsigned char[K];
				for (int i = 0; i < K; i++) p[i] = 0; // init p with first K-tuple
				int i = 0, z = 0;                     // i: pointer in SA; z: counter
				while (true) {  // step through all K-tuples:
 					while (i < k && strncmp((char*) &t[SA[i]], (char*) p, K) < 0) i++;
 					B[z++] = i; // store beginning

					// visit next K-tuple:
					int j = K-1; // j: pointer in p
					while (j >= 0 && p[j] == 255) p[j--] = 0;
					if (j < 0) break;
					p[j]++;
				} 
			}
		}
		else {
			// calculate LCP:
			LCP = (int*) I;      // 'I' not needed anymore => reuse space
			calculateLCP(invSA); // calculate LCP-table
			delete[] invSA;      // invSA not needed anymore => free space

			if (preproc == LLCP_RLCP) {
				calculateLLCPandRLCP(); // pre-calculate LCP-values for bin. search
			}
			else if (preproc == LCP_RMQ) {
				RMQ = new RMQ_n_1_alstrup(LCP, k); // prepare LCP for RMQ
			}
		}
	}
	else { // could not open text
		cout << "COULD NOT OPEN TEXT... EXIT!\n";
		exit(-1);
	}
}

/**
 * Bucket-sort the suffixes t_{I[SA[l]]..n}, ..., t_{I[SA[r]]..n} in-place taking
 * their (h+1)'th character as the sort key.
 **/
void WordSA::radixStep(int l, int r, int h) {
	// first pass: count
	int* Sigma = new int[256]; // Sigma counts occurring characters in bucket
	memset(Sigma, 0, sizeof(int) * 256);
	for (int i = l; i <= r; i++) Sigma[t[I[SA[i]]+h]]++; // count characters
	BucketBegin[0] = l;
	for (int i = 1; i < 256; i++) {
		BucketBegin[i] = Sigma[i-1] + BucketBegin[i-1]; // accumulate
	}

	// second pass: move (this variant does *not* need an additional array!)
	unsigned char currentKey = 0;    // character of current bucket
	int end = l-1+Sigma[currentKey]; // end of current bucket
	int pos = l;                     // 'pos' is current position in bucket
	while (1) {
		if (pos > end) {
			if (currentKey == 255) break;
			currentKey++;
			pos = BucketBegin[currentKey];
			end += Sigma[currentKey];
		}
		else {
			unsigned int tmp = SA[BucketBegin[t[I[SA[pos]]+h]]];
			SA[BucketBegin[t[I[SA[pos]]+h]]++] = SA[pos];
			SA[pos] = tmp;
			if (t[I[SA[pos]]+h] == currentKey) pos++;
		}
	}

	// recursively refine buckets and calculate new text:
	int beg = l; end = l-1;
	for (int i = 1; i < 256; i++) { // step through Sigma to find bucket borders
		end += Sigma[i];
		if (beg <= end) {
			bool bucket_finished = false;
			if (beg == end) bucket_finished = true;  // 1-element bucket
			else {
				// check if this bucket has reached a separator:
				for (int j = 0; j < seps; j++) {
					if (t[I[SA[beg]]+h] == sepList[j]) bucket_finished = true;
				}
			}
			if (bucket_finished) {
				bucketNr++;
				for (int j = beg; j <= end; j++) t_new[SA[j]] = bucketNr; // set new text
			}
			else {
				radixStep(beg, end, h+1); // recursive refinement
			}
			beg = end + 1;
		}
	}
	delete[] Sigma;
}

/**
 * Calculate LCP-table for SA in O(n) time and O(k) space.
 * This method is adapted from Kasai et al.'s O(n)-LCP computation (CPM'01).
 */
void WordSA::calculateLCP(int* invSA) {
	LCP[0] = -1;
	int h = 0; int p;
	for (int i = 0; i < k; i++) {
		p = invSA[i];
		h -= SA[p];
		if (h < 0) h = 0;
		if (p > 0) {
			int y = SA[p-1];
			while (SA[p]+h < n && y + h < n && t[SA[p] + h] == t[y+h]) h++;
			LCP[p] = h;
		}
		h += SA[p];
	}
}

void WordSA::calculateLLCPandRLCP() {
	int MM = (k-1)/2;
	pair<int, int> LCP_child = calculateLLCPandRLCPrecursive(0, k-1, MM);
	if (LCP_child.first > LCP_child.second) {
		LCP[MM] = LCP_child.first; otherLCPatRoot = LCP_child.second;
	}
	else {
		LCP[MM] = -1 * LCP_child.second; otherLCPatRoot = LCP_child.first;
	}
}

pair<int, int> WordSA::calculateLLCPandRLCPrecursive(int L, int R, int M) {
	int MM, LLCP_current, RLCP_current;
	pair<int, int> LCP_child;

	if (R - L == 2) {
		// Base case:
		LLCP_current = LCP[M];
		RLCP_current = LCP[R];
	}
	else {
		// start recursion:
		if (M - L > 1) {
			MM = (L + M) / 2;
			LCP_child = calculateLLCPandRLCPrecursive(L, M, MM); // go left
			// berechne LCP von L und M (Dyn. Programmierung):
			if (LCP_child.first > LCP_child.second) {
				LCP[MM] = LCP_child.first; LLCP_current = LCP_child.second;
			}
			else {
				LCP[MM] = -1 * LCP_child.second; LLCP_current = LCP_child.first;
			}
		}
		else LLCP_current = LCP[M];

		MM = (R + M) / 2;
		LCP_child = calculateLLCPandRLCPrecursive(M, R, MM); // go right
		if (LCP_child.first > LCP_child.second) {
			LCP[MM] = LCP_child.first; RLCP_current = LCP_child.second;
		}
		else {
			LCP[MM] = -1 * LCP_child.second; RLCP_current = LCP_child.first;
		}
	}
	return pair<int, int> (LLCP_current, RLCP_current);
}

/**
 * Implements the NAIVE binary search for pattern p[0..len-1] in SA.
 * Each binary search step compares p with t from scratch, so the time
 * needed is O(|p| * log(k)).
 **/
pair<int, int> WordSA::range_naive(unsigned char* p, int len){
	int l, r, m, r2, l2=0, vgl;
	bool found = false;

	int cmp_with_first = strncmp((char*) p, (char*) &t[SA[0]],   len);
	int cmp_with_last  = strncmp((char*) p, (char*) &t[SA[k-1]], len);
	if (cmp_with_first < 0) {
		l = 1; l2 = 0;   // pattern doesn't occur!
	}
	else if(cmp_with_last > 0) {
		l = k; l2 = k-1; // pattern doesn't occur!
	}
	else {
		// search for left border:
		l = 0; r = k-1;
		if (cmp_with_first == 0) {
			found = true; r2 = r;
		}
		else {
			while (r - l > 1) {
				m = (l+r) / 2;
				vgl = strncmp((char*) p, (char*) &t[SA[m]], len);
				if (vgl <= 0) {
					if (!found && vgl == 0) {
						found = true;
						l2 = m; r2 = r; // search interval for right border
					}
					r = m;
				}
				else l = m;
			}
			l = r;
		}

		// search for right border (in the range [l2:r2])
		if (!found) {
			l2 = l - 1; // pattern not found => right border to the left of 'l'
		}
		else if (cmp_with_last == 0) {
			l2 = k-1; // right border is the end of the array
		}
		else {
			while (r2 - l2 > 1) {
				m = (l2 + r2) / 2;
				vgl = strncmp((char*) p, (char*) &t[SA[m]], len);
				if (vgl < 0) r2 = m;
				else l2 = m;
			}
		}
	}

	return pair<int, int>(l, l2);
}

/**
 * Implements the naive binary search with some heuristics which make the search
 * faster in practice (but not in theory).
 **/
pair<int, int> WordSA::range_engineered(unsigned char* p, int len) {
	// calculate "signature" of first min{K, len} characters in p:
	int H = 0, m = 1, pos = K-1, l, r;
	if (pos < len) {
		for (int i = 0; i < K; i++) {
			H += m * p[pos];
			m *= 256; pos--;
		}
		l = B[H]; r = B[H+1]-1; // init search interval in SA
	}
	else {
		l = 0; r = k-1; // search the complete SA
	}

	int l2 = l, r2 = r;
	bool found = false;
	int L = lcp(p, &t[SA[l]], len); // L=#matching characters of p and t_{SA[l]..n}
	int R = lcp(p, &t[SA[r]], len); // R=#matching characters of p and t_{SA[r]..n}
	int L2 = L, R2 = R, match_right = R;

	if (L == len) found = true; // complete match at beginning of SA
	else if (p[L] < t[SA[l]+L]) {
		l = 1; l2 = 0;   // pattern doesn't occur!
	}
	else if(R < len && p[R] > t[SA[r]+R]) {
		l = k; l2 = k-1; // pattern doesn't occur!
	}
	else {
		// search for left border:
		while (r - l > 1) {
			m = (l+r) / 2;
			H = L < R ? L : R;
		    H += lcp(&t[SA[m]+H], &p[H], len-H);

			if (H == len || p[H] <= t[SA[m] + H]) {
				if (!found && H == len) {
					found = true;
					l2 = m; r2 = r; // search interval for right border
					L2 = H; R2 = R; // save #matching characters
				}
				r = m; R = H;
			}
			else { l = m; L = H; }
		}
		l = r;
	}

	// search for right border (in the range [l2:r2])
	if (match_right < len && !found) l2 = l - 1; // p not found => right border left of l
	else if (match_right == len) {
		l2 = r2; // right border is the end of the search interval
	}
	else {
		while (r2 - l2 > 1) {
			m = (l2 + r2) / 2;

			H = L2 < R2 ? L2 : R2;
			H += lcp(&t[SA[m] + H], &p[H], len-H);

			if (H == len || p[H] >= t[SA[m] + H]) {
				l2 = m; L2 = H; 
			}
			else { r2 = m; R2 = H; }
		}
	}

	return pair<int, int>(l, l2);	
}

// LCP for 2 strings (simple string comparisons):
int WordSA::lcp(unsigned char* t1, unsigned char* t2, int max) {
	int i = 0;
	while (i < max && t1[i] == t2[i]) i++;
	return i;
}

/**
 * Implements the IMPROVED binary search for pattern p[0..len-1] in SA.
 * Each binary search step compares p with t starting from max{L,R}, so
 * the time needed is O(|p| + log(k)).
 **/
pair<int, int> WordSA::range_improved(unsigned char* p, int len){
	int l = 0, r = k-1, m, l2=0, r2=k-1, M;
	int LLCP_m, RLCP_m, otherLCP = otherLCPatRoot, otherLCP2 = otherLCP;
	bool found = false;
	int L = lcp(p, &t[SA[0]], len);   // L=#matching characters of p and t_{SA[l]..n}
	int R = lcp(p, &t[SA[k-1]], len); // R=#matching characters of p and t_{SA[r]..n}
	int L2 = L, R2 = R, match_right = R;

	if (L == len) found = true; // complete match at beginning of SA
	else if (p[L] < t[SA[0]+L]) {
		l = 1; l2 = 0;   // pattern doesn't occur!
	}
	else if(R < len && p[R] > t[SA[k-1]+R]) {
		l = k; l2 = k-1; // pattern doesn't occur!
	}
	else {
		// search for left border:
		while (r - l > 1) {
			m = (l+r) / 2;
			if (LCP[m] < 0) { LLCP_m = otherLCP; RLCP_m = LCP[m]*-1; }
			else { LLCP_m = LCP[m]; RLCP_m = otherLCP; }

			if (L >= R) {
				if (LLCP_m >= L) M = L + lcp(&t[SA[m]+L], &p[L], len-L);
				else M = LLCP_m;
			}
			else {
				if (RLCP_m >= R) M = R + lcp(&t[SA[m]+R], &p[R], len-R);
				else M = RLCP_m;
			}

			if (M == len || p[M] <= t[SA[m] + M]) {
				if (!found && M == len) {
					found = true;
					l2 = m; r2 = r; // search interval for right border
					L2 = M; R2 = R; // save #matching characters
					otherLCP2 = RLCP_m;
				}
				r = m; R = M; otherLCP = LLCP_m;
			}
			else { l = m; L = M; otherLCP = RLCP_m; }
		}
		l = r;
	}

	// search for right border (in the range [l2:r2])
	if (!found) l2 = l - 1; // pattern not found => right border to the left of 'l'
	else if (match_right == len) {
		l2 = k-1; // right border is the end of the array
	}
	else {
		while (r2 - l2 > 1) {
			m = (l2 + r2) / 2;
			if (LCP[m] < 0) { LLCP_m = otherLCP2; RLCP_m = LCP[m]*-1; }
			else { LLCP_m = LCP[m]; RLCP_m = otherLCP2; }

			if (L2 >= R2) {
				if (LLCP_m >= L2) M = L2 + lcp(&t[SA[m] + L2], &p[L2], len-L2);
				else M = LLCP_m;
			}
			else {
				if (RLCP_m >= R2) M = R2 + lcp(&t[SA[m] + R2], &p[R2], len-R2);
				else M = RLCP_m;
			}

			if (M == len || p[M] >= t[SA[m] + M]) {
				l2 = m; L2 = M; otherLCP2 = RLCP_m;
			}
			else { r2 = m; R2 = M; otherLCP2 = LLCP_m; }
		}
	}

	return pair<int, int>(l, l2);	
}

/**
 * Implements the Enhanced Suffix Array-search with improvements from
 * Fischer/Heun'07. Searching takes time O(|p|*|Sigma|).
 */
pair<int, int> WordSA::range_esa(unsigned char* p, int len){
	int c = 0, min;     // c: number of matched characters so far
	int l = 0, r = k-1; // current interval in SA (start with root)
	bool found = true;  // true iff p[0..c-1] occurrs in the text

	do {
		pair<int,int> child = getChild(l, r, p[c]);
		l = child.first; r = child.second;
		if (l == -1) return pair<int,int>(l, l-1); // not found
		if (l == r) min = len;  // reached a leaf => match to the end of p
		else {
			register int L = LCP[RMQ->query(l+1,r)];
			min = len < L ? len : L;
		}
		for ( ; found && c < min; c++) found = (p[c] == t[SA[l]+c]);
		c = min;
	} while (l < r && c < len && found);
	if (found) return pair<int,int>(l, r);
	return pair<int,int>(l, l-1); // not found
}

pair<int, int> WordSA::getChild(int l, int r, unsigned char a) {
	int r_new = RMQ->query(l+1, r); // get first \ell-index
	int h = LCP[r_new]; // h is the depth of this node in the ST
	do {
		if (t[SA[l]+h] == a) return pair<int, int>(l, r_new-1);
		l = r_new;
		r_new = RMQ->query(l+1, r);
	} while (l != r && LCP[r_new] <= h);
	if (t[SA[l]+h] == a) return pair<int, int>(l, r);
	return pair<int,int>(-1,-1); // not found
}

WordSA::~WordSA() {
	if (SA != NULL) delete[] SA;
	if (LCP != NULL) delete[] LCP;
	if (RMQ != NULL) delete RMQ;
	if (t != NULL) free(t);
}
