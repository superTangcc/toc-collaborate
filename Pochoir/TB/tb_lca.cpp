/*
 * ============================================================================
 *
 *       Filename:  lca.cpp
 *
 *    Description:  bit tricks to find the lowest common ancestor of a 
 *                  complete binary tree, which is stored in an array
 *                  The lowest common ancestor of (a, b) is actually
 *                  the longest common prefix of (a, b)
 *
 *        Version:  1.0
 *        Created:  11/16/2011 04:55:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <cstdio>
#include <cstdlib>

static inline unsigned int log_2_bt(unsigned int v) {
    register unsigned int r; // result of log2(v) will go here
    register unsigned int shift;

    r     = (v > 0xffff) << 4; v >>= r;
    shift = (v > 0xff) << 3  ; v >>= shift; r |= shift;
    shift = (v > 0xf) << 2   ; v >>= shift; r |= shift;
    shift = (v > 0x3) << 1   ; v >>= shift; r |= shift;
                                            r |= (v >> 1);
    return (r+1);
}

static inline unsigned int log2_ceil(unsigned long a) {
    printf("long version!\n");
    return 64-__builtin_clzl(a);
}

static inline unsigned int log2_ceil(unsigned int a) {
    printf("int version!\n");
    return 32-__builtin_clz(a);
}

static inline unsigned int log2_floor(unsigned long a) {
    printf("long version!\n");
    return 63-__builtin_clzl(a);
}

static inline unsigned int log2_floor(unsigned int a) {
    printf("int version!\n");
    return 31-__builtin_clz(a);
}

static inline unsigned int MultiplyDeBruijn(unsigned int v) {
    static const int MultiplyDeBruijnBitPos[32] = {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    unsigned int r = MultiplyDeBruijnBitPos[(unsigned int)(v * 0x07c4acddu) >> 27];
    return (r+1);
}

static inline unsigned long lcp(unsigned long a, unsigned long b) {
    /* lcp: longest common prefix */
    unsigned int bit_len_a = log2_ceil(a), bit_len_b = log2_ceil(b);
    if (bit_len_a >= bit_len_b) {
        a >>= (bit_len_a - bit_len_b);
    } else {
        b >>= (bit_len_b - bit_len_a);
    }
    unsigned int c = a^b; /* xor operation */
    if (c == 0)
        return a;
    unsigned int log2c = log2_ceil(c);
    return (a >> log2c);
}

static inline unsigned long allone64(void) {
    unsigned long res = 0;
    for (int i = 0; i < 64; ++i) {
        res = (res << 1) | 0x1;
    }
    return 0xffffffffffffffff;
}
int main(int argc, char * argv[]) {
    if (argc < 3) {
        printf("argc < 3: quit!\n");
        exit(EXIT_FAILURE);
    }
    unsigned int a = atoi(argv[1]), b = atoi(argv[2]);

    printf("Lowest Common Ancestor(%d, %d) = %lu\n", a, b, lcp(a, b));

    printf("allone64 = 0x%lx, mod64 = 0x%lx, 63 = 0x%lx, true = %d\n", allone64(), allone64() << 6, (unsigned long)0x3f, 2>0);
    return 0;
}
