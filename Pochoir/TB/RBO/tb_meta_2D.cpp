/*
 * ============================================================================
 *
 *       Filename:  tb_meta.cpp
 *
 *    Description:  test bench for 1D meta-algo
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
// #include "lib_init_2D.hpp"
#include "lib_meta_2D.hpp"

using namespace std;

#define N_RANK 2

template <typename F, typename T>
static inline T naive_scan(F f, T * _input_array, size_t (&a)[N_RANK] /* inclusive */, size_t (&b)[N_RANK] /* exclusive */, size_t (&stride)[N_RANK]) {
    /* naive scan through the range [a, b) */
    const size_t stride_1 = stride[1];
    const size_t stride_0 = stride[0];
    size_t l_addr = a[1] * stride_1 + a[0] * stride_0;
    T res = _input_array[l_addr];
    l_addr += stride_0;
    for (size_t j = a[0] + 1; j < b[0]; ++j,
            l_addr += stride_0) {
        res = f(res, _input_array[l_addr]);
    }
    for (size_t i = a[1] + 1; i < b[1]; ++i) {
        l_addr = i * stride_1 + a[0] * stride_0;
        for (size_t j = a[0]; j < b[0]; ++j,
                l_addr += stride_0) {
            res = f(res, _input_array[l_addr]);
        }
    }
    return res;
}

template <typename T>
static inline int check_result(size_t (&a)[N_RANK], size_t (&b)[N_RANK], T res_meta, T res_naive) {
    if (res_meta != res_naive) {
        throw(Wrong_RBO<T_Data, N_RANK>(a, b, res_meta, res_naive));
    } else {
#ifdef DEBUG
        cout << "res_meta[[" << a[1] << ", " << a[0] << "], " 
             << "[" << b[1] << ", " << b[0] << "]] == " 
             << "res_naive[[" << a[1] << ", " << a[0] << "], " 
             << "[" << b[1] << ", " << b[0] << "]] == " 
             << res_meta << endl;
#endif
    }
    return 0;
}

int main (int argc, char * argv[]) {
    if (argc < 3) {
        printf("argc < 3, quit! \n");
        exit(EXIT_FAILURE);
    }
    size_t size[N_RANK];
    size[1] = (size_t)atoi(argv[1]);
    size[0] = (size_t)atoi(argv[2]);
    size[1] = (size[1] % 2 == 1 ? ++size[1] : size[1]);
    size[0] = (size[0] % 2 == 1 ? ++size[0] : size[0]);
#if 0
    size[1] = pow2(size[1]); 
    size[0] = pow2(size[0]);
#endif
    size_t stride[N_RANK];
    stride[1] = size[0]; stride[0] = 1;
    // unsigned long size = (unsigned long)atoi(argv[1]);
    T_Data * input_array = new T_Data[size[1] * size[0]];
    /* initialize the input array with random 1/0 */
    for (size_t i = 0; i < size[1]; ++i) {
        size_t l_stride = i * size[0];
        for (size_t j = 0; j < size[0]; ++j) {
            /* make it containing significant number of '0' */
            // input_array[i] = (rand() & bmask);
            input_array[l_stride + j] = (rand() % 8);
        }
    }
#define min(a, b) ((a) < (b) ? (a) : (b))
#define INF 10000000000
    struct timeval start, end;
    double sum_meta_tdiff = 0, sum_naive_tdiff = 0;

    function<T_Data (T_Data, T_Data)> op = [](T_Data x, T_Data y) { return (x+y); };
    gettimeofday(&start, 0);
    Meta<T_Data, 2, 1> meta(op, input_array, size[1], size[0]);
    gettimeofday(&end, 0);
    printf("Meta-algo preprocessing takes : %.3f ms\n", 1.0e3 * tdiff(&end, &start));

    /* perform some random queries */
#if 1
    #define TIMES 1555
#else
    unsigned long TIMES = size[1] * size[1] * size[0] * size[0];
#endif
    for (size_t i = 0; i < TIMES; ++i) {
        size_t a[N_RANK], b[N_RANK], _a[N_RANK], _b[N_RANK];
        a[1] = rand() % size[1]; a[0] = rand() % size[0];
        b[1] = rand() % size[1]; b[0] = rand() % size[0];
        _a[1] = (a[1] <= b[1]) ? a[1] : b[1];
        _b[1] = (a[1] <= b[1]) ? b[1] : a[1];
        _a[0] = (a[0] <= b[0]) ? a[0] : b[0];
        _b[0] = (a[0] <= b[0]) ? b[0] : a[0];
        ++_b[0]; ++_b[1];

        gettimeofday(&start, 0);
        size_t res_meta = meta.query(_a, _b);
        gettimeofday(&end, 0);
        sum_meta_tdiff += (1.0e3 * tdiff(&end, &start));
        gettimeofday(&start, 0);
        size_t res_naive = naive_scan(op, input_array, _a, _b, stride);
        gettimeofday(&end, 0);
        sum_naive_tdiff += (1.0e3 * tdiff(&end, &start));
        try {
            check_result(_a, _b, res_meta, res_naive);
        } catch (Wrong_RBO<T_Data, 2> & wrong_result) {
            printf("Meta-algo query takes : %.6f ms, naive scan takes : %.6f ms\n", 
                    sum_meta_tdiff/(i+1), sum_naive_tdiff/(i+1));
            wrong_result.print_errmsg();
            /* output the meta-data structure!!! */
            cout << meta << endl;
            meta.print_range(wrong_result.a_, wrong_result.b_);
#ifdef DEBUG
            // cout << meta;
#endif
            delete [] input_array;
            exit(EXIT_FAILURE);
        }
    }
    printf("Meta-algo PASSED, array_size (%lu x %lu)!!\n", size[1], size[0]);
    printf("Meta-algo query takes : %.6f ms, naive scan takes : %.6f ms\n", 
            sum_meta_tdiff/TIMES, sum_naive_tdiff/TIMES);
#ifdef DEBUG
    // cout << meta;
#endif
    delete [] input_array;
    return 0;
}
