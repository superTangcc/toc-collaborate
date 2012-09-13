/*
 * ============================================================================
 *
 *       Filename:  lib_init_3D.hpp
 *
 *    Description:  init-algorithm for 3D partial sum query,
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

#ifndef LIB_INIT_3D_HPP
#define LIB_INIT_3D_HPP

#include <cstdio>
#include <cstdlib>
#include <cstddef> 
#include <cassert>
#include <iostream>
#include <functional>

#include "lib_common.hpp"
#include "lib_init_2D.hpp"

using namespace std;

/* N_RANK: dimensionality
 * T: type of the semi-group */
template <typename T>
struct Init_Algo <T, 3> {
    private:
        typedef function<T (T, T)> T_Op;
        typedef Init_Algo<T, 2> T_Input_2D_Algo;
        T_Op op_; // op_ is the partial sum operator
        /* input_2D_algo_ will be 2D algo */
        T_Input_2D_Algo ** input_2D_algo_;

        T * input_array_;
        // preprocessing array which stores the results of data reduction
        T ** pp_array_; 
        unsigned short cut_dim_, red_dim_[2];
        bool stride_set_, dim_set_;
        size_t stride_[3];
        size_t input_size_[3], total_size_;
        size_t thres_;
        size_t lca_size_, level_;
        template <typename I>
        inline void init_sizes(I _size) {
            input_size_[0] = _size; 
            if (!stride_set_)
                stride_[0] = 1;
            total_size_ = _size; 
            for (int i = 1; i < 3; ++i) {
                if (!stride_set_) 
                    stride_[i] = input_size_[i-1] * stride_[i-1];
                total_size_ *= input_size_[i];
            }
            assert(total_size_ == input_size_[2] * input_size_[1] * input_size_[0]);

            if (!dim_set_) {
#if 0
                /* assuming stride_[] are aligned to dimensionality */
                if (input_size_[0] >= input_size_[1] 
                        && input_size_[0] >= input_size_[2]) {
                    cut_dim_ = 0; red_dim_[1] = 2; red_dim_[0] = 1; 
                } else if (input_size_[1] >= input_size_[0] 
                        && input_size_[1] >= input_size_[2]) {
                    cut_dim_ = 1; red_dim_[1] = 2; red_dim_[0] = 0;
                } else {
                    cut_dim_ = 2; red_dim_[1] = 1; red_dim_[0] = 0;
                }
#else
                if (input_size_[0] >= input_size_[1] 
                        && input_size_[0] >= input_size_[2]) {
                    cut_dim_ = 0; 
                } else if (input_size_[1] >= input_size_[0] 
                        && input_size_[1] >= input_size_[2]) {
                    cut_dim_ = 1;
                } else {
                    cut_dim_ = 2;
                }
                /* set the red_dim_[] according to stride_[] */
                unsigned int code = (1u << (cut_dim_+3)) | (((stride_[2] >= stride_[1]) & 0x1) << 2) | (((stride_[1] >= stride_[0]) & 0x1) << 1) | ((stride_[2] >= stride_[0]) & 0x1);
                switch (code) {
                    case 34 : 
                    case 35 :
                    case 38 : 
                    case 39 : red_dim_[1] = 1; red_dim_[0] = 0; break;
                    case 32 :
                    case 33 :
                    case 36 :
                    case 37 : red_dim_[1] = 0; red_dim_[0] = 1; break;
                    case 17 :
                    case 19 :
                    case 21 : 
                    case 23 : red_dim_[1] = 2; red_dim_[0] = 0; break;
                    case 16 :
                    case 18 :
                    case 20 :
                    case 22 : red_dim_[1] = 0; red_dim_[0] = 2; break;
                    case 12 :
                    case 13 :
                    case 14 :
                    case 15 : red_dim_[1] = 2; red_dim_[0] = 1; break;
                    case 8  :
                    case 9  :
                    case 10 :
                    case 11 : red_dim_[1] = 1; red_dim_[0] = 2; break;
                    default : printf("code = %x\n", code);
                              exit(1);
                } /* end switch */
#endif
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
            input_2D_algo_ = new T_Input_2D_Algo*[level_];
            for (size_t i = 0; i < level_; ++i) {
                pp_array_[i] = new T[total_size_];
                /* let's make the cut_stride the largest stride,
                 * since we are going to perform 2D preprocessing
                 * on the remaining two dimensions
                 */
                const size_t pp_cut_stride = input_size_[red_dim_[1]] * input_size_[red_dim_[0]];
                const size_t pp_red_stride_1 = input_size_[red_dim_[0]];
                const size_t pp_red_stride_0 = 1;
                /* init_pp_i() do the data reduction of each level 
                 * by reformulate the data from original array into pp_array_
                 */
                init_pp_i(i);
                input_2D_algo_[i] = new T_Input_2D_Algo[input_size_[cut_dim_]];
                for (size_t j = 0; j < input_size_[cut_dim_]; ++j) {
                    /* since the input_2D_algo_ to this initial algo is a 2D
                     * algo, we don't set_dim of it
                     */
                    input_2D_algo_[i][j].set_stride(pp_red_stride_1, pp_red_stride_0);
                    input_2D_algo_[i][j].preprocess(op_, pp_array_[i] + j * pp_cut_stride, input_size_[red_dim_[1]], input_size_[red_dim_[0]]);
                }
            }

            return;
        }
        
        /* init_pp_i() do the data reduction of each level : 
         * _i is the level
         */
        inline void init_pp_i(size_t _i) {
            size_t begin_idx = pow2(_i);
            size_t end_idx = pow2(_i+1);
            int begin_range, end_range, mid_point;
            const size_t cut_stride = stride_[cut_dim_];
            const size_t red_stride_1 = stride_[red_dim_[1]];
            const size_t red_stride_0 = stride_[red_dim_[0]];
            const size_t pp_cut_stride = input_size_[red_dim_[1]] * input_size_[red_dim_[0]];
            const size_t pp_red_stride_1 = input_size_[red_dim_[0]];
            const size_t pp_red_stride_0 = 1;

            for (size_t i = begin_idx; i < end_idx; ++i) {
                int l_begin_range, l_end_range, l_mid_point;
                size_t shift_in_bits = level_ + 1 - msb_pos(i);
                l_begin_range = (i << shift_in_bits) - lca_size_;
                l_end_range = ((i << shift_in_bits) | ((1ul << shift_in_bits) - 1)) - lca_size_;
                l_mid_point = (l_end_range + l_begin_range + 1) >> 1;
                if (l_begin_range < input_size_[cut_dim_]) {
                    begin_range = l_begin_range;
                    end_range = l_end_range >= (input_size_[cut_dim_]-1) ? (input_size_[cut_dim_]-1) : l_end_range;
                    mid_point = l_mid_point;
                    size_t l_pp_base_addr = (mid_point-1) * pp_cut_stride;
                    size_t l_base_addr = (mid_point-1) * cut_stride;
                    const size_t l_input_size_1 = input_size_[red_dim_[1]];
                    const size_t l_input_size_0 = input_size_[red_dim_[0]];
                    size_t l_pp_base_1 = 0, l_base_1 = 0;
                    if (mid_point - 1 >= begin_range
                            && mid_point <= end_range) {
                        /* the most common case: */
                        /* fill in the mid_point - 1 & mid_point */
                        for (size_t j = 0; j < l_input_size_1; ++j,
                                l_pp_base_1 += pp_red_stride_1,
                                l_base_1 += red_stride_1) {
                            size_t l_pp_addr = l_pp_base_addr + l_pp_base_1;
                            size_t l_addr = l_base_addr + l_base_1;
                            for (size_t l = 0; l < l_input_size_0; 
                                    ++l, l_pp_addr += pp_red_stride_0,
                                    l_addr += red_stride_0) {
                                pp_array_[_i][l_pp_addr] = 
                                    input_array_[l_addr];
                                pp_array_[_i][l_pp_addr + pp_cut_stride] = 
                                    input_array_[l_addr + cut_stride];
                            }
                        }
                    } else if (mid_point - 1 >= begin_range
                            && mid_point - 1 <= end_range) {
                        /* just fill in the mid_point-1 */
                        for (size_t j = 0; j < l_input_size_1; ++j,
                                l_pp_base_1 += pp_red_stride_1,
                                l_base_1 += red_stride_1) {
                            size_t l_pp_addr = l_pp_base_addr + l_pp_base_1;
                            size_t l_addr = l_base_addr + l_base_1;
                            for (size_t l = 0; l < l_input_size_0;
                                    ++l, l_pp_addr += pp_red_stride_0,
                                    l_addr += red_stride_0) {
                                pp_array_[_i][l_pp_addr] = 
                                    input_array_[l_addr];
                            }
                        }
                    }

                    /* possibly merge the below 2 loops in the future */
                    // size_t l_pp_addr_1, l_addr_1;
                    int k = mid_point-2, k1 = mid_point+1, i = 0;
                    k = min (k, end_range-1);
                    // k1 = min (k1, end_range);
                    int len_0 = k-begin_range;
                    int len_1 = end_range-k1;
                    int len = min(len_0, len_1) + 1;
                    l_pp_base_addr = k * pp_cut_stride;
                    l_base_addr = k * cut_stride;
                    size_t l_pp_base_addr_1 = k1 * pp_cut_stride;
                    size_t l_base_addr_1 = k1 * cut_stride;
                    for ( ; i < len; --k, ++k1, ++i,
                            l_pp_base_addr -= pp_cut_stride,
                            l_base_addr -= cut_stride,
                            l_pp_base_addr_1 += pp_cut_stride,
                            l_base_addr_1 += cut_stride) {
                        l_pp_base_1 = 0; l_base_1 = 0;
                        for (size_t j = 0; j < l_input_size_1; ++j,
                                l_pp_base_1 += pp_red_stride_1,
                                l_base_1 += red_stride_1) {
                            size_t l_pp_addr = l_pp_base_addr + l_pp_base_1;
                            size_t l_addr = l_base_addr + l_base_1;
                            size_t l_pp_addr_1 = l_pp_base_addr_1 + l_pp_base_1;
                            size_t l_addr_1 = l_base_addr_1 + l_base_1;
                            for (size_t l = 0; l < l_input_size_0; 
                                    ++l,
                                    l_pp_addr += pp_red_stride_0,
                                    l_addr += red_stride_0,
                                    l_pp_addr_1 += pp_red_stride_0,
                                    l_addr_1 += red_stride_0) {
                            /* do the data reduction */
                            pp_array_[_i][l_pp_addr] = 
                                op_(pp_array_[_i][l_pp_addr + pp_cut_stride], 
                                        input_array_[l_addr]);
                            pp_array_[_i][l_pp_addr_1] = 
                                op_(pp_array_[_i][l_pp_addr_1 - pp_cut_stride], 
                                        input_array_[l_addr_1]);
                            }
                        }
                    }
                    /* fill out the rest of prefix */
                    for ( ; k1 <= end_range; ++k1,
                            l_pp_base_addr_1 += pp_cut_stride,
                            l_base_addr_1 += cut_stride) {
                        l_pp_base_1 = 0; l_base_1 = 0;
                        for (size_t j = 0; j < l_input_size_1; ++j,
                                l_pp_base_1 += pp_red_stride_1,
                                l_base_1 += red_stride_1) {
                            size_t l_pp_addr_1 = l_pp_base_addr_1 + l_pp_base_1;
                            size_t l_addr_1 = l_base_addr_1 + l_base_1;
                            for (size_t l = 0; l < l_input_size_0;
                                    ++l,
                                    l_pp_addr_1 += pp_red_stride_0,
                                    l_addr_1 += red_stride_0) {
                            pp_array_[_i][l_pp_addr_1] = 
                                op_(pp_array_[_i][l_pp_addr_1 - pp_cut_stride], 
                                        input_array_[l_addr_1]);
                            }
                        }
                    }

                    /* fill out the rest of suffix */
                    for ( ; k >= begin_range; --k,
                            l_pp_base_addr -= pp_cut_stride,
                            l_base_addr -= cut_stride) {
                        l_pp_base_1 = 0; l_base_1 = 0;
                        for (size_t j = 0; j < l_input_size_1; ++j,
                                l_pp_base_1 += pp_red_stride_1,
                                l_base_1 += red_stride_1) {
                            size_t l_pp_addr = l_pp_base_addr + l_pp_base_1;
                            size_t l_addr = l_base_addr + l_base_1;
                            for (size_t l = 0; l < l_input_size_0;
                                    ++l,
                                    l_pp_addr += pp_red_stride_0,
                                    l_addr += red_stride_0) {
                            pp_array_[_i][l_pp_addr] = 
                                op_(pp_array_[_i][l_pp_addr + pp_cut_stride], 
                                        input_array_[l_addr]);
                            }

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
        inline T query(size_t (&lo)[3] /* inclusive */, size_t (&hi)[3] /* exclusive */) {
            /* query the range [lo, hi) => [l_lo, l_hi] */
            T res;
            if (((hi[2] - lo[2]) * (hi[1] - lo[1]) * (hi[0] - lo[0])) <= thres_) {
                /* for extremely small sized array, we just scan through 
                 */
                const size_t stride_2 = stride_[2];
                const size_t stride_1 = stride_[1];
                const size_t stride_0 = stride_[0];
                size_t l_addr = lo[2] * stride_2 + lo[1] * stride_1 + lo[0] * stride_0;
                res = input_array_[l_addr];
                l_addr += stride_0;
                for (size_t j = lo[0] + 1; j < hi[0]; ++j,
                        l_addr += stride_0) {
                    res = op_(res, input_array_[l_addr]);
                }
                size_t l_base_2 = lo[2] * stride_2;
                size_t l_base_1 = (lo[1] + 1) * stride_1;
                size_t l_base_0 = lo[0] * stride_0;
                for (size_t i = lo[1] + 1; i < hi[1]; ++i,
                        l_base_1 += stride_1) {
                    l_addr = l_base_2 + l_base_1 + l_base_0;
                    for (size_t j = lo[0]; j < hi[0]; ++j,
                            l_addr += stride_0) {
                        res = op_(res, input_array_[l_addr]);
                    }
                }
                l_base_2 = (lo[2] + 1) * stride_2;
                l_base_0 = lo[0] * stride_0;
                for (size_t i = lo[2] + 1; i < hi[2]; ++i,
                        l_base_2 += stride_2) {
                    l_base_1 = lo[1] * stride_1;
                    for (size_t j = lo[1]; j < hi[1]; ++j,
                            l_base_1 += stride_1) {
                        l_addr = l_base_2 + l_base_1 + l_base_0;
                        for (size_t l = lo[0]; l < hi[0]; ++l,
                                l_addr += stride_0) {
                            res = op_(res, input_array_[l_addr]);
                        }
                    }
                }
                return res;
            } /* end if extremely small sized array */

            size_t l_lo = lo[cut_dim_], l_hi = hi[cut_dim_] - 1;
            size_t l_lca = lca((l_lo + lca_size_), (l_hi + lca_size_)), l_level = msb_pos(l_lca)-1;
            l_level = (l_level == level_ ? l_level - 1 : l_level);
            size_t lo_red[2], hi_red[2];
            lo_red[1] = lo[red_dim_[1]]; hi_red[1] = hi[red_dim_[1]];
            lo_red[0] = lo[red_dim_[0]]; hi_red[0] = hi[red_dim_[0]];
            if (l_lo == l_hi) { 
                /* Just curious if we directly plug in the 3D integer
                 * array into an argument which is supposed to be a 2D
                 * integer array, what will happen??
                 */
                res = input_2D_algo_[l_level][l_lo].query(lo_red, hi_red);
            } else {
                T res_lo = input_2D_algo_[l_level][l_lo].query(lo_red, hi_red);
                T res_hi = input_2D_algo_[l_level][l_hi].query(lo_red, hi_red);
                res = op_(res_lo, res_hi); 
            }

            return res;
        }
        inline void set_dim(unsigned int _cut_dim) {
            cut_dim_ = _cut_dim; 
            unsigned int code = (1u << (cut_dim_+3)) | ((stride_[2] >= stride_[1]) << 2) | ((stride_[1] >= stride_[0]) << 1) | (stride_[2] >= stride_[0]);
            switch (code) {
                case 34 : 
                case 35 :
                case 38 : 
                case 39 : red_dim_[1] = 1; red_dim_[0] = 0; break;
                case 32 :
                case 33 :
                case 36 :
                case 37 : red_dim_[1] = 0; red_dim_[0] = 1; break;
                case 17 :
                case 19 :
                case 21 : 
                case 23 : red_dim_[1] = 2; red_dim_[0] = 0; break;
                case 16 :
                case 18 :
                case 20 :
                case 22 : red_dim_[1] = 0; red_dim_[0] = 2; break;
                case 12 :
                case 13 :
                case 14 :
                case 15 : red_dim_[1] = 2; red_dim_[0] = 1; break;
                case 8  :
                case 9  :
                case 10 :
                case 11 : red_dim_[1] = 1; red_dim_[0] = 2; break;
                default : printf("code = %x\n", code);
                          exit(1);
            } /* end switch */
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
            thres_ = thres_ * thres_ * thres_;
            pp_array_ = NULL;
            return;
        }
        template <typename ... IS>
        Init_Algo(T_Op _op, T * _input_array, IS ... _sizes) : input_array_(_input_array), stride_set_(false), dim_set_(false) {
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            thres_ = thres_ * thres_ * thres_;
            pp_array_ = NULL;
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
                if (input_2D_algo_ != NULL) 
                    delete [] input_2D_algo_[i];
            }
            delete [] pp_array_;
            delete [] input_2D_algo_;

            return;
        }
        void print_info(void) {
            cout << "\nInit_Algo (input size = " 
                 << input_size_[2] " x " << input_size_[1] 
                 << " x " << input_size_[0] 
                 << ", cut dim : " << cut_dim_ 
                 << ", red_dim_[1] : " << red_dim_[1] 
                 << ", red_dim_[0] : " << red_dim_[0] << ")\n";
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        void print_range(size_t (&lo)[3] /* inclusive */, size_t (&hi)[3] /* exclusive */) {
            cout << "\nInit_Algo (input size = " 
                 << input_size_[2] << " x " << input_size_[1] 
                 << " x " << input_size_[0] 
                 << ", cut dim : " << cut_dim_ 
                 << ", red_dim_[1] : " << red_dim_[1] 
                 << ", red_dim_[0] : " << red_dim_[0] << ")\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "Input Array: " << endl;
            for (size_t i = lo[2]; i < hi[2]; ++i) {
                cout << "i = " << i << " : " << endl;
                for (size_t j = lo[1]; j < hi[1]; ++j) {
                    size_t l_addr = i * stride_[2] + j * stride_[1] 
                        + lo[0] * stride_[0];
                    for (size_t l = lo[0]; l < hi[0]-1; ++l,
                            l_addr += stride_[0]) {
                        cout << input_array_[l_addr] << ", ";
                    }
                    cout << input_array_[l_addr] << endl;
                }
                cout << endl;
            }
            cout << "-----------------------------------------------------------------------\n";
            if (pp_array_ != NULL) {
                cout << "pp_array: " << endl;
                size_t l_lca = lca(lo[cut_dim_] + lca_size_, hi[cut_dim_] + lca_size_), l_level = msb_pos(l_lca) - 1;
                const size_t pp_stride_2 = input_size_[red_dim_[1]] * input_size_[red_dim_[0]];
                const size_t pp_stride_1 = input_size_[red_dim_[0]];
                const size_t pp_stride_0 = 1;
                l_level = (l_level == level_ ? l_level - 1 : l_level);
                cout << "level " << l_level << ": " << endl;
                for (size_t i = lo[cut_dim_]; i < hi[cut_dim_]; ++i) {
                    cout << "i = " << i << " : " << endl;
                    for (size_t j = lo[red_dim_[1]]; j < hi[red_dim_[1]]; ++j) {
                        size_t l_addr = i * pp_stride_2 + j * pp_stride_1 
                            + lo[red_dim_[0]] * pp_stride_0;
                        for (size_t l = lo[red_dim_[0]]; l < hi[red_dim_[0]]-1; 
                                ++l, l_addr += pp_stride_0) {
                            cout << pp_array_[l_level][l_addr] << ", ";
                        }
                        cout << pp_array_[l_level][l_addr] << endl;
                    }
                    cout << endl;
                }
                cout << "-----------------------------------------------------------------------\n";
            } /* end if (pp_array_ != NULL) */

            return;
        }
        friend ostream & operator<<(ostream & fs, Init_Algo<T, 3> const & _init_algo) {
            fs << "\nInit_Algo (input size = " 
                 << _init_algo.input_size_[2] << " x " 
                 <<_init_algo.input_size_[1] << " x " 
                 << _init_algo.input_size_[0] 
                 << ", cut dim : " << _init_algo.cut_dim_ 
                 << ", red_dim_[1] : " << _init_algo.red_dim_[1] 
                 << ", red_dim_[0] : " << _init_algo.red_dim_[0] << ")\n";
            fs << "-----------------------------------------------------------------------\n";
            fs << "Input Array: " << endl;
            for (size_t i = 0; i < _init_algo.input_size_[2]; ++i) {
                cout << "i = " << i << " : " << endl;
                for (size_t j = 0; j < _init_algo.input_size_[1]; ++j) {
                    size_t l_addr = i * _init_algo.stride_[2] + j * _init_algo.stride_[1];
                    for (size_t l = 0; l < _init_algo.input_size_[0]-1; ++l,
                            l_addr += _init_algo.stride_[0]) {
                        fs << _init_algo.input_array_[l_addr] << ", ";
                    }
                    fs << _init_algo.input_array_[l_addr] << endl;
                }
                cout << endl;
            }
            fs << "-----------------------------------------------------------------------\n";
            if (_init_algo.pp_array_ != NULL) {
                cout << "pp_array: " << endl;
                for (size_t l = 0; l < _init_algo.level_; ++l) {
                    size_t l_level = l;
                    const size_t pp_cut_stride = _init_algo.input_size_[_init_algo.red_dim_[1]] * _init_algo.input_size_[_init_algo.red_dim_[0]];
                    const size_t pp_red_stride_1 = _init_algo.input_size_[_init_algo.red_dim_[0]];
                    const size_t pp_red_stride_0 = 1;
                    fs << "level " << l_level << ": " << endl;
                    for (size_t i = 0; i < _init_algo.input_size_[_init_algo.cut_dim_]; ++i) {
                        cout << "i = " << i << " : " << endl;
                        for (size_t j = 0; j < _init_algo.input_size_[_init_algo.red_dim_[1]]; ++j) {
                            size_t l_addr = i * _init_algo.stride_[_init_algo.cut_dim_] + j * _init_algo.stride_[_init_algo.red_dim_[1]];
                            for (size_t l = 0; l < _init_algo.input_size_[_init_algo.red_dim_[0]]-1; ++l, l_addr += _init_algo.stride_[_init_algo.red_dim_[0]]) {
                                fs << _init_algo.pp_array_[l_level][l_addr] << ", ";
                            }
                            fs << _init_algo.pp_array_[l_level][l_addr] << endl;
                        }
                        cout << endl;
                    }
                    fs << "-----------------------------------------------------------------------\n";
                }
            } /* end if (_init_algo.pp_array_ != NULL) */

            return fs;
        }
};
#endif // LIB_INIT_3D_HPP
