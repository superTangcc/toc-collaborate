/* One dimensional 1-bit range minimum query. 
 *                      -- Bradley Kuszmaul
 */

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

void *xmalloc(size_t s)
// Effect: malloc space of size $s$, but abort if the malloc fails.
{
    void *r=malloc(s);
    assert(r);
    return r;
}

#define MALLOC(s) s = xmalloc(sizeof(*(s)))

static int lg (unsigned long a)
// Effect: Return the floor of the log base 2 of a.  That is $\lfloor\lg a\rfloor$.
// Warning: This function is undefined for a==0.
// This function is about the fastest way to do it on modern processors.  Another way to do it (that may be about the same or maybe faster or slower) is to convert to a float and then fetch out the exponent by improper casting.
{
    assert(a>0);
    return 63-__builtin_clzl(a);
}


float tdiff (struct timeval *start, struct timeval *end)
// Effect: Compute the difference between two times, in seconds.
{
    return (end->tv_sec-start->tv_sec) +1e-6*(end->tv_usec - start->tv_usec);
}

typedef struct rmq *RMQ;
struct rmq {
    unsigned long N;
    unsigned long *bits;
    unsigned long **summaries;
};

static int fetch_bit (unsigned long *A, unsigned long i)
// Effect: In a bitvector A, fetch the ith bit.
{
    return 1&(A[i/64]>>(i%64));
}
static void set_bit (unsigned long *A, unsigned long i, int b)
// Effect: In a bitvector A, set the ith bit to 0 or 1 depending on whether b is zero or nonzero.
{
    unsigned long *Ai64 = A+i/64;
    unsigned long v = *Ai64;
    *Ai64 = (v&~(1ul<<(i%64))) | ((unsigned long)(b!=0) << i%64);
}

static int n_summaries (unsigned long N)
// Effect: For an RMQ data structure with N bits in it, how many summary levels do we need?
{
    if (N/64==0) return 0;
    assert(0<=lg(N/64) && lg(N/64)<64);
    return lg(N/64);
}
static unsigned long size_of_summary_in_bits(unsigned long N, int i)
// Effect: For an RMQ data structure with N bits in it, how many bits are needed.
{
    return (N/64)+1-(2ul<<i);
}

void rmq_create (RMQ *result, unsigned long N, unsigned long *bits)
// Arguments:
//  bits is a bit array of length N.  A pointer to that array will bestored in the RMQ data structure.
//    bit i is at 1&(bits[i/64]>>(i%64))
//  The bit array is stored in the rmq, but it isn't owned by the rmq.  After destroying the rmq, you must arrange to free the bit array.
{
    RMQ MALLOC(r);
    r->N = N;
    r->bits = bits;
    int n_sums = n_summaries(N);
    r->summaries = xmalloc(n_sums*sizeof(unsigned long *));
    for (int i=0; i<n_sums; i++) {
	unsigned long n = size_of_summary_in_bits(N, i);
	r->summaries[i] = xmalloc((n+63)/64*sizeof(unsigned long));
	for (unsigned long j=0; j<n; j++) {
	    int bit;
	    if (i==0) {
		bit = 0!=(r->bits[j]|r->bits[j+1]);
	    } else {
		bit = fetch_bit(r->summaries[i-1], j) | fetch_bit(r->summaries[i-1], j+(1ul<<i));
	    }
	    set_bit(r->summaries[i], j, bit);
	}
    }
    *result = r;
}

void rmq_destroy (RMQ rmq)
// Effect: Free the rmq (but not the bit array)
{
    for (int i=0; i<n_summaries(rmq->N); i++) {
	free(rmq->summaries[i]);
    }
    free(rmq->summaries);
    free(rmq);
}

void rmq_print (RMQ rmq)
// Effect: print an rmq in human-readable format.
{
    printf("rmq contains %ld bits\n", rmq->N);
    for (unsigned long i=0; i<rmq->N; i++) {
	if (1) {
	    if (i%64==0) {
		printf("%016lx ", rmq->bits[i/64]);
	    }
	} else {
	    printf("%d", fetch_bit(rmq->bits, i));
	    if (i%64==63) printf(" ");
	}
    }
    printf("\n");
    for (int j=0; j<n_summaries(rmq->N); j++) {
	printf("level %2d: ", j);
	for (unsigned long i=0; i<size_of_summary_in_bits(rmq->N, j); i++) {
	    printf("%d", fetch_bit(rmq->summaries[j], i));
	}
	printf("\n");
    }
}

static unsigned long nmask (unsigned long n)
// Effect: Return 2^{n}-1 for n in the range 0 to 64.
// Implementation note:  the << operator is undefined if n>63.   I found that (1ul<<64) == 1, rather than the zero that I expected
//
// Thus this is incorrect since it overflows:
//     (1ul << n)-1;  

// And this is incorrect:
//    unsigned long r = 1ul << (n-1);
//    return 2*r-1;
// since it fails for n==0
{
    signed long d = 63-n; // this is negative for n==64, non negative for others.
    signed long ds = d>>63; // this -1 for n==64, 0 otherwise.  So use the case that is undefined for n==64, and or it with ds.
    return ds | ((1ul<<n)-1);
}

static void test_nmask (void) {
    assert(nmask(0)==0);
    assert(nmask(1)==1);
    assert(nmask(2)==3);
    assert(nmask(3)==7);
    assert(nmask(4)==15);
    assert(nmask(5)==31);
    assert(nmask(6)==63);
    assert(nmask(32)== 0xFFFFFFFFul);
    assert(nmask(33)==0x1FFFFFFFFul);
    assert(nmask(34)==0x3FFFFFFFFul);
    assert(nmask(62)==0x3FFFFFFFFFFFFFFFul);
    assert(nmask(63)==0x7FFFFFFFFFFFFFFFul);
    assert(nmask(64)==0xFFFFFFFFFFFFFFFFul);

}

unsigned long rmq_query (RMQ rmq, unsigned long lo /*inclusive*/, unsigned long hi /*exclusive*/)
// Effect: return nonzero iff there are any nonzero bits in the range [lo..hi).
{
    if (hi<=lo) return true; // if the range is empty then the minimum is "true".
    if ((lo|63) >= hi-1) {
	// They are on the same word.
	return (rmq->bits[lo/64]>>(lo%64)) & nmask(hi-lo);
    } else {
	unsigned long lo_d64 = lo/64; // the first word of the query
	unsigned int  lo_m64 = lo%64;
	unsigned long hi_d64 = hi/64; // the last word of the query (if hi_m64==0 then the last word has no bits in it, but that's ok)
	unsigned int  hi_m64 = hi%64;
	unsigned long first_word_result = rmq->bits[lo_d64] >> lo_m64;
	unsigned long last_word_result  = rmq->bits[hi_d64] & nmask(hi_m64);
	unsigned long first_last_result = first_word_result | last_word_result;
	if (lo_d64+1 == hi_d64) {
	    return first_last_result;
	} else if (lo_d64+2 == hi_d64) {
	    return first_last_result | rmq->bits[lo_d64+1];
	} else {
	    unsigned int  lgdiff = lg(hi_d64-lo_d64-1);
	    unsigned long *summary = rmq->summaries[lgdiff-1];
	    unsigned long q_start = fetch_bit(summary, lo_d64+1);
	    unsigned long q_end   = fetch_bit(summary, hi_d64-(1ul<<lgdiff));
	    return first_last_result | q_start | q_end;
	}
    }
}

static int log2_slow (unsigned long n) {
    for (int i=0; i<64; i++) {
	if (n < (1ull<<i)) return i-1;
    }
    return 63;
}

void check_lg (unsigned long a) {
    assert(log2_slow(a)==lg(a));
}

void test_log2 (void) {
    check_lg(1);
    //check_lg(0);
}

int main (int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__))) {
    test_log2();
    test_nmask();
    {
    RMQ r;
    unsigned long bits[8]={0,1,0,0,0,0,0,0};
    rmq_create(&r, 4*64, bits);
    rmq_print(r);
    rmq_destroy(r);

    rmq_create(&r, 4*64-1, bits);
    rmq_print(r);
    rmq_destroy(r);

    rmq_create(&r, 5*64, bits);
    rmq_print(r);
    rmq_destroy(r);
    }

    for (int blength=2; blength<1024; blength*=2) {
	for (int off=-1; off<2; off++) {
	    int length = blength+off;
	    int wlen = (length+63)/64;
	    unsigned long bits[wlen];
	    for (int i=0; i<wlen; i++) bits[i]=0;
	    {
		RMQ r;
		rmq_create(&r, length, bits);
		for (int j=0; j<length; j++) {
		    for (int k=j+1; k<length; k++) {
			assert(0==rmq_query(r, j, k));
		    }
		}
		rmq_destroy(r);
	    }
	    for (int z=0; z<length; z++) {
		for (int i=0; i<wlen; i++) bits[i]=0;
		set_bit(bits, z, 1);
		RMQ r;
		rmq_create(&r, length, bits);
		for (int j=0; j<length; j++) {
		    for (int k=j+1; k<length; k++) {
			bool is_zero = 0==rmq_query(r, j, k);
			if (j<=z && z<k) assert(!is_zero);
			else assert(is_zero);
		    }
		}
		rmq_destroy(r);
	    }
	}
    }

    return 0;
}
