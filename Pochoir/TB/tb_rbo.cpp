/*
 * ============================================================================
 *
 *       Filename:  tb_rbo.cpp
 *
 *    Description:  test bench for d-dimensional RBO
 *                  RBO: Range Bit-wise Operation
 *
 *        Version:  1.0
 *        Created:  03/06/2012 09:21:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include "lib_common.hpp"
#include "lib_rbo_idx.hpp"
#include "lib_rbo_bvector.hpp"
#include "lib_rbo_color_array.hpp"
#include "lib_rbo_counter_d.hpp"

using namespace std;
#define NBITS 1
#define BVECTOR 0
#define IDX 0
#define COLOR_ARRAY 0
#define VAL_D 1

static inline unsigned long naive_scan_or(unsigned long * _input_array, unsigned int _nbits, unsigned long a /* inclusive */, unsigned long b /* exclusive */) {
    /* naive scan through the range [a, b) */
    unsigned long bmask = 1ul << (_nbits - 1);
    unsigned long res = 0;
    for (unsigned long i = a; i < b; ++i) {
        res |= _input_array[i];
    }
    return ((res & bmask) > 0);
}

static inline unsigned long naive_scan_and(unsigned long * _input_array, unsigned int _nbits, unsigned long a /* inclusive */, unsigned long b /* exclusive */) {
    /* naive scan through the range [a, b) */
    unsigned long bmask = 1ul << (_nbits - 1);
    unsigned long res = 1ul << (_nbits - 1);
    for (unsigned long i = a; i < b; ++i) {
        res &= _input_array[i];
    }
    return ((res & bmask) > 0);
}

static inline int check_result(unsigned long a, unsigned long b, unsigned long res_rbo, unsigned long res_naive) {
    if (res_rbo != res_naive) {
        throw(Wrong_RBO(a, b, res_rbo, res_naive));
    } else {
#if 0
        if (res_naive == 0) {
            printf("RBO(%lu, %lu) : res_idx = %lu, res_bv = %lu, res_naive = %lu\n",
                     a, b, res_idx, res_bv, res_naive);
        }
#endif
    }
    return 0;
}

int main (int argc, char * argv[]) {
    if (argc < 2) {
        printf("argc < 2, quit! \n");
        exit(EXIT_FAILURE);
    }
    unsigned long size = (unsigned long)atoi(argv[1]);
    size = pow2(size);
    // unsigned long size = (unsigned long)atoi(argv[1]);
    unsigned long * input_array = new unsigned long[size];
    unsigned long bmask = 1ul << (NBITS - 1);
    /* initialize the input array with random 1/0 */
    for (unsigned long i = 0; i < size; ++i) {
        /* make it containing significant number of '0' */
        // input_array[i] = (rand() & bmask);
        input_array[i] = (rand() % 8 == 0);
    }
#define min(a, b) ((a) < (b) ? (a) : (b))
#define INF 10000000000
    struct timeval start, end;
    double sum_rbo_tdiff = 0, sum_naive_tdiff = 0;

    gettimeofday(&start, 0);
#if IDX
    RBO_idx rbo(input_array, size, NBITS);
#endif
#if BVECTOR
    RBO_bvector rbo(input_array, size, NBITS);
#endif
#if COLOR_ARRAY
    RBO_color_array rbo(input_array, size, NBITS);
#endif
#if VAL_D
    RBO_counter_d<1, 1> rbo(NBITS, input_array, size);
#endif
    gettimeofday(&end, 0);
    printf("RBO create takes : %.3f ms\n", 1.0e3 * tdiff(&end, &start));

    /* perform some random queries */
#define TIMES 9111
    for (unsigned int i = 0; i < TIMES; ++i) {
        unsigned long a = rand() % size, b = rand() % size;
        unsigned long _a = (a <= b) ? a : b;
        unsigned long _b = (a <= b) ? b : a;
        gettimeofday(&start, 0);
        unsigned long res_rbo = rbo.query_or(_a, _b+1);
        gettimeofday(&end, 0);
        sum_rbo_tdiff += (1.0e3 * tdiff(&end, &start));
        gettimeofday(&start, 0);
        unsigned long res_naive = naive_scan_or(input_array, NBITS, _a, _b+1);
        gettimeofday(&end, 0);
        sum_naive_tdiff += (1.0e3 * tdiff(&end, &start));
        try {
            check_result(_a, _b+1, res_rbo, res_naive);
        } catch (Wrong_RBO & wrong_result) {
            printf("RBO query takes : %.6f ms, naive scan takes : %.6f ms\n", 
                    sum_rbo_tdiff/(i+1), sum_naive_tdiff/(i+1));
            wrong_result.print_errmsg();
            /* output the RBO data structure!!! */
            // cout << rbo << endl;
            rbo.print_range(wrong_result.a_, wrong_result.b_);
            unsigned long i = 0;
            for (i = wrong_result.a_; i < wrong_result.b_ - 1; ++i) {
                printf("[%lu]\t", input_array[i]);
            }
            printf("[%lu]\n", input_array[i]);
            delete [] input_array;
            exit(EXIT_FAILURE);
        }
    }
    printf("RBO passed, array_size (%lu)!!\n", size);
    printf("RBO query takes : %.6f ms, naive scan takes : %.6f ms\n", 
            sum_rbo_tdiff/TIMES, sum_naive_tdiff/TIMES);
    delete [] input_array;
    return 0;
}
