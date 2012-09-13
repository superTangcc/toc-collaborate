/*
 * ============================================================================
 *
 *       Filename:  lib_init_2D.hpp
 *
 *    Description:  init-algorithm for 2D partial sum query,
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

#ifndef LIB_INIT_2D_HPP
#define LIB_INIT_2D_HPP

#include <cstdio>
#include <cstdlib>
#include <cstddef> 
#include <cassert>
#include <iostream>
#include <functional>

#include "lib_common.hpp"
#include "lib_init_1D.hpp"

using namespace std;

/* N_RANK: dimensionality
 * T: type of the semi-group */
template <typename T>
struct Init_Algo <T, 2> {
    private:
        typedef function<T (T, T)> T_Op;
        typedef Init_Algo<T, 1> T_Input_1D_Algo;
        T_Op op_; // op_ is the partial sum operator
        /* input_1D_algo_ will be 1D algo */
        T_Input_1D_Algo ** input_1D_algo_;

        T * input_array_;
        // preprocessing array which stores the results of data reduction
        T ** pp_array_; 
        unsigned short cut_dim_, red_dim_;
        bool stride_set_, dim_set_;
        size_t stride_[2];
        size_t input_size_[2], total_size_;
        size_t thres_;
        size_t lca_size_, level_;
        template <typename I>
        inline void init_sizes(I _size) {
            input_size_[0] = _size; 
            if (!stride_set_)
                stride_[0] = 1;
            total_size_ = _size; 
            for (int i = 1; i < 2; ++i) {
                if (!stride_set_) 
                    stride_[i] = input_size_[i-1] * stride_[i-1];
                total_size_ *= input_size_[i];
            }
            assert(total_size_ == input_size_[1] * input_size_[0]);

            if (!dim_set_) {
                if (input_size_[1] >= input_size_[0]) {
                    cut_dim_ = 1; red_dim_ = 0;
                } else {
                    assert(input_size_[1] < input_size_[0]);
                    cut_dim_ = 0; red_dim_ = 1;
                }
            }
            level_ = log2_ceil(input_size_[cut_dim_]);
            lca_size_ = pow2(level_);

            return;
        }
        template <typename I, typename ... IS>
        inline void init_sizes(I _size, IS ... _sizes) {
            unsigned int l_dim = sizeof...(IS);
            input_size_[l_dim] = _size;
            init_sizes(_sizes ...);
            return;
        }

        /* init preprocessing arrays */
        inline void init_pp(void) {
            pp_array_ = new T*[level_];
            input_1D_algo_ = new T_Input_1D_Algo*[level_];
            for (size_t i = 0; i < level_; ++i) {
                pp_array_[i] = new T[total_size_];
                /* a re-arrangement of pp_array[]'s stride to make
                 * the 1D preprocessing on it more cache-friendly
                 */
                const size_t pp_cut_stride = input_size_[red_dim_];
                const size_t pp_red_stride = 1;
                /* init_pp_i() do the data reduction of each level */
                init_pp_i(i);
                input_1D_algo_[i] = new T_Input_1D_Algo[input_size_[cut_dim_]];
                for (size_t j = 0; j < input_size_[cut_dim_]; ++j) {
                    /* do the preprocessing along red_dim_ of pp_array_[] */
                    input_1D_algo_[i][j].preprocess(op_, pp_array_[i] + j * pp_cut_stride, input_size_[red_dim_]);
                }
            }

            return;
        }
        
        /* init_pp_i() do the data reduction of each level */
        inline void init_pp_i(size_t _i) {
            size_t begin_idx = pow2(_i);
            size_t end_idx = pow2(_i+1);
            int begin_range, end_range, mid_point;
            const size_t cut_stride = stride_[cut_dim_];
            const size_t red_stride = stride_[red_dim_];
            const size_t pp_cut_stride = input_size_[red_dim_];
            const size_t pp_red_stride = 1;

            for (size_t i = begin_idx; i < end_idx; ++i) {
                int l_begin_range, l_end_range, l_mid_point;
                size_t shift_in_bits = level_ + 1 - msb_pos(i);
                l_begin_range = (i << shift_in_bits) - lca_size_;
                l_end_range = ((i << shift_in_bits) | ((1ul << shift_in_bits) - 1)) - lca_size_;
                l_mid_point = (l_end_range + l_begin_range + 1) >> 1;
                if (l_begin_range < input_size_[cut_dim_]) {
                    begin_range = l_begin_range;
                    end_range = l_end_range > (input_size_[cut_dim_]-1) ? (input_size_[cut_dim_]-1) : l_end_range;
                    mid_point = l_mid_point;
                    /* this branch will yield 20% performance improvement
                     * in preprocessing stage compared with above branch
                     * when the problem size is 2^11 x 2^11
                     */
                    size_t l_pp_addr = (mid_point-1) * pp_cut_stride;
                    size_t l_addr = (mid_point-1) * cut_stride;
                    if (mid_point - 1 >= begin_range
                            && mid_point <= end_range) {
                        /* the most common case: */
                        /* fill in the mid_point - 1 & mid_point */
                        for (size_t j = 0; j < input_size_[red_dim_]; ++j,
                                l_pp_addr += pp_red_stride,
                                l_addr += red_stride) {
                            pp_array_[_i][l_pp_addr] = 
                                input_array_[l_addr];
                            pp_array_[_i][l_pp_addr + pp_cut_stride] = 
                                input_array_[l_addr + cut_stride];
                        }
                    } else if (mid_point - 1 >= begin_range
                            && mid_point - 1 <= end_range) {
                        /* just fill in the mid_point-1 */
                        // l_pp_addr += pp_cut_stride;
                        // l_addr += cut_stride;
                        for (size_t j = 0; j < input_size_[red_dim_]; ++j,
                                l_pp_addr += pp_red_stride,
                                l_addr += red_stride) {
                            pp_array_[_i][l_pp_addr] = 
                                input_array_[l_addr];
                        }
                    }

                    /* possibly merge the below 2 loops in the future */
                    size_t l_pp_addr_1, l_addr_1;
                    int k = mid_point-2, k1 = mid_point+1, i = 0;
                    k = min (k, end_range-1);
                    // k1 = min (k1, end_range);
#if 1
                    int len_0 = k-begin_range;
                    int len_1 = end_range-k1;
                    int len = min(len_0, len_1) + 1;
                    size_t l_k_pp_base = k * pp_cut_stride,
                           l_k_base = k * cut_stride;
                    size_t l_k1_pp_base = k1 * pp_cut_stride,
                           l_k1_base = k1 * cut_stride;
                    for ( ; i < len; --k, ++k1, ++i,
                            l_k_pp_base -= pp_cut_stride,
                            l_k_base -= cut_stride,
                            l_k1_pp_base += pp_cut_stride,
                            l_k1_base += cut_stride) {
                        l_pp_addr = l_k_pp_base;
                        l_addr = l_k_base;
                        l_pp_addr_1 = l_k1_pp_base;
                        l_addr_1 = l_k1_base;
                        for (size_t j = 0; j < input_size_[red_dim_]; ++j,
                            l_pp_addr += pp_red_stride,
                            l_addr += red_stride,
                            l_pp_addr_1 += pp_red_stride,
                            l_addr_1 += red_stride) {
                            /* do the data reduction */
                            pp_array_[_i][l_pp_addr] = 
                                op_(pp_array_[_i][l_pp_addr + pp_cut_stride], 
                                        input_array_[l_addr]);
                            pp_array_[_i][l_pp_addr_1] = 
                                op_(pp_array_[_i][l_pp_addr_1 - pp_cut_stride], 
                                        input_array_[l_addr_1]);
                        }
                    }
#endif
                    /* fill out the rest of prefix */
                    l_k1_pp_base = k1 * pp_cut_stride;
                    l_k1_base = k1 * cut_stride;
                    for ( ; k1 <= end_range; ++k1,
                            l_k1_pp_base += pp_cut_stride,
                            l_k1_base += cut_stride) {
                        l_pp_addr_1 = l_k1_pp_base;
                        l_addr_1 = l_k1_base;
                        for (size_t j = 0; j < input_size_[red_dim_]; ++j,
                            l_pp_addr_1 += pp_red_stride,
                            l_addr_1 += red_stride) {
                            pp_array_[_i][l_pp_addr_1] = 
                                op_(pp_array_[_i][l_pp_addr_1 - pp_cut_stride], 
                                        input_array_[l_addr_1]);
                        }
                    }

                    /* fill out the rest of suffix */
                    l_k_pp_base = k * pp_cut_stride;
                    l_k_base = k * cut_stride;
                    for ( ; k >= begin_range; --k,
                            l_k_pp_base -= pp_cut_stride,
                            l_k_base -= cut_stride) {
                        l_pp_addr = l_k_pp_base;
                        l_addr = l_k_base;
                        for (size_t j = 0; j < input_size_[red_dim_]; ++j,
                            l_pp_addr += pp_red_stride,
                            l_addr += red_stride) {
                            pp_array_[_i][l_pp_addr] = 
                                op_(pp_array_[_i][l_pp_addr + pp_cut_stride], 
                                        input_array_[l_addr]);

                        }
                    }
                } /* end if (l_begin_range <= input_size_[cut_dim_]-1) */
                else {
                    return;
                }
            }

            return;
        }
    public:
        inline T query(size_t (&lo)[2] /* inclusive */, size_t (&hi)[2] /* exclusive */) {
            /* query the range [lo, hi) => [l_lo, l_hi] */
            T res;
            if (((hi[1] - lo[1]) * (hi[0] - lo[0])) <= thres_) {
                /* for extremely small sized array, we just scan through 
                 */
                const size_t stride_1 = stride_[1];
                const size_t stride_0 = stride_[0];
                size_t l_addr = lo[1] * stride_1 + lo[0] * stride_0;
                res = input_array_[l_addr];
                l_addr += stride_0;
                for (size_t j = lo[0] + 1; j < hi[0]; ++j,
                        l_addr += stride_0) {
                    res = op_(res, input_array_[l_addr]);
                }
                for (size_t i = lo[1] + 1; i < hi[1]; ++i) {
                    l_addr = i * stride_1 + lo[0] * stride_0;
                    for (size_t j = lo[0]; j < hi[0]; ++j,
                            l_addr += stride_0) {
                        res = op_(res, input_array_[l_addr]);
                    }
                }

                return res;
            }

            size_t l_lo = lo[cut_dim_], l_hi = hi[cut_dim_] - 1;
            size_t l_lca = lca((l_lo + lca_size_), (l_hi + lca_size_)), l_level = msb_pos(l_lca)-1;
            l_level = (l_level == level_ ? l_level - 1 : l_level);
            size_t lo_red[1], hi_red[1];
            lo_red[0] = lo[red_dim_]; hi_red[0] = hi[red_dim_];
            if (l_lo == l_hi) { 
                /* Just curious if we directly plug in the 2D integer
                 * array into an argument which is supposed to be a 1D
                 * integer array, what will happen??
                 */
                res = input_1D_algo_[l_level][l_lo].query(lo_red, hi_red);
            } else {
                T res_lo = input_1D_algo_[l_level][l_lo].query(lo_red, hi_red);
                T res_hi = input_1D_algo_[l_level][l_hi].query(lo_red, hi_red);
                res = op_(res_lo, res_hi); 
            }

            return res;
        }
        inline void set_dim(unsigned int _cut_dim) {
            cut_dim_ = _cut_dim; red_dim_ = 1 - cut_dim_;
            dim_set_ = true;
        }
        template <typename I>
        inline void set_stride(I _stride) {
            stride_[0] = _stride;
            stride_set_ = true;
            return;
        }
        template <typename I, typename ... IS>
        inline void set_stride(I _stride, IS ... _strides) {
            unsigned int l_dim = sizeof...(IS);
            stride_[l_dim] = _stride;
            set_stride(_strides ...);
            return;
        }

        template <typename ... IS>
        inline void preprocess(T_Op _op, T * _input_array, IS ... _sizes) {
            input_array_ = _input_array;
            op_ = _op; // this is the operator for partial sum
            /* we now decide cut_dim_ and red_dim_ inside init_sizes
             */
            init_sizes(_sizes ...);
            if (total_size_ <= thres_)
                return;
            init_pp();

            return;
        }
        Init_Algo(void) : stride_set_(false), dim_set_(false) { 
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            thres_ = thres_ * thres_;
            return;
        }
        template <typename ... IS>
        Init_Algo(T_Op _op, T * _input_array, IS ... _sizes) : input_array_(_input_array), stride_set_(false), dim_set_(false) {
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            thres_ = thres_ * thres_;
            op_ = _op; // this is the operator for partial sum
            init_sizes(_sizes ...);
            if (total_size_ <= thres_)
                return;
            init_pp();

            return;
        }
        ~Init_Algo() {
            /* release all the memory */
            for (size_t i = 0; i < level_; ++i) {
                if (pp_array_ != NULL) 
                    delete [] pp_array_[i];
                if (input_1D_algo_ != NULL) 
                    delete [] input_1D_algo_[i];
            }
            delete [] pp_array_;
            delete [] input_1D_algo_;

            return;
        }
        void print_info(void) {
            cout << "\nInit_Algo (input size = " 
                 << input_size_[1] << " x " << input_size_[0] 
                 << ", cut dim : " << cut_dim_ << ")\n";
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        void print_range(size_t (&lo)[2] /* inclusive */, size_t (&hi)[2] /* exclusive */) {
            cout << "\nInit_Algo (input size = " 
                 << input_size_[1] << " x " << input_size_[0] 
                 << ", cut dim : " << cut_dim_ << ")\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "Input Array: " << endl;
            for (size_t i = lo[1]; i < hi[1]; ++i) {
                size_t l_addr = i * stride_[1] + lo[0] * stride_[0];
                for (size_t j = lo[0]; j < hi[0]-1; 
                        ++j, l_addr += stride_[0]) {
                    cout << input_array_[l_addr] << ", ";
                }
                cout << input_array_[l_addr] << endl;
            }
            cout << "-----------------------------------------------------------------------\n";
            size_t l_lca = lca(lo[cut_dim_] + lca_size_, hi[cut_dim_] + lca_size_), l_level = msb_pos(l_lca) - 1;
            const size_t pp_stride_1 = input_size_[red_dim_];
            const size_t pp_stride_0 = 1;
            l_level = (l_level == level_ ? l_level - 1 : l_level);
            cout << "level " << l_level << ": " << endl;
            for (size_t i = lo[1]; i < hi[1]; ++i) {
                size_t l_addr = i * pp_stride_1 + lo[0] * pp_stride_0;
                for (size_t j = lo[0]; j < hi[0]-1; 
                        ++j, l_addr += pp_stride_0) {
                    cout << pp_array_[l_level][l_addr] << ", ";
                }
                cout << pp_array_[l_level][l_addr] << endl;
            }
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        friend ostream & operator<<(ostream & fs, Init_Algo<T, 2> const & _init_algo) {
            fs << "\nInit_Algo (input size = " 
                 << _init_algo.input_size_[1] << " x " << _init_algo.input_size_[0] 
                 << ", cut dim : " << _init_algo.cut_dim_ << ")\n";
            fs << "-----------------------------------------------------------------------\n";
            fs << "Input Array: " << endl;
            for (size_t i = 0; i < _init_algo.input_size_[1]; ++i) {
                size_t l_addr = i * _init_algo.stride_[1];
                for (size_t j = 0; j < _init_algo.input_size_[0]-1; 
                        ++j, l_addr += _init_algo.stride_[0]) {
                    fs << _init_algo.input_array_[l_addr] << ", ";
                }
                fs << _init_algo.input_array_[l_addr] << endl;
            }
            fs << "-----------------------------------------------------------------------\n";
            for (size_t l = 0; l < _init_algo.level_; ++l) {
                size_t l_level = l;
                const size_t pp_cut_stride = _init_algo.input_size_[_init_algo.red_dim_];
                const size_t pp_red_stride = 1;
                fs << "level " << l_level << ": " << endl;
                for (size_t i = 0; i < _init_algo.input_size_[1]; ++i) {
                    size_t l_addr = i * pp_cut_stride;
                    for (size_t j = 0; j < _init_algo.input_size_[0]-1; 
                            ++j, l_addr += pp_red_stride) {
                        fs << _init_algo.pp_array_[l_level][l_addr] << ", ";
                    }
                    fs << _init_algo.pp_array_[l_level][l_addr] << endl;
                }
                fs << "-----------------------------------------------------------------------\n";
            }

            return fs;
        }
};
#endif // LIB_INIT_2D_HPP
