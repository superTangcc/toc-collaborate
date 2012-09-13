/* One dimensional 1-bit range minimum query. */

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

int log2_slow (unsigned long n) {
    for (int i=0; i<64; i++) {
	if (n < (1ull<<i)) return i-1;
    }
    return 63;
}

int log2_branches (unsigned long n) {
    int r = 0;
    if (n >= (1ull << 32)) {
	r += 32;
	n = n>>32;
    }
    if (n >= (1ull << 16)) {
	r += 16;
	n = n>>16;
    }
    if (n >= (1ull << 8)) {
	r += 8;
	n = n>>8;
    }
    if (n >= (1ull << 4)) {
	r += 4;
	n = n>>4;
    }
    if (n >= (1ull << 2)) {
	r += 2;
	n = n>>2;
    }
    if (n >= (1ull << 1)) {
	r += 1;
	n = n>>1;
    }
    if (n == 0) {
	r=-1;
    }
    return r;
}

int log2_opt_branches (unsigned long n) {
    register unsigned int r = 0;
    register unsigned long v = n;
    register int shift;

    shift = v >= 0x100000000;
	r = shift ? 32 : r;
	v = shift ? v>>32 : v;

    shift = v >= 0x10000;
	r = shift? r+16: r;
	v = shift? v>>16 : v;

    shift = v >= 0x100;
	r = shift? r+8: r;
	v = shift? v>>8: v;

    shift = v >= 0x10;
	r = shift? r+4 : r;
	v = shift? v>>4: v;

    shift = v >= 0x4;
	r = shift? r+2: r;
	v = shift? v>>2: v;

    shift = v >= 0x2;
	r = shift? r+1: r;
	v = shift? v>>1: v;

    shift = v == 0;
    r = shift? -1: r;
    return r;
}

int log2_nobranches (unsigned long n)
// Effect: Return $\lfloor \log_2 n \rfloor$.
// Implementation note: Do it in $O(\log \id{sizeof} n)$ operations and no branches.
{
    //int l2 = log2_slow(n);
    int r;
    {
	unsigned long n_32 = n>>32;
	signed   long s_32 = (signed long)n_32;
	signed   long b_32 = (s_32-1) >> 63;  // all 1's or all 0's.   All 0's if n had a bit set in the top 32 bits.  All 1 had no bits in the top half.

	r = (~b_32) & 32;
	n = ( b_32 & (n&0xFFFFFFFF)) | ((~b_32) & n_32);
    }
    //assert(l2 == r + log2_slow(n));

    {
	unsigned long n_16 = n>>16;
	signed   long s_16 = (signed long)n_16;
	signed   long b_16 = (s_16-1) >> 63;  // all 1's or all 0's.   All 0's if n had a bit set in the top 32 bits.  All 1 had no bits in the top half.

	r += (~b_16) & 16;
	n = ( b_16 & (n&0xFFFF)) | ((~b_16) & n_16);
    }
    //assert(l2 == r + log2_slow(n));

    {
	unsigned long n_8 = n>>8;
	signed   long s_8 = (signed long)n_8;
	signed   long b_8 = (s_8-1) >> 63;  // all 1's or all 0's.   All 0's if n had a bit set in the top 32 bits.  All 1 had no bits in the top half.

	r += (~b_8) & 8;
	n = ( b_8 & (n&0xFF)) | ((~b_8) & n_8);
    }
    //assert(l2 == r + log2_slow(n));

    {
	unsigned long n_4 = n>>4;
	signed   long s_4 = (signed long)n_4;
	signed   long b_4 = (s_4-1) >> 63;  // all 1's or all 0's.   All 0's if n had a bit set in the top 32 bits.  All 1 had no bits in the top half.

	r += (~b_4) & 4;
	n = ( b_4 & (n&0xF)) | ((~b_4) & n_4);
    }
    //assert(l2 == r + log2_slow(n));

    {
	unsigned long n_2 = n>>2;
	signed   long s_2 = (signed long)n_2;
	signed   long b_2 = (s_2-1) >> 63;  // all 1's or all 0's.   All 0's if n had a bit set in the top 32 bits.  All 1 had no bits in the top half.

	r += (~b_2) & 2;
	n = ( b_2 & (n&0x3)) | ((~b_2) & n_2);
    }
    //assert(l2 == r + log2_slow(n));

    {
	unsigned long n_1 = n>>1;
	signed   long s_1 = (signed long)n_1;
	signed   long b_1 = (s_1-1) >> 63;  // all 1's or all 0's.   All 0's if n had a bit set in the top 32 bits.  All 1 had no bits in the top half.

	r += (~b_1) & 1;
	n = ( b_1 & (n&0x1)) | ((~b_1) & n_1);
    }
    //assert(l2 == r + log2_slow(n));


    return r;
}

int log2_bsr (unsigned long a) {
    return 63-__builtin_clzl(a);
}

int log2_bt (unsigned long a) {
    register unsigned int r; // result of log2(v) will go here
    register unsigned int shift;

    r     = (a > 0xffffffff) << 5; a >>= r;
    shift = (a > 0xffff) << 4; a >>= shift; r |= shift;
    shift = (a > 0xff) << 3  ; a >>= shift; r |= shift;
    shift = (a > 0xf) << 2   ; a >>= shift; r |= shift;
    shift = (a > 0x3) << 1   ; a >>= shift; r |= shift;
                                            r |= (a >> 1);
    // return (r+1);
    return (r);
}

int log2_DeBruijn(unsigned long a) {
    static const int MultiplyDeBruijnBitPos[32] = {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    a |= a >> 1;
    a |= a >> 2;
    a |= a >> 4;
    a |= a >> 8;
    a |= a >> 16;
    unsigned int r = MultiplyDeBruijnBitPos[(unsigned int)(a * 0x07c4acddu) >> 27];
    // return (r+1);
    return (r);
}

int log2_double (unsigned long a) {
    union u {
	double f;
	unsigned long a;
    } u;
    u.f=a;
    int shiftit = u.a>>52;
    int result = shiftit-0x3ff;
    return result;
}

int log2_ldouble (unsigned long a) {
    union u {
	long double f;
	unsigned long a[2];
    } u;
    u.f=a;
    //printf("u=%016lx %016lx\n", u.a[0], u.a[1]);
    int shiftit = u.a[1] & 0x7ffful;
    //printf("s=%x\n", shiftit);
    int result = shiftit-0x3fff;
    //printf("s=%d\n", result);
    return result;
}

void check (unsigned long a) {
    if (a==0) return;
    int aslow = log2_slow(a);
    int abranches   = log2_branches(a);
    assert(aslow==abranches);
    int aoptbranches   = log2_opt_branches(a);
    assert(aslow==aoptbranches);
    int anobranches = log2_nobranches(a);
    assert(aslow==anobranches);
    int absr        = log2_bsr(a);
    assert(aslow==absr);
    int abt         = log2_bt(a);
    // assert(aslow==abt);
    int aDeBruijn         = log2_DeBruijn(a);
    static bool fst_enter = true;
    // if (fst_enter && (abt != aslow || aDeBruijn != aslow)) {
    if (fst_enter && (abt != aslow)) {
        printf("aslow = %d, abt = %d, aDeBruijn = %d\n", aslow, abt, aDeBruijn);
        fst_enter = false;
    }
    // assert(aslow==aDeBruijn);
    int aldbl       = log2_ldouble(a);
    assert(aslow==aldbl);
}

void test_log_branches (void) {
    for (int i=0; i<64; i++) {
	unsigned long a = 1ull<<i;
	check(a);
	check(a-1);
	for (int j=0; j<64; j++) {
	    unsigned long b = 1ull<<j;
	    check(a|b);
	}
    }
    for (int i=0; i<10000000; i++) {
	check(i);
    }
}

float tdiff (struct timeval *start, struct timeval *end) {
    return (end->tv_sec-start->tv_sec) +1e-6*(end->tv_usec - start->tv_usec);
}

unsigned long N=50000000;

#define def_run(f) void run_ ## f (void) { int sum = 0; for (unsigned int i=0; i<N ;i++) sum+=f(i); if (sum==0) printf("sum=%d\n", sum); }
def_run(log2_slow)
def_run(log2_branches)
def_run(log2_opt_branches)
def_run(log2_nobranches)
def_run(log2_bsr)
def_run(log2_bt)
def_run(log2_DeBruijn)
def_run(log2_double)
def_run(log2_ldouble)

void timeit (void (*f)(void), const char *s) {
    struct timeval a,b;
    const int times = 1;
    gettimeofday(&a, NULL);
    for (int i = 0; i < times; ++i) {
        f();
    }
    gettimeofday(&b, NULL);
    printf("%20s: %.6f\n", s, tdiff(&a, &b));
}

int main (int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__))) {
    test_log_branches();
#define runf(f) timeit(run_ ##f, #f) 
    runf(log2_slow);
    runf(log2_branches);
    runf(log2_opt_branches);
    runf(log2_nobranches);
    runf(log2_bsr);
    runf(log2_bt);
    runf(log2_DeBruijn);
    runf(log2_double);
    runf(log2_ldouble);
    return 0;
}

