/*
 * ============================================================================
 *
 *       Filename:  lib_meta_3D.hpp
 *
 *    Description:  meta-algo for 3D partial sum query on general
 *                  semi-group, which only assumes associativity and commutativity
 *
 *        Version:  1.0
 *        Created:  06/15/2012 11:37:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#ifndef LIB_META_3D_HPP
#define LIB_META_3D_HPP

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cmath>
#include <iostream>
#include <functional>

#include "lib_common.hpp"
#include "lib_init_2D.hpp"
#include "lib_init_3D.hpp"
#include "lib_meta_2D.hpp"

using namespace std;

template <typename T>
struct Meta<T, 3, 0> {
    /* the N log^3 N algo */
    private:
        typedef function<T (T, T)> T_Op;
        typedef Init_Algo<T, 3> T_Input_3D_Algo;
        T_Op op_; // op_ is the partial sum operator
        T_Input_3D_Algo * input_3D_algo_;
        T * input_array_;
        T * promoted_array_, * prefix_array_, * suffix_array_;
        bool stride_set_, dim_set_;
        unsigned short cut_dim_, red_dim_[2];
        size_t stride_[3];
        size_t input_size_[3], total_size_, level_;
    public:
        inline T query(size_t (&lo)[3] /* inclusive */, size_t (&hi)[3] /* exclusive */) {
            T res = input_3D_algo_->query(lo, hi);
            return res;
        }
        inline void set_dim(unsigned int _cut_dim) {
            input_3D_algo_->set_dim(_cut_dim);
            dim_set_ = true;
            return;
        }
        template <typename ... IS>
        inline void set_stride(IS ... _strides) {
            input_3D_algo_->set_stride(_strides ...);
            stride_set_ = true;
            return;
        }
        template <typename ... IS>
        inline void preprocess(T_Op _op, T * _input_array, IS ... _sizes) {
            input_3D_algo_->preprocess(_op, _input_array, _sizes ...);
            return;
        }
        Meta(void) : stride_set_(false), dim_set_(false) { 
            input_3D_algo_ = new T_Input_3D_Algo();
            return; 
        }
        template <typename ... IS>
        Meta(T_Op _op, T * _input_array, IS ... _sizes): input_array_(_input_array), op_(_op), stride_set_(false), dim_set_(false) {
            input_3D_algo_ = new T_Input_3D_Algo(_op, _input_array, _sizes ...);
            return;
        }
        ~Meta() {
            delete input_3D_algo_;
        }
        void print_info(void) {
            input_3D_algo_->print_info();
            return;
        }
        void print_range(size_t (&a)[3], size_t (&b)[3]) {
            input_3D_algo_->print_range(a, b);
            return;
        }
        friend ostream & operator<<(ostream & fs, Meta<T, 3, 0> const & meta) {
            fs << (*(meta.input_3D_algo_));
            return fs;
        }
};

template <typename T, int REC>
struct Meta<T, 3, REC> {
    private:
        typedef function<T (T, T)> T_Op;
        typedef Meta<T, 3, REC-1> T_Input_3D_Algo;
        typedef Meta<T, 2, REC-1> T_Input_2D_Algo;
        typedef Meta<T, 3, REC> T_Meta;
        T_Op op_; // op_ is the partial sum operator
        /* May we get the input_2D_algo_ like op_ from user's input?
         */
        T_Input_3D_Algo * input_3D_algo_;
        T_Input_2D_Algo ** input_2D_algo_;
        /* array meta_[] is to recursively call meta algorithm
         * on segments of input array
         */
        T_Meta * meta_;
        T_Curry_Func curry_func_;
        T * input_array_;
        T * promoted_array_, * prefix_array_, * suffix_array_;
        size_t thres_;
        size_t seg_size_, n_segs_;
        bool stride_set_, dim_set_;
        unsigned short cut_dim_[2], red_dim_;
        size_t stride_[3], promoted_stride_[3];
        size_t input_size_[3], total_size_;
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
                    red_dim_ = 0;
                } else if (input_size_[1] >= input_size_[0]
                        && input_size_[1] >= input_size_[2]) {
                    red_dim_ = 1;
                } else {
                    red_dim_ = 2;
                }
                /* set the red_dim_[] according to stride_[] */
                unsigned int code = (1u << (red_dim_+3)) | (((stride_[2] >= stride_[1]) & 0x1) << 2) | (((stride_[1] >= stride_[0]) & 0x1) << 1) | ((stride_[2] >= stride_[0]) & 0x1);
                switch (code) {
                    case 34 :
                    case 35 :
                    case 38 :
                    case 39 : cut_dim_[1] = 1; cut_dim_[0] = 0; break;
                    case 32 :
                    case 33 :
                    case 36 :
                    case 37 : cut_dim_[1] = 0; cut_dim_[0] = 1; break;
                    case 17 :
                    case 19 :
                    case 21 :
                    case 23 : cut_dim_[1] = 2; cut_dim_[0] = 0; break;
                    case 16 :
                    case 18 :
                    case 20 :
                    case 22 : cut_dim_[1] = 0; cut_dim_[0] = 2; break;
                    case 12 :
                    case 13 :
                    case 14 :
                    case 15 : cut_dim_[1] = 2; cut_dim_[0] = 1; break;
                    case 8  :
                    case 9  :
                    case 10 :
                    case 11 : cut_dim_[1] = 1; cut_dim_[0] = 2; break;
                    default : printf("code = %x\n", code);
                              exit(1);
                } /* end switch */
#endif
            }

            return;
        }
        template <typename I, typename ... IS>
        inline void init_sizes(I _size, IS ... _sizes) {
            unsigned int l_dim = sizeof...(IS);
            input_size_[l_dim] = _size;
            init_sizes(_sizes ...);
            return;
        }

        inline void init_pp(void) {
            seg_size_ = curry_func_(input_size_[red_dim_]); 
            seg_size_ += (seg_size_ == 0);
            n_segs_ = input_size_[red_dim_]/seg_size_ + (input_size_[red_dim_] % seg_size_ > 0);

            size_t l_addr;
            /* handle the reduced array */
            /* bookmark */
            promoted_array_ = new T[n_segs_ * input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]]];
            promoted_stride_[2] = input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]];
            promoted_stride_[1] = input_size_[cut_dim_[0]];
            promoted_stride_[0] = 1;

            prefix_array_ = new T[total_size_];
            suffix_array_ = new T[total_size_];
            size_t l_base_2 = 0, l_base_1 = 0;
            for (size_t i = 0; i < input_size_[cut_dim_[1]]; ++i,
                    l_base_2 += promoted_stride_[1]) {
                l_base_1 = 0;
                for (size_t j = 0; j < input_size_[cut_dim_[0]]; ++j,
                        l_base_1 += promoted_stride_[0]) {
                    l_addr = l_base_2 + l_base_1;
                    for (size_t l = 0; l < n_segs_; 
                            ++l, l_addr += promoted_stride_[2]) {
                        /* init_pp_i() will reduce the data from input_array_[]
                         * to promoted_array_[], prepare the prefix/suffix array,
                         */
                        promoted_array_[l_addr] = init_pp_i(i, j, l);
                    }
                }
            }
            /* apply the input_3D_algo_ on promoted_array_ */
            input_3D_algo_ = new T_Input_3D_Algo(op_, promoted_array_, n_segs_, input_size_[cut_dim_[1]], input_size_[cut_dim_[0]]);

            meta_ = new T_Meta[n_segs_];
            /* call itself over the segmented blocks */
            size_t begin_idx = 0;
            size_t end_idx = seg_size_;
            l_addr = 0;
            const size_t block_size = seg_size_ * stride_[red_dim_];

            if (red_dim_ == 2) {
                /* apply itself on blocks of size n_segs_ * input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]] */
                for (size_t i = 0; i < n_segs_; ++i,
                        begin_idx += seg_size_,
                        end_idx += seg_size_,
                        l_addr += block_size) {
                    end_idx = (end_idx > input_size_[red_dim_] ? input_size_[red_dim_] : end_idx);
                    meta_[i].set_stride(stride_[2], stride_[1], stride_[0]);
                    meta_[i].preprocess(op_, input_array_ + l_addr, end_idx - begin_idx, input_size_[1], input_size_[0]);
                }
            } else if (red_dim_ == 1) {
                /* apply itself on blocks of size n_segs_ * input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]] */
                for (size_t i = 0; i < n_segs_; ++i,
                        begin_idx += seg_size_,
                        end_idx += seg_size_,
                        l_addr += block_size) {
                    end_idx = (end_idx > input_size_[red_dim_] ? input_size_[red_dim_] : end_idx);
                    meta_[i].set_stride(stride_[2], stride_[1], stride_[0]);
                    meta_[i].preprocess(op_, input_array_ + l_addr, input_size_[2], end_idx - begin_idx, input_size_[0]);
                }
            } else {
                assert(red_dim_ == 0);

                /* apply itself on blocks of size n_segs_ * input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]] */
                for (size_t i = 0; i < n_segs_; ++i,
                        begin_idx += seg_size_,
                        end_idx += seg_size_,
                        l_addr += block_size) {
                    end_idx = (end_idx > input_size_[red_dim_] ? input_size_[red_dim_] : end_idx);
                    meta_[i].set_stride(stride_[2], stride_[1], stride_[0]);
                    meta_[i].preprocess(op_, input_array_ + l_addr, input_size_[2], input_size_[1], end_idx - begin_idx);
                }
            }

            /* Apply 2D algo to every line of prefix/suffix array, 
             * along cut_dim_
             */
            /* one for prefix_array_[], one for suffix_array_[] */
            input_2D_algo_ = new T_Input_2D_Algo*[2];
            input_2D_algo_[0] = new T_Input_2D_Algo[input_size_[red_dim_]];
            input_2D_algo_[1] = new T_Input_2D_Algo[input_size_[red_dim_]];
            /* preprocess the prefix/suffix array */
            const size_t pp_red_stride = input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]];
            const size_t pp_cut_stride_1 = input_size_[cut_dim_[0]];
            const size_t pp_cut_stride_0 = 1;
            for (size_t i = 0; i < input_size_[red_dim_]; ++i) {
                /* prefix/suffix arrays are reduced from input_array_[],
                 * so they should have their own stride
                 */
                // input_2D_algo_[0][i].set_stride(pp_cut_stride_1, pp_cut_stride_0);
                input_2D_algo_[0][i].preprocess(op_, prefix_array_ + i * pp_red_stride, input_size_[cut_dim_[1]], input_size_[cut_dim_[0]]);
                // input_2D_algo_[1][i].set_stride(pp_cut_stride_1, pp_cut_stride_0);
                input_2D_algo_[1][i].preprocess(op_, suffix_array_ + i * pp_red_stride, input_size_[cut_dim_[1]], input_size_[cut_dim_[0]]);
            }

            return;
        }
        /* init_pp_i() will reduce the data from input_array_
         * to promoted_array_, prepare the prefix/suffix array,
         * _row is the index in cut_dim_
         */
        inline T init_pp_i(size_t _i, size_t _j, size_t _seg_n) {
            /* [begin_idx, end_idx] will be both inclusive */
            const size_t red_stride = stride_[red_dim_];
            const size_t cut_stride_1 = stride_[cut_dim_[1]];
            const size_t cut_stride_0 = stride_[cut_dim_[0]];
            const size_t pp_red_stride = input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]];
            const size_t pp_cut_stride_1 = input_size_[cut_dim_[0]];
            const size_t pp_cut_stride_0 = 1;
            size_t begin_idx = _seg_n * seg_size_;
            size_t end_idx = begin_idx + seg_size_;
            end_idx = (end_idx > input_size_[red_dim_] ? input_size_[red_dim_] : end_idx);
            size_t len = end_idx - begin_idx - 1;
            /* res will store the data reduction result in segment
             * from begin_idx to end_idx
             */
            size_t l_prefix_addr = _i * cut_stride_1 + _j * cut_stride_0 + begin_idx * red_stride;
            size_t l_suffix_addr = _i * cut_stride_1 + _j * cut_stride_0 + (end_idx - 1) * red_stride;
            size_t l_pp_prefix_addr = _i * pp_cut_stride_1 + _j * pp_cut_stride_0 + begin_idx * pp_red_stride;
            size_t l_pp_suffix_addr = _i * pp_cut_stride_1 + _j * pp_cut_stride_0 + (end_idx - 1) * pp_red_stride;
            T tmp = input_array_[l_prefix_addr];
            prefix_array_[l_pp_prefix_addr] = tmp;
            tmp = input_array_[l_suffix_addr];
            suffix_array_[l_pp_suffix_addr] = tmp;
            l_pp_prefix_addr += pp_red_stride; 
            l_pp_suffix_addr -= pp_red_stride;
            l_prefix_addr += red_stride;
            l_suffix_addr -= red_stride;
            for (size_t i = 0; i < len; ++i,
                    l_prefix_addr += red_stride,
                    l_suffix_addr -= red_stride,
                    l_pp_prefix_addr += pp_red_stride,
                    l_pp_suffix_addr -= pp_red_stride) {
                prefix_array_[l_pp_prefix_addr] = 
                    op_(prefix_array_[l_pp_prefix_addr - pp_red_stride], 
                        input_array_[l_prefix_addr]);
                suffix_array_[l_pp_suffix_addr] = 
                    op_(suffix_array_[l_pp_suffix_addr + pp_red_stride], 
                        input_array_[l_suffix_addr]);
            }
            assert(prefix_array_[l_pp_prefix_addr - pp_red_stride] 
                    == suffix_array_[l_pp_suffix_addr + pp_red_stride]);
            return (prefix_array_[l_pp_prefix_addr - pp_red_stride]);
        }
    public:
        inline T query(size_t (&lo)[3] /* inclusive */, size_t (&hi)[3] /* exclusive */) {
            T res;
            size_t l_addr;
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
            }
            size_t begin_range[3], end_range[3];
            size_t begin_idx[3], end_idx[3];

            begin_range[red_dim_] = lo[red_dim_] / seg_size_;
            end_range[red_dim_] = (hi[red_dim_] - 1) / seg_size_;
            begin_idx[red_dim_] = lo[red_dim_] % seg_size_;
            end_idx[red_dim_] = (hi[red_dim_] - 1) % seg_size_ + 1;

            size_t l_cut_lo[2], l_cut_hi[2];
            l_cut_lo[1] = lo[cut_dim_[1]]; l_cut_hi[1] = hi[cut_dim_[1]];
            l_cut_lo[0] = lo[cut_dim_[0]]; l_cut_hi[0] = hi[cut_dim_[0]];
            if (begin_range[red_dim_] + 1 == end_range[red_dim_]) {
#ifdef DEBUG
                printf("prefix + suffix\n");
#endif
                T res_suffix = input_2D_algo_[1][lo[red_dim_]].query(l_cut_lo, l_cut_hi);
                T res_prefix = input_2D_algo_[0][hi[red_dim_]-1].query(l_cut_lo, l_cut_hi);
                res = op_(res_suffix, res_prefix); 
            } else if (begin_range[red_dim_] < end_range[red_dim_]) {
                assert(end_range[red_dim_] - begin_range[red_dim_] > 1);
#ifdef DEBUG
                printf("inter-block query!\n");
#endif
                /* inter-block query */
                ++begin_range[red_dim_]; 

                /* we switch the dimensionality to align to the data 
                 * layout of promoted_array_[]
                 */
                begin_range[2] = begin_range[red_dim_];
                end_range[2] = end_range[red_dim_];
                begin_range[1] = lo[cut_dim_[1]];
                end_range[1] = hi[cut_dim_[1]];
                begin_range[0] = lo[cut_dim_[0]];
                end_range[0] = hi[cut_dim_[0]];

                T res_block = input_3D_algo_->query(begin_range, end_range);
                T res_suffix = input_2D_algo_[1][lo[red_dim_]].query(l_cut_lo, l_cut_hi);
                T res_prefix = input_2D_algo_[0][hi[red_dim_]-1].query(l_cut_lo, l_cut_hi);
#ifdef DEBUG
                printf("res_block = %lu, res_suffix = %lu, res_prefix = %lu\n",
                        res_block, res_suffix, res_prefix);
#endif
                res = op_(res_suffix, res_block);
                res = op_(res, res_prefix);
            } else {
                /* intra-block query */
                assert(begin_range[red_dim_] == end_range[red_dim_]);
#ifdef DEBUG
                printf("intra-block query!\n");
#endif
                begin_idx[cut_dim_[1]] = lo[cut_dim_[1]];
                end_idx[cut_dim_[1]] = hi[cut_dim_[1]];
                begin_idx[cut_dim_[0]] = lo[cut_dim_[0]];
                end_idx[cut_dim_[0]] = hi[cut_dim_[0]];
                res = meta_[begin_range[red_dim_]].query(begin_idx, end_idx);
            }
            return res;
        }
        inline void set_dim(unsigned short _red_dim) {
            red_dim_ = _red_dim;
            unsigned int code = (1u << (red_dim_+3)) | (((stride_[2] >= stride_[1]) & 0x1) << 2) | (((stride_[1] >= stride_[0]) & 0x1) << 1) | ((stride_[2] >= stride_[0]) & 0x1);
            switch (code) {
                case 34 :
                case 35 :
                case 38 :
                case 39 : cut_dim_[1] = 1; cut_dim_[0] = 0; break;
                case 32 :
                case 33 :
                case 36 :
                case 37 : cut_dim_[1] = 0; cut_dim_[0] = 1; break;
                case 17 :
                case 19 :
                case 21 :
                case 23 : cut_dim_[1] = 2; cut_dim_[0] = 0; break;
                case 16 :
                case 18 :
                case 20 :
                case 22 : cut_dim_[1] = 0; cut_dim_[0] = 2; break;
                case 12 :
                case 13 :
                case 14 :
                case 15 : cut_dim_[1] = 2; cut_dim_[0] = 1; break;
                case 8  :
                case 9  :
                case 10 :
                case 11 : cut_dim_[1] = 1; cut_dim_[0] = 2; break;
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
        void preprocess(T_Op _op, T * _input_array, IS ... _sizes) {
            input_array_ = _input_array;
            op_ = _op;
            init_sizes(_sizes ...);
            if (total_size_ <= thres_) 
                return;
            init_pp();
            return;
        }
        Meta(void) : stride_set_(false), dim_set_(false) {
            // T_Curry_Func log_helper = [](T_Data x) { return (63 - __builtin_clzl(x)); };
            /* the size of thres_ plays a significant role in preprocess/query
             * overhead
             */
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            thres_ = thres_ * thres_ * thres_;
            curry_func_ = log2_helper;
            for (int i = 0; i < REC-1; ++i) {
                curry_func_ = bind(star, curry_func_, _1);
            }
            input_3D_algo_ = NULL; input_2D_algo_ = NULL; meta_ = NULL; 
            promoted_array_ = NULL; prefix_array_ = NULL; suffix_array_ = NULL;
            return;
        }
        template <typename ... IS>
        Meta(T_Op _op, T * _input_array, IS ... _sizes) : input_array_(_input_array), op_(_op), stride_set_(false), dim_set_(false) {
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            thres_ = thres_ * thres_ * thres_;
            curry_func_ = log2_helper;
            for (int i = 0; i < REC-1; ++i) {
                curry_func_ = bind(star, curry_func_, _1);
            }
            input_3D_algo_ = NULL; input_2D_algo_ = NULL; meta_ = NULL; 
            promoted_array_ = NULL; prefix_array_ = NULL; suffix_array_ = NULL;
            init_sizes(_sizes ...);
            if (total_size_ <= thres_) 
                return;
            init_pp();
            return;
        }
        ~Meta() {
            delete input_3D_algo_;
            if (input_2D_algo_ != NULL) {
                for (int i = 0; i < 2; ++i) {
                    delete [] input_2D_algo_[i];
                }
            }
            delete [] input_2D_algo_;
            delete [] meta_;
            delete [] promoted_array_;
            delete [] prefix_array_;
            delete [] suffix_array_;
        }
        void print_info(void) {
            cout << "\nMeta_Algo<T, 2, " << REC << "> (input size = " 
                 << input_size_[2] << " x " << input_size_[1] 
                 << " x " << input_size_[0] 
                 << ", red_dim_ : " << red_dim_
                 << ", cut_dim_[1] : " << cut_dim_[1]
                 << ", cut_dim_[0] : " << cut_dim_[0]
                 << ", seg_size_ = " << seg_size_ 
                 << ", n_segs_ = " << n_segs_ << ")\n";
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        void print_range(size_t (&lo)[3], size_t (&hi)[3]) {
            cout << "\nMeta_Algo<T, 3, " << REC << "> (input size = " 
                 << input_size_[2] << " x " << input_size_[1] 
                 << " x " << input_size_[0] 
                 << ", red_dim_ : " << red_dim_
                 << ", cut_dim_[1] : " << cut_dim_[1]
                 << ", cut_dim_[0] : " << cut_dim_[0]
                 << ", seg_size_ = " << seg_size_ 
                 << ", n_segs_ = " << n_segs_ << ")\n";
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
            cout << "promoted array : " << endl;
            int begin_range[3], end_range[3];
            int begin_idx[3], end_idx[3];

            begin_range[red_dim_] = lo[red_dim_]/seg_size_ + 1; 
            end_range[red_dim_] = (hi[red_dim_] - 1)/seg_size_;
            begin_range[cut_dim_[1]] = lo[cut_dim_[1]];
            end_range[cut_dim_[1]] = hi[cut_dim_[1]];
            begin_range[cut_dim_[0]] = lo[cut_dim_[0]];
            end_range[cut_dim_[0]] = hi[cut_dim_[0]];
            for (int i = begin_range[cut_dim_[1]]; i < end_range[cut_dim_[1]]; ++i) {
                cout << "i = " << i << endl;
                for (int j = begin_range[cut_dim_[0]]; j < end_range[cut_dim_[0]]; ++j) {
                    size_t l_addr = i * promoted_stride_[cut_dim_[1]] 
                        + j * promoted_stride_[cut_dim_[0]]
                        + begin_range[red_dim_] * promoted_stride_[red_dim_]; 
                    if (begin_range[red_dim_] <= end_range[red_dim_]-1) {
                        for (int l = begin_range[red_dim_]; l < end_range[red_dim_]-1; ++l,
                                l_addr += promoted_stride_[red_dim_]) {
                            cout << promoted_array_[l_addr] << ", ";
                        }
                        cout << promoted_array_[l_addr] << endl;
                    }
                }
                cout << endl;
            }
            cout << "-----------------------------------------------------------------------\n";
            cout << "Suffix array : " << endl;
            begin_range[red_dim_] = lo[red_dim_];
            end_range[red_dim_] = hi[red_dim_]-1;
            int i = begin_range[red_dim_];
            size_t l_red_stride = input_size_[cut_dim_[1]] * input_size_[cut_dim_[0]];
            size_t l_cut_stride_1 = input_size_[cut_dim_[0]];
            size_t l_cut_stride_0 = 1;
            for (int j = begin_range[cut_dim_[1]]; j < end_range[cut_dim_[1]]; ++j) {
                size_t l_addr = i * l_red_stride + j * l_cut_stride_1 + begin_range[cut_dim_[0]] * l_cut_stride_0; 
                for (int l = begin_range[cut_dim_[0]]; l < end_range[cut_dim_[0]]-1; ++l, l_addr += l_cut_stride_0) {
                    cout << suffix_array_[l_addr] << ", ";
                }
                cout << suffix_array_[l_addr] << endl;
            }

            cout << "-----------------------------------------------------------------------\n";
            cout << "Prefix array : " << endl;
            i = end_range[red_dim_];
            for (int j = begin_range[cut_dim_[1]]; j < end_range[cut_dim_[1]]; ++j) {
                size_t l_addr = i * l_red_stride + j * l_cut_stride_1 + begin_range[cut_dim_[0]] * l_cut_stride_0; 
                for (int l = begin_range[cut_dim_[0]]; l < end_range[cut_dim_[0]]-1; ++l, l_addr += l_cut_stride_0) {
                    cout << prefix_array_[l_addr] << ", ";
                }
                cout << prefix_array_[l_addr] << endl;
            }
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        friend ostream & operator<<(ostream & fs, Meta<T, 3, REC> const & _meta) {
            fs << "\nMeta_Algo<T, 3, " << REC << "> (input size = " 
                 << _meta.input_size_[2] << " x " <<_meta.input_size_[1] 
                 << " x " << _meta.input_size_[0] 
                 << ", red_dim_ : " << _meta.red_dim_
                 << ", cut_dim_[1] : " << _meta.cut_dim_[1]
                 << ", cut_dim_[0] : " << _meta.cut_dim_[0]
                 << ", seg_size_ = " << _meta.seg_size_ 
                 << ", n_segs_ = " << _meta.n_segs_ << ")\n";
            fs << "-----------------------------------------------------------------------\n";
            const unsigned short l_red_dim = _meta.red_dim_;
            const unsigned short l_cut_dim_1 = _meta.cut_dim_[1];
            const unsigned short l_cut_dim_0 = _meta.cut_dim_[0];
            cout << "Input Array: " << endl;
            for (size_t i = 0; i < _meta.input_size_[l_red_dim]; ++i) {
                cout << "i = " << i << " : " << endl;
                for (size_t j = 0; j < _meta.input_size_[l_cut_dim_1]; ++j) {
                    size_t l_addr = i * _meta.stride_[l_red_dim] 
                        + j * _meta.stride_[l_cut_dim_1];
                    for (size_t l = 0; l < _meta.input_size_[l_cut_dim_0]-1; ++l,
                            l_addr += _meta.stride_[l_cut_dim_0]) {
                        cout << _meta.input_array_[l_addr] << ", ";
                    }
                    cout << _meta.input_array_[l_addr] << endl;
                }
                cout << endl;
            }
            cout << "-----------------------------------------------------------------------\n";
            const size_t l_stride_2 = _meta.promoted_stride_[l_red_dim];
            const size_t l_stride_1 = _meta.promoted_stride_[l_cut_dim_1];
            const size_t l_stride_0 = _meta.promoted_stride_[l_cut_dim_0];
            const size_t l_len_2 = _meta.n_segs_;
            const size_t l_len_1 = _meta.input_size_[l_cut_dim_1];
            const size_t l_len_0 = _meta.input_size_[l_cut_dim_0];
            fs << "Promoted Array : " << endl;
            for (size_t i = 0; i < l_len_2; ++i) {
                cout << "i = " << i << " : " << endl;
                for (size_t j = 0; j < l_len_1; ++j) {
                    size_t l_addr = i * l_stride_2 + j * l_stride_1;
                    for (size_t l = 0; l < l_len_0-1; ++l,
                            l_addr += l_stride_0) {
                        cout << _meta.promoted_array_[l_addr] << ", ";
                    }
                    cout << _meta.promoted_array_[l_addr] << endl;
                }
                cout << endl;
            }

            const size_t l_red_stride = _meta.input_size_[l_cut_dim_1] * _meta.input_size_[l_cut_dim_0];
            const size_t l_cut_stride_1 = _meta.input_size_[l_cut_dim_0];
            const size_t l_cut_stride_0 = 1;
            fs << "Prefix Array : " << endl;
            for (size_t i = 0; i < _meta.input_size_[l_red_dim]; ++i) {
                fs << "i = " << i << endl;
                for (size_t j = 0; j < _meta.input_size_[l_cut_dim_1]; ++j) {
                    size_t l_addr = i * l_red_stride 
                        + j * l_cut_stride_1;
                    for (size_t l = 0; l < _meta.input_size_[l_cut_dim_0]-1; 
                            ++l, l_addr += l_cut_stride_0) {
                        fs << _meta.prefix_array_[l_addr] << ", ";
                    }
                    fs << _meta.prefix_array_[l_addr] << endl;
                }
                fs << endl;
            }
            fs << "-----------------------------------------------------------------------\n";

            fs << "Suffix Array : " << endl;
            for (size_t i = 0; i < _meta.input_size_[l_red_dim]; ++i) {
                fs << "i = " << i << endl;
                for (size_t j = 0; j < _meta.input_size_[l_cut_dim_1]; ++j) {
                    size_t l_addr = i * l_red_stride 
                        + j * l_cut_stride_1;
                    for (size_t l = 0; l < _meta.input_size_[l_cut_dim_0]-1; 
                            ++l, l_addr += l_cut_stride_0) {
                        fs << _meta.suffix_array_[l_addr] << ", ";
                    }
                    fs << _meta.suffix_array_[l_addr] << endl;
                }
                fs << endl;
            }
            fs << "-----------------------------------------------------------------------\n";
            return fs;
        }
};

#endif // LIB_META_3D_HPP
