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
// #include "lib_init.hpp"
#include "lib_meta_1D.hpp"

using namespace std;

template <typename F, typename T>
static inline T naive_scan(F f, T * _input_array, size_t (&a)[1] /* inclusive */, size_t (&b)[1] /* exclusive */) {
    /* naive scan through the range [a, b) */
    T res = _input_array[a[0]];
    for (size_t i = a[0]+1; i < b[0]; ++i) {
        res = f(res,_input_array[i]);
    }
    return res;
}

template <typename T>
static inline int check_result(size_t (&a)[1], size_t (&b)[1], T res_meta, T res_naive) {
    if (res_meta != res_naive) {
        throw(Wrong_RBO<T_Data, 1>(a, b, res_meta, res_naive));
    } else {
#ifdef DEBUG
        cout << "res_meta[" << a[0] << ", " << b[0] << "] == " 
             << "res_naive[" << a[0] << ", " << b[0] << "] == " 
             << res_meta << endl;
#endif
    }
    return 0;
}

int main (int argc, char * argv[]) {
    if (argc < 2) {
        printf("argc < 2, quit! \n");
        exit(EXIT_FAILURE);
    }
    size_t size = (size_t)atoi(argv[1]);
    size = (size & 0x1 ? ++size : size);
    T_Data * input_array = new T_Data[size];
    /* initialize the input array with random 1/0 */
    for (size_t i = 0; i < size; ++i) {
        /* make it containing significant number of '0' */
        // input_array[i] = (rand() & bmask);
        input_array[i] = (rand() % 8);
    }
#define min(a, b) ((a) < (b) ? (a) : (b))
#define INF 10000000000
    struct timeval start, end;
    double sum_meta_tdiff = 0, sum_naive_tdiff = 0;

    function<T_Data (T_Data, T_Data)> op = [](T_Data x, T_Data y) { return (x+y); };
    gettimeofday(&start, 0);
    /* Preprocess the entire 1D array */
    Meta<T_Data, 1, 2> meta(op, input_array, size);
    gettimeofday(&end, 0);
    printf("Meta-algo preprocessing takes : %.3f ms\n", 1.0e3 * tdiff(&end, &start));

    /* perform some random queries */
#define TIMES 1555
    for (int i = 0; i < TIMES; ++i) {
        /* generate an arbitrary range _a[], _b[] */
        size_t a = rand() % size, b = rand() % size;
        size_t _a[1], _b[1];
        _a[0] = (a <= b) ? a : b;
        _b[0] = (a <= b) ? b : a;
        ++_b[0];
        gettimeofday(&start, 0);
        /* Query the range [_a, _b) */
        size_t res_meta = meta.query(_a, _b);
        gettimeofday(&end, 0);
        sum_meta_tdiff += (1.0e3 * tdiff(&end, &start));
        gettimeofday(&start, 0);
        size_t res_naive = naive_scan(op, input_array, _a, _b);
        gettimeofday(&end, 0);
        sum_naive_tdiff += (1.0e3 * tdiff(&end, &start));
        try {
            check_result(_a, _b, res_meta, res_naive);
        } catch (Wrong_RBO<T_Data, 1> & wrong_result) {
            printf("Meta-algo query takes : %.6f ms, naive scan takes : %.6f ms\n", 
                    sum_meta_tdiff/(i+1), sum_naive_tdiff/(i+1));
            wrong_result.print_errmsg();
            /* output the meta-data structure!!! */
            // cout << meta << endl;
            // meta.print_range(wrong_result.a_, wrong_result.b_);
            size_t i = 0;
            for (i = wrong_result.a_[0]; i < wrong_result.b_[0]; ++i) {
                printf("[%lu]\t", input_array[i]);
            }
            printf("\n");
#ifdef DEBUG
            cout << meta;
#endif
            delete [] input_array;
            exit(EXIT_FAILURE);
        }
    }
    printf("Meta-algo PASSED, array_size (%lu)!!\n", size);
    printf("Meta-algo query takes : %.6f ms, naive scan takes : %.6f ms\n", 
            sum_meta_tdiff/TIMES, sum_naive_tdiff/TIMES);
#ifdef DEBUG
    // cout << meta;
#endif
    delete [] input_array;
    return 0;
}
