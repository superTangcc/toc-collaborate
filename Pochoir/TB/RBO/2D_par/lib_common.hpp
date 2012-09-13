/*
 * ============================================================================
 *
 *       Filename:  lib_common.hpp
 *
 *    Description:  common facilities for test benches
 *
 *        Version:  1.0
 *        Created:  03/09/2012 11:23:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */
#ifndef LIB_COMMON_HPP
#define LIB_COMMON_HPP

/* BOOST will be used to utilize the bind() facility only if the std::bind()
 * doesn't work, e.g. on Ubuntu 10.04
 */
#ifdef BOOST
#undef BOOST
#endif

#include <cilk/cilk.h>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <exception>
#ifdef BOOST
#include <boost/function.hpp>
#include <boost/bind.hpp>
#else
#include <functional>
#endif

using namespace std;
#ifndef BOOST
using namespace placeholders;
#endif

#define false 0
#define true 1

static const unsigned long ALLZERO64 = 0x0;
static const unsigned long ALLONE64 = 0xffffffffffffffff;

static inline double tdiff (struct timeval *a, struct timeval *b) {
    return a->tv_sec - b->tv_sec + 1e-6 * (a->tv_usec - b->tv_usec);
}
static inline unsigned int log2_ceil (unsigned long a) {
    unsigned int nbits = __builtin_popcountl(a);
    unsigned int res = nbits > 1 ? 64 - __builtin_clzl(a) : 63 - __builtin_clzl(a);
    return res;
}
static inline unsigned int log2_ceil (unsigned int a) {
    unsigned int nbits = __builtin_popcount(a);
    unsigned int res = nbits > 1 ? 32 - __builtin_clz(a) : 31 - __builtin_clz(a);
    return res;
}
static inline unsigned int log2_floor (unsigned long a) {
    return 63-__builtin_clzl(a);
}
static inline unsigned int log2_floor (unsigned int a) {
    return 31-__builtin_clz(a);
}
#define THRES 2

typedef unsigned long T_Data;
#ifdef BOOST
typedef boost::function<T_Data (T_Data)> T_Curry_Func;
#else
typedef function<T_Data (T_Data)> T_Curry_Func;
#endif

static inline T_Data log2_helper (T_Data a) {
    return 63-__builtin_clzl(a);
}
static inline T_Data star(T_Curry_Func f, T_Data N) {
    T_Data n = N, res = 0;
    while (n > THRES) {
        n = f(n);
        ++res;
    }
    return res;
}

static inline T_Data alpha(T_Data N) {
    T_Curry_Func func = log2_helper;
    T_Data n = N, res = 0;
    while (n > THRES) {
        func = bind(star, func, _1);
        n = func(n);
        ++res;
    }
    return res;
}

static inline unsigned int msb_pos (unsigned long a) {
    /* returns the position of most significant bit
     * or number of valid bits
     */
    assert(a>0);
    return 64-__builtin_clzl(a);
}
static inline unsigned int msb_pos (unsigned int a) {
    /* returns the position of most significant bit
     * or number of valid bits
     */
    assert(a>0);
    return 32-__builtin_clz(a);
}
static inline unsigned long msb_i(unsigned long a, unsigned long i) {
    /* return most 'i' significant bits */
    return (a>>i);
}
static inline unsigned long lsb_i(unsigned long a, unsigned long i) {
    /* return least 'i' significant bigs */
    if (i == 64)
        return a;
    return (a - ((a >> i) << i));
}
template <int DIVISOR>
inline unsigned long mod(unsigned long a) { return (a % DIVISOR); }
template <>
inline unsigned long mod<1>(unsigned long a) { return 0; }
template <>
inline unsigned long mod<2>(unsigned long a) { return (a & ((unsigned long)0x1)); }
template <>
inline unsigned long mod<4>(unsigned long a) { return (a & ((unsigned long)0x3)); }
template <>
inline unsigned long mod<8>(unsigned long a) { return (a & ((unsigned long)0x7)); }
template <>
inline unsigned long mod<16>(unsigned long a) { return (a & ((unsigned long)0xf)); }
template <>
inline unsigned long mod<32>(unsigned long a) { return (a & ((unsigned long)0x1f)); }
template <>
inline unsigned long mod<64>(unsigned long a) { return (a & ((unsigned long)0x3f)); }

template <int DIVISOR>
inline unsigned long div_ceil(unsigned long a) { return (a/DIVISOR + (mod<DIVISOR>(a) > 0)); }
template <>
inline unsigned long div_ceil<1>(unsigned long a) { return a; }
template <>
inline unsigned long div_ceil<2>(unsigned long a) { return ((a>>1) + (mod<2>(a) > 0)); }
template <>
inline unsigned long div_ceil<4>(unsigned long a) { return ((a>>2) + (mod<4>(a) > 0)); }
template <>
inline unsigned long div_ceil<8>(unsigned long a) { return ((a>>3) + (mod<8>(a) > 0)); }
template <>
inline unsigned long div_ceil<16>(unsigned long a) { return ((a>>4) + (mod<16>(a) > 0)); }
template <>
inline unsigned long div_ceil<32>(unsigned long a) { return ((a>>5) + (mod<32>(a) > 0)); }
template <>
inline unsigned long div_ceil<64>(unsigned long a) { return ((a>>6) + (mod<64>(a) > 0)); }

template <int DIVISOR>
inline unsigned long div(unsigned long a) { return (a/DIVISOR); }
template <>
inline unsigned long div<1>(unsigned long a) { return a; }
template <>
inline unsigned long div<2>(unsigned long a) { return (a>>1); }
template <>
inline unsigned long div<4>(unsigned long a) { return (a>>2); }
template <>
inline unsigned long div<8>(unsigned long a) { return (a>>3); }
template <>
inline unsigned long div<16>(unsigned long a) { return (a>>4); }
template <>
inline unsigned long div<32>(unsigned long a) { return (a>>5); }
template <>
inline unsigned long div<64>(unsigned long a) { return (a>>6); }

template <int UNFOLD>
inline unsigned long unfold_compact(unsigned long * _input_array, unsigned long _idx, unsigned long _bmask) {
    return (((_input_array[_idx + UNFOLD - 1] & _bmask) << (UNFOLD-1)) | unfold_compact<UNFOLD-1>(_input_array, _idx, _bmask));
}
template <>
inline unsigned long unfold_compact<1>(unsigned long * _input_array, unsigned long _idx, unsigned long _bmask) {
    return (_input_array[_idx] & _bmask);
}

static inline unsigned long pow2(unsigned int e) {
    assert(e < 64);
    unsigned long res = 1ul << e;
    return res;
}

static inline unsigned long lca(unsigned long a, unsigned long b) {
    /* lca: lowest common ancestor */
    unsigned int bit_len_a = log2_floor(a), bit_len_b = log2_floor(b);
    if (bit_len_a >= bit_len_b) {
        a >>= (bit_len_a - bit_len_b);
    } else {
        b >>= (bit_len_b - bit_len_a);
    }
    unsigned int c = a^b; /* xor operation */
    if (c == 0)
        return a;
    return (a >> msb_pos(c));
}

template <typename T, int N_RANK>
struct Wrong_RBO {
    public:
        Wrong_RBO(size_t (&_a)[N_RANK], size_t (&_b)[N_RANK], T _res_meta, T _res_naive) : res_meta_(_res_meta), res_naive_(_res_naive) {
            for (size_t i = 0; i < N_RANK; ++i) {
                a_[i] = _a[i]; b_[i] = _b[i];
            }
        }
        void print_errmsg(void) {
            cout << "meta[";
            print_idx(a_);
            cout << ", ";
            print_idx(b_);
            cout << "] = " << res_meta_ << ", naive_scan = " << res_naive_ << "\n";
            return;
        }
        void print_idx(size_t (&idx)[N_RANK]) {
            cout << "[";
            for (int i = N_RANK-1; i >= 0; --i) {
                cout << idx[i];
                if (i > 0)
                    cout << ", ";
            }
            cout << "]";
        }
    public:
        size_t a_[N_RANK], b_[N_RANK];
        T res_meta_, res_naive_;
};

#endif
