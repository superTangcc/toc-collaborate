/*
 * ============================================================================
 *
 *       Filename:  tb_rbo_3D.cpp
 *
 *    Description:  test bench for 3d-dimensional RBO
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
#include "lib_rbo_counter_d.hpp"

using namespace std;
#define NBITS 1
#define N_RANK 3

static inline unsigned long naive_scan_or(unsigned long * _input_array, unsigned int _nbits, unsigned long (&a)[N_RANK] /* inclusive */, unsigned long (&b)[N_RANK] /* exclusive */, unsigned long (&size)[N_RANK]) {
    /* naive scan through the range [a, b) */
    unsigned long bmask = 1ul << (_nbits - 1);
    unsigned long res = 0;
    for (unsigned long k = a[2]; k < b[2]; ++k) {
        for (unsigned long j = a[1]; j < b[1]; ++j) {
    for (unsigned long i = a[0]; i < b[0]; ++i) {
            res |= _input_array[k * size[1] * size[0] + j * size[0] + i];
    } } }
    return ((res & bmask) > 0);
}

static inline int check_result(unsigned long (&a)[N_RANK], unsigned long (&b)[N_RANK], unsigned long res_rbo, unsigned long res_naive) {
    if (res_rbo != res_naive) {
        throw(Wrong_RBO<N_RANK>(a, b, res_rbo, res_naive));
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
    if (argc < N_RANK+1) {
        printf("argc < %d, quit! \n", N_RANK+1);
        exit(EXIT_FAILURE);
    }
    unsigned long size[N_RANK];
    size[2] = (unsigned long)atoi(argv[1]);
    size[1] = (unsigned long)atoi(argv[2]);
    size[0] = (unsigned long)atoi(argv[3]);
    // size[2] = pow2(size[2]);
    // size[1] = pow2(size[1]);
    // size[0] = pow2(size[0]);
    unsigned long * input_array = new unsigned long[size[2] * size[1] * size[0]];
    unsigned long bmask = 1ul << (NBITS - 1);
    /* initialize the input array with random 1/0 */
    for (unsigned long k = 0; k < size[2]; ++k) {
        for (unsigned long j = 0; j < size[1]; ++j) {
    for (unsigned long i = 0; i < size[0]; ++i) {
        /* make it containing significant number of '0' */
        // input_array[i] = (rand() & bmask);
        input_array[k * size[1] * size[0] + j * size[0] + i] = (rand() % 8 == 0);
    } } }
#define min(a, b) ((a) < (b) ? (a) : (b))
#define INF 10000000000
    struct timeval start, end;
    double sum_rbo_tdiff = 0, sum_naive_tdiff = 0;

    gettimeofday(&start, 0);
    RBO_counter_d<N_RANK, 1> rbo(NBITS, input_array, size[2], size[1], size[0]);
    gettimeofday(&end, 0);
    printf("RBO create takes : %.3f ms\n", 1.0e3 * tdiff(&end, &start));

    /* perform some random queries */
#define TIMES 9111
    for (unsigned int i = 0; i < TIMES; ++i) {
        unsigned long a[N_RANK], b[N_RANK], _a[N_RANK], _b[N_RANK];
        a[2] = rand() % size[2]; a[1] = rand() % size[1]; a[0] = rand() % size[0];
        b[2] = rand() % size[2]; b[1] = rand() % size[1]; b[0] = rand() % size[0];
        _a[2] = (a[2] <= b[2]) ? a[2] : b[2];
        _b[2] = (a[2] <= b[2]) ? b[2] : a[2];
        _a[1] = (a[1] <= b[1]) ? a[1] : b[1];
        _b[1] = (a[1] <= b[1]) ? b[1] : a[1];
        _a[0] = (a[0] <= b[0]) ? a[0] : b[0];
        _b[0] = (a[0] <= b[0]) ? b[0] : a[0];
        ++_b[0]; ++_b[1]; ++_b[2];
        gettimeofday(&start, 0);
        unsigned long res_rbo = rbo.query_or(_a, _b);
        gettimeofday(&end, 0);
        sum_rbo_tdiff += (1.0e3 * tdiff(&end, &start));
        gettimeofday(&start, 0);
        unsigned long res_naive = naive_scan_or(input_array, NBITS, _a, _b, size);
        gettimeofday(&end, 0);
        sum_naive_tdiff += (1.0e3 * tdiff(&end, &start));
        try {
            check_result(_a, _b, res_rbo, res_naive);
        } catch (Wrong_RBO<N_RANK> & wrong_result) {
            printf("RBO query takes : %.6f ms, naive scan takes : %.6f ms\n", 
                    sum_rbo_tdiff/(i+1), sum_naive_tdiff/(i+1));
            wrong_result.print_errmsg();
            /* output the RBO data structure!!! */
            cout << rbo << endl;
            // rbo.print_range(_a, _b);
            for (unsigned long k = _a[2]; k < _b[2]; ++k) {
                for (unsigned long j = _a[1]; j < _b[1]; ++j) {
            unsigned long i;
            for (i = _a[0]; i < _b[0]-1; ++i) {
                cout << "[" << input_array[k * size[1] * size[0] + j * size[0] + i] << "], ";
            }
            cout << "[" << input_array[k * size[1] * size[0] + j * size[0] + i] << "]\n";
            }
            cout << "\n------------------------------------------------------------------\n";
            }

            delete [] input_array;
            exit(EXIT_FAILURE);
        }
    }
    printf("RBO passed, array_size (%lu, %lu, %lu)!!\n", size[2], size[1], size[0]);
    printf("RBO query takes : %.6f ms, naive scan takes : %.6f ms\n", 
            sum_rbo_tdiff/TIMES, sum_naive_tdiff/TIMES);
    delete [] input_array;
    return 0;
}
