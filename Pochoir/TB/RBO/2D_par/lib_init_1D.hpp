/*
 * ============================================================================
 *
 *       Filename:  lib_init_1D.hpp
 *
 *    Description:  init-algorithm for 1D partial sum query,
 *                  which will serve as the input algorithm to our meta-algo
 *
 *        Version:  1.0
 *        Created:  06/13/2012 04:41:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#ifndef LIB_INIT_1D_HPP
#define LIB_INIT_1D_HPP

#include <cstdio>
#include <cstdlib>
#include <cstddef> 
#include <cassert>
#include <iostream>
#include <functional>

#include "lib_common.hpp"

using namespace std;

/* N_RANK: dimensionality
 * T: type of the semi-group */
template <typename T, int N_RANK>
struct Init_Algo {
    private:
        typedef function<T (T, T)> T_Op;
        T_Op op_;
        T * input_array_;
        T ** pp_array_; // preprocessing array
        bool stride_set_;
        size_t stride_[N_RANK];
        size_t input_size_[N_RANK], total_size_;
        size_t lca_size_, level_;
    public:
        inline T query(size_t (&lo)[N_RANK] /* inclusive */, size_t (&hi)[N_RANK] /* exclusive */) { }
        Init_Algo(void) { return; }
        template <typename F, typename ... IS>
        Init_Algo(F _op, T * _input_array, IS ... _sizes) : input_array_(_input_array) { }
        ~Init_Algo() { }
        template <typename ... IS>
        void set_stride(IS ... _strides) { }
        void print_info(void) { }
        void print_range(size_t * _begin, size_t * _end) { }
        friend ostream & operator<<(ostream & fs, Init_Algo<T, N_RANK> const & init_algo) { return fs; }
};

template <typename T>
struct Init_Algo <T, 1> {
    private:
        typedef function<T (T, T)> T_Op;
        T_Op op_; // op_ is the partial sum operator
        T * input_array_;
        T ** pp_array_; // preprocessing array
        bool stride_set_;
        size_t stride_[1];
        size_t input_size_[1], total_size_;
        size_t thres_;
        size_t lca_size_, level_;
        template <typename I>
        inline void init_sizes(I _size) {
            input_size_[0] = _size; 
            if (!stride_set_)
                stride_[0] = 1;
            total_size_ = _size; 
            level_ = log2_ceil(input_size_[0]);
            lca_size_ = pow2(level_);

            return;
        }

        /* init preprocessing arrays */
        inline void init_pp(void) {
            pp_array_ = new T*[level_];
            // cilk_for (size_t i = 0; i < level_; ++i) {
// #pragma omp parallel for
            for (size_t i = 0; i < level_; ++i) {
                pp_array_[i] = new T[total_size_];
                init_pp_i(i);
            }

            return;
        }
        
        inline void init_pp_i(size_t _i) {
            size_t begin_idx = pow2(_i);
            size_t end_idx = pow2(_i+1);
            const size_t l_stride = stride_[0];

            /* cilk_for at this level may be too fine-grain!? */
            for (size_t i = begin_idx; i < end_idx; ++i) {
                int l_begin_range, l_end_range, l_mid_point;
                int begin_range, end_range, mid_point;
                size_t shift_in_bits = level_ + 1 - msb_pos(i);
                l_begin_range = (i << shift_in_bits) - lca_size_;
                l_end_range = ((i << shift_in_bits) | ((1ul << shift_in_bits) - 1)) - lca_size_;
                l_mid_point = (l_end_range + l_begin_range + 1) >> 1;
                if (l_begin_range < input_size_[0]) {
                    begin_range = l_begin_range;
                    end_range = l_end_range > (input_size_[0]-1) ? (input_size_[0]-1) : l_end_range;
                    mid_point = l_mid_point;
                    if (mid_point - 1 >= begin_range
                            && mid_point <= input_size_[0]) {
                        pp_array_[_i][mid_point-1] = input_array_[(mid_point-1) * l_stride];
                    }
                    if (mid_point <= end_range 
                            && mid_point <= input_size_[0]-1) {
                        pp_array_[_i][mid_point] = input_array_[mid_point * l_stride];
                    }
                    /* possibly merge the below 2 loops in the future */
                    /* data reduction for suffix */
                    int j = min (mid_point-2, (int)input_size_[0]-2);
                    // for this level of parallelization, we can use
                    // cilk_spawn without cilk_sync
                    // cilk_spawn reduce_suffix(_i, j, begin_range);
                    reduce_suffix(_i, j, begin_range);
                    /* data reduction for prefix */
                    j = mid_point+1;
                    reduce_prefix(_i, j, end_range);
                    // cilk_sync;
                } /* end if (l_begin_range < input_size_[0]) */
                else {
                    /* we cannot return directly in a cilk_for loop */
                    // return;
                }
            }

            return;
        }

        inline void reduce_suffix(size_t _i, int j, int begin_range) {
            /* input parameters:
             * _i : level
             * j : indices
             */
            const size_t l_stride = stride_[0];
            size_t l_addr = j * l_stride;
            for ( ; j >= begin_range; --j, l_addr -= l_stride) {
                pp_array_[_i][j] = op_(pp_array_[_i][j+1], input_array_[l_addr]);
            }
            return;
        }

        inline void reduce_prefix(size_t _i, int j, int end_range) {
            /* input parameters:
             * _i : level
             * j : indices
             */
            const size_t l_stride = stride_[0];
            size_t l_addr = j * l_stride;
            for ( ; j <= end_range; ++j, l_addr += l_stride) {
                pp_array_[_i][j] = op_(pp_array_[_i][j-1], input_array_[l_addr]);
            }
            return;
        }
    public:
        inline T query(size_t (&lo)[1] /* inclusive */, size_t (&hi)[1] /* exclusive */) {
            /* query the range [lo, hi) => [l_lo, l_hi] */
            T res;
            if (total_size_ <= thres_ || (hi[0] - lo[0]) <= thres_) {
                /* for extremely small-sized array, we just scan through 
                 */
                const size_t l_stride = stride_[0];
                T res = input_array_[lo[0] * l_stride];
                size_t l_addr = (lo[0]+1) * l_stride;
                for (int i = lo[0]+1; i < hi[0];
                        ++i, l_addr += l_stride) {
                    res = op_(res, input_array_[l_addr]);
                }
                return res;
            }
           
            size_t l_lo = lo[0], l_hi = hi[0] - 1;
            size_t l_lca = lca((l_lo + lca_size_), (l_hi + lca_size_)), l_level = msb_pos(l_lca)-1;
            l_level = l_level == level_ ? l_level - 1 : l_level;
            if (l_lo == l_hi) 
                res = pp_array_[l_level][l_lo];
            else
                res = op_(pp_array_[l_level][l_lo], pp_array_[l_level][l_hi]); 

            return res;
        }
        template <typename I>
        inline void set_stride(I _stride) { 
            /* this function could be used to overwrite
             * the stride_[] set by init_sizes()
             */
            stride_[0] = _stride;
            stride_set_ = true;
            return;
        }
        template <typename I>
        inline void preprocess(T_Op _op, T * _input_array, I _size) {
            op_ = _op; // this is the operator for partial sum
            input_array_ = _input_array;
            init_sizes(_size);
            // since this is 1D case
            assert(total_size_ == input_size_[0]);
            if (total_size_ <= thres_)
                return;
            init_pp();

            return;
        }
        Init_Algo(void) : stride_set_(false) { 
            pp_array_ = NULL;
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            return; 
        }
        template <typename I>
        Init_Algo(T_Op _op, T * _input_array, I _size) : input_array_(_input_array), stride_set_(false) {
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            op_ = _op; // this is the operator for partial sum
            init_sizes(_size);
            // since this is 1D case
            assert(total_size_ == input_size_[0] || total_size_ == input_size_[0] + 1);
            if (total_size_ <= thres_)
                return;
            init_pp();

            return;
        }
        ~Init_Algo() {
            /* release all the memory */
            if (pp_array_ != NULL) {
                for (size_t i = 0; i < level_; ++i) {
                    delete [] pp_array_[i];
                }
            }
            delete [] pp_array_;

            return;
        }
        void print_info(void) {
            cout << "\nInit_Algo (input size = " << input_size_[0] << ")\n";
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        void print_range(size_t (&lo)[1], size_t (&hi)[1]) {
            cout << "\nInit_Algo (input size = " << input_size_[0] << ")\n";
            cout << "-----------------------------------------------------------------------\n";
            size_t l_lo = lo[0], l_hi = hi[0];
            size_t l_lca = lca(l_lo, l_hi), l_level = msb_pos(l_lca) - 1;
            cout << "Input Array: [";
            const size_t l_stride = stride_[0];
            size_t l_addr = l_lo * l_stride;
            for (size_t i = l_lo; i < l_hi-1; 
                    ++i, l_addr += l_stride) {
                cout << input_array_[l_addr] << ", ";
            }
            cout << input_array_[l_addr] << "] ";
            cout << "\n-----------------------------------------------------------------------\n";
            cout << "level " << l_level << ": [";
            for (size_t i = l_lo; i < l_hi-1; ++i) {
                cout << pp_array_[l_level][i] << ", ";
            }
            cout << pp_array_[l_level][l_hi-1] << "] ";
            cout << "\n-----------------------------------------------------------------------\n";

            return;
        }
        friend ostream & operator<<(ostream & fs, Init_Algo<T, 1> const & init_algo) {
            size_t l_lo = 0, l_hi = init_algo.input_size_[0]-1;
            const size_t l_stride = init_algo.stride_[0];
            fs << "\nInit_Algo (input size = " << init_algo.total_size_ << ")\n";
            fs << "-----------------------------------------------------------------------\n";
            fs << "Input Array: [";
            size_t l_addr = l_lo * l_stride;
            for (size_t i = l_lo; i < l_hi; 
                    ++i, l_addr += l_stride) {
                fs << init_algo.input_array_[l_addr] << ", ";
            }
            fs << init_algo.input_array_[l_addr] << "] ";
            fs << "\n-----------------------------------------------------------------------\n";
            for (size_t l = 0; l < init_algo.level_; ++l) {
                size_t l_level = init_algo.level_ - 1 - l;
                fs << "level " << l_level << ": [";
                for (size_t i = l_lo; i < l_hi; ++i) {
                    fs << init_algo.pp_array_[l_level][i] << ", ";
                }
                fs << init_algo.pp_array_[l_level][l_hi] << "] ";
                fs << "\n-----------------------------------------------------------------------\n";
            }

            return fs;
        }
};
#endif // LIB_INIT_1D_HPP
