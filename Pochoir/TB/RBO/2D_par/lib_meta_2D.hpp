/*
 * ============================================================================
 *
 *       Filename:  lib_meta_2D.hpp
 *
 *    Description:  meta-algo for 2D partial sum query on general
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

#ifndef LIB_META_2D_HPP
#define LIB_META_2D_HPP

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cmath>
#include <iostream>
#include <functional>

#include "lib_common.hpp"
#include "lib_init_1D.hpp"
#include "lib_init_2D.hpp"
#include "lib_meta_1D.hpp"

using namespace std;

template <typename T>
struct Meta<T, 2, 0> {
    /* the N log^2 N algo */
    private:
        typedef function<T (T, T)> T_Op;
        typedef Init_Algo<T, 2> T_Input_2D_Algo;
        T_Op op_; // op_ is the partial sum operator
        T_Input_2D_Algo * input_2D_algo_;
        T * input_array_;
        T * promoted_array_, * prefix_array_, * suffix_array_;
        bool stride_set_, dim_set_;
        unsigned short cut_dim_, red_dim_;
        size_t stride_[2];
        size_t input_size_[2], total_size_, level_;
    public:
        inline T query(size_t (&lo)[2] /* inclusive */, size_t (&hi)[2] /* exclusive */) {
            T res = input_2D_algo_->query(lo, hi);
            return res;
        }
        inline void set_dim(unsigned int _cut_dim) {
            input_2D_algo_->set_dim(_cut_dim);
            dim_set_ = true;
            return;
        }
        template <typename ... IS>
        inline void set_stride(IS ... _strides) {
            input_2D_algo_->set_stride(_strides ...);
            stride_set_ = true;
            return;
        }
        template <typename ... IS>
        inline void preprocess(T_Op _op, T * _input_array, IS ... _sizes) {
            input_2D_algo_->preprocess(_op, _input_array, _sizes ...);
            return;
        }
        Meta(void) : stride_set_(false), dim_set_(false) { 
            input_2D_algo_ = new T_Input_2D_Algo();
            return; 
        }
        template <typename ... IS>
        Meta(T_Op _op, T * _input_array, IS ... _sizes): input_array_(_input_array), op_(_op), stride_set_(false), dim_set_(false) {
            input_2D_algo_ = new T_Input_2D_Algo(_op, _input_array, _sizes ...);
            return;
        }
        ~Meta() {
            delete input_2D_algo_;
        }
        void print_info(void) {
            input_2D_algo_->print_info();
            return;
        }
        void print_range(size_t (&a)[2], size_t (&b)[2]) {
            input_2D_algo_->print_range(a, b);
            return;
        }
        friend ostream & operator<<(ostream & fs, Meta<T, 2, 0> const & meta) {
            fs << (*(meta.input_2D_algo_));
            return fs;
        }
};

template <typename T, int REC>
struct Meta<T, 2, REC> {
    private:
        typedef function<T (T, T)> T_Op;
        typedef Meta<T, 2, REC-1> T_Input_2D_Algo;
        typedef Meta<T, 1, REC-1> T_Input_1D_Algo;
        typedef Meta<T, 2, REC> T_Meta;
        T_Op op_; // op_ is the partial sum operator
        /* May we get the input_2D_algo_ like op_ from user's input?
         */
        T_Input_2D_Algo * input_2D_algo_;
        T_Input_1D_Algo ** input_1D_algo_;
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
        unsigned short cut_dim_, red_dim_, step_;
        size_t stride_[2], promoted_stride_[2];
        size_t input_size_[2], total_size_;
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
                if (input_size_[0] >= input_size_[1]) {
                    red_dim_ = 0; cut_dim_ = 1; 
                } else {
                    assert(input_size_[1] > input_size_[0]);
                    red_dim_ = 1; cut_dim_ = 0; 
                }
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
#ifdef DEBUG
            printf("step_ = %u\n", step_);
#endif
            if (step_ & 0x2) {
                /* step 2 & 3 */
                seg_size_ = (size_t) sqrt(input_size_[red_dim_]);
            } else {
                /* step 0 & 1 */
                seg_size_ = curry_func_(input_size_[red_dim_]); 
                seg_size_ += (seg_size_ == 0);
            }
            n_segs_ = input_size_[red_dim_]/seg_size_ + (input_size_[red_dim_] % seg_size_ > 0);

            size_t l_addr;
            /* handle the reduced array */
            promoted_array_ = new T[n_segs_ * input_size_[cut_dim_]];
            promoted_stride_[1] = red_dim_ == 0 ? n_segs_ : input_size_[0];
            promoted_stride_[0] = 1;
            prefix_array_ = new T[total_size_];
            suffix_array_ = new T[total_size_];
            for (size_t i = 0; i < input_size_[cut_dim_]; ++i) {
                // l_addr = i * promoted_stride_[cut_dim_];
                for (size_t j = 0; j < n_segs_; ++j) {
                    /* init_pp_i() will reduce the data from input_array_[]
                     * to promoted_array_[], prepare the prefix/suffix array,
                     */
                    l_addr = i * promoted_stride_[cut_dim_] + j * promoted_stride_[red_dim_];
                    promoted_array_[l_addr] = init_pp_i(i, j);
                }
            }
            if (red_dim_ == 1) {
                input_2D_algo_ = new T_Input_2D_Algo(op_, promoted_array_, n_segs_, input_size_[0]);
            } else {
                assert(red_dim_ == 0);
                input_2D_algo_ = new T_Input_2D_Algo(op_, promoted_array_, input_size_[1], n_segs_);
            }

            meta_ = new T_Meta[n_segs_];
            /* preprocess the segmented blocks */
            const size_t block_size = seg_size_ * stride_[red_dim_];
            const unsigned short next_step = (step_ + 1) & 0x3;
// #pragma omp parallel for \
//             private(begin_idx, end_idx, l_addr)
            cilk_for (size_t i = 0; i < n_segs_; ++i) {
                size_t begin_idx = i * seg_size_, end_idx = begin_idx + seg_size_;
                size_t l_addr = i * block_size;
                end_idx = (end_idx > input_size_[red_dim_] ? input_size_[red_dim_] : end_idx);
                // meta_[i].set_stride(stride_[cut_dim_], stride_[red_dim_]);
                meta_[i].set_stride(stride_[1], stride_[0]);
                meta_[i].set_step(next_step);
                if (red_dim_ == 0) {
                    meta_[i].preprocess(op_, input_array_ + l_addr, input_size_[1], end_idx - begin_idx);
                } else {
                    assert(red_dim_ == 1);
                    meta_[i].preprocess(op_, input_array_ + l_addr, end_idx - begin_idx, input_size_[0]);
                }
            }
            /* Apply 1D algo to every line of prefix/suffix array, 
             * along cut_dim_
             */
            /* one for prefix_array_[], one for suffix_array_[] */
            input_1D_algo_ = new T_Input_1D_Algo*[2];
            input_1D_algo_[0] = new T_Input_1D_Algo[input_size_[red_dim_]];
            input_1D_algo_[1] = new T_Input_1D_Algo[input_size_[red_dim_]];
            /* preprocess the prefix/suffix array */
#if 0
            const size_t pp_cut_stride = input_size_[red_dim_];
            const size_t pp_red_stride = 1;
#else
            const size_t pp_cut_stride = 1;
            const size_t pp_red_stride = input_size_[cut_dim_];
#endif
// #pragma omp parallel for 
            for (size_t i = 0; i < input_size_[red_dim_]; ++i) {
                /* prefix/suffix arrays are reduced from input_array_[],
                 * so they should have their own stride
                 */
                // input_1D_algo_[0][i].set_stride(pp_cut_stride);
                input_1D_algo_[0][i].preprocess(op_, prefix_array_ + i * pp_red_stride, input_size_[cut_dim_]);
                // input_1D_algo_[1][i].set_stride(pp_cut_stride);
                input_1D_algo_[1][i].preprocess(op_, suffix_array_ + i * pp_red_stride, input_size_[cut_dim_]);
            }

            return;
        }
        /* init_pp_i() will reduce the data from input_array_
         * to promoted_array_, prepare the prefix/suffix array,
         * _row is the index in cut_dim_
         */
        inline T init_pp_i(size_t _row, size_t _seg_n) {
            /* [begin_idx, end_idx] will be both inclusive */
            const size_t cut_stride = stride_[cut_dim_];
            const size_t red_stride = stride_[red_dim_];
            const size_t pp_cut_stride = 1;
            const size_t pp_red_stride = input_size_[cut_dim_];
            size_t begin_idx = _seg_n * seg_size_;
            size_t end_idx = begin_idx + seg_size_;
            end_idx = (end_idx > input_size_[red_dim_] ? input_size_[red_dim_] : end_idx);
            size_t len = end_idx - begin_idx - 1;
            /* res will store the data reduction result in segment
             * from begin_idx to end_idx
             */
            size_t l_prefix_addr = _row * cut_stride + begin_idx * red_stride;
            size_t l_suffix_addr = _row * cut_stride + (end_idx - 1) * red_stride;
            size_t l_pp_prefix_addr = _row * pp_cut_stride + begin_idx * pp_red_stride;
            size_t l_pp_suffix_addr = _row * pp_cut_stride + (end_idx - 1) * pp_red_stride;
            prefix_array_[l_pp_prefix_addr] = input_array_[l_prefix_addr];
            suffix_array_[l_pp_suffix_addr] = input_array_[l_suffix_addr];
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
        inline T query(size_t (&lo)[2] /* inclusive */, size_t (&hi)[2] /* exclusive */) {
            T res;
            size_t l_addr;
            const size_t stride_1 = stride_[1];
            const size_t stride_0 = stride_[0];

            if (total_size_ <= thres_ || ((hi[1] - lo[1]) * (hi[0] - lo[0])) <= thres_) {
                /* for extremely small sized array, we just scan through 
                 */
                l_addr = lo[1] * stride_1 + lo[0] * stride_0;
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
            size_t begin_range[2], end_range[2];
            size_t begin_idx[2], end_idx[2];

            begin_range[red_dim_] = lo[red_dim_] / seg_size_;
            end_range[red_dim_] = (hi[red_dim_] - 1) / seg_size_;
#if 1
            begin_idx[red_dim_] = lo[red_dim_] % seg_size_;
            end_idx[red_dim_] = (hi[red_dim_] - 1) % seg_size_ + 1;
#else
            begin_idx[red_dim_] = lo[red_dim_] - begin_range[red_dim_] * seg_size_;
            end_idx[red_dim_] = hi[red_dim_] - end_range[red_dim_] * seg_size;
#endif

            size_t l_cut_lo[1], l_cut_hi[1];
            l_cut_lo[0] = lo[cut_dim_]; l_cut_hi[0] = hi[cut_dim_];
            if (begin_range[red_dim_] + 1 == end_range[red_dim_]) {
                T res_suffix = input_1D_algo_[1][lo[red_dim_]].query(l_cut_lo, l_cut_hi);
                T res_prefix = input_1D_algo_[0][hi[red_dim_]-1].query(l_cut_lo, l_cut_hi);
                res = op_(res_suffix, res_prefix); 
            } else if (begin_range[red_dim_] < end_range[red_dim_]) {
                assert(end_range[red_dim_] - begin_range[red_dim_] > 1);
                /* inter-block query */
                ++begin_range[red_dim_]; 
                begin_range[cut_dim_] = lo[cut_dim_];
                end_range[cut_dim_] = hi[cut_dim_];
                T res_block = input_2D_algo_->query(begin_range, end_range);
                T res_suffix = input_1D_algo_[1][lo[red_dim_]].query(l_cut_lo, l_cut_hi);
                T res_prefix = input_1D_algo_[0][hi[red_dim_]-1].query(l_cut_lo, l_cut_hi);
#ifdef DEBUG
                printf("res_block = %lu, res_suffix = %lu, res_prefix = %lu\n",
                        res_block, res_suffix, res_prefix);
#endif
#if 0
                unsigned short code = ((begin_idx[red_dim_] == 0) << 1) | (end_idx[red_dim_] == seg_size_);
                switch (code) {
                    case 0 : 
                        res = op_(res_suffix, res_block);
                        res = op_(res, res_prefix);
                        break;
                    case 1 :
                        res = op_(res_suffix, res_block);
                        break;
                    case 2 :
                        res = op_(res_block, res_prefix);
                        break;
                    case 3 :
                        res = res_block;
                        break;
                }
#else
                res = op_(res_suffix, res_block);
                res = op_(res, res_prefix);
#endif
            } else {
                /* intra-block query */
                assert(begin_range[red_dim_] == end_range[red_dim_]);
                begin_idx[cut_dim_] = lo[cut_dim_];
                end_idx[cut_dim_] = hi[cut_dim_];
                res = meta_[begin_range[red_dim_]].query(begin_idx, end_idx);
            }
            return res;
        }
        inline void set_dim(unsigned short _cut_dim) {
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
        inline void set_step(unsigned short _step) { 
            step_ = _step;
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
            thres_ = thres_ * thres_;
            curry_func_ = log2_helper;
            for (int i = 0; i < REC-1; ++i) {
                curry_func_ = bind(star, curry_func_, _1);
            }
            input_2D_algo_ = NULL; input_1D_algo_ = NULL; meta_ = NULL; 
            promoted_array_ = NULL; prefix_array_ = NULL; suffix_array_ = NULL;
            return;
        }
        template <typename ... IS>
        Meta(T_Op _op, T * _input_array, IS ... _sizes) : input_array_(_input_array), op_(_op), stride_set_(false), dim_set_(false) {
            step_ = 0;
            auto thres_func = bind(star, log2_helper, _1);
            thres_ = thres_func((1ul << 63));
            thres_ = thres_ * thres_;
            curry_func_ = log2_helper;
            for (int i = 0; i < REC-1; ++i) {
                curry_func_ = bind(star, curry_func_, _1);
            }
            input_2D_algo_ = NULL; input_1D_algo_ = NULL; meta_ = NULL; 
            promoted_array_ = NULL; prefix_array_ = NULL; suffix_array_ = NULL;
            init_sizes(_sizes ...);
            if (total_size_ <= thres_) 
                return;
            init_pp();
            return;
        }
        ~Meta() {
            delete input_2D_algo_;
            if (input_1D_algo_ != NULL) {
                for (int i = 0; i < 2; ++i) {
                    delete [] input_1D_algo_[i];
                }
            }
            delete [] input_1D_algo_;
            delete [] meta_;
            delete [] promoted_array_;
            delete [] prefix_array_;
            delete [] suffix_array_;
        }
        void print_info(void) {
            cout << "\nMeta_Algo<T, 2, " << REC << "> (input size = " 
                 << input_size_[1] << " x " << input_size_[0] 
                 << ", cut dim : " << cut_dim_
                 << ", seg_size_ = " << seg_size_ 
                 << ", n_segs_ = " << n_segs_ << ")\n";
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        void print_range(size_t (&lo)[2], size_t (&hi)[2]) {
            cout << "\nMeta_Algo<T, 2, " << REC << "> (input size = " 
                 << input_size_[1] << " x " << input_size_[0] 
                 << ", cut dim : " << cut_dim_
                 << ", seg_size_ = " << seg_size_ 
                 << ", n_segs_ = " << n_segs_ << ")\n";
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
            cout << "promoted array : " << endl;
            int begin_range[2], end_range[2];
            int begin_idx[2], end_idx[2];

            begin_range[red_dim_] = lo[red_dim_]/seg_size_ + 1; 
            end_range[red_dim_] = (hi[red_dim_] - 1)/seg_size_;
            begin_range[cut_dim_] = lo[cut_dim_];
            end_range[cut_dim_] = hi[cut_dim_];
            for (int i = begin_range[cut_dim_]; i < end_range[cut_dim_]; ++i) {
                size_t l_addr = i * promoted_stride_[cut_dim_] 
                    + begin_range[red_dim_] * promoted_stride_[red_dim_]; 
                if (begin_range[red_dim_] <= end_range[red_dim_]-1) {
                    for (int j = begin_range[red_dim_]; j < end_range[red_dim_]-1; ++j,
                            l_addr += promoted_stride_[red_dim_]) {
                        cout << promoted_array_[l_addr] << ", ";
                    }
                    cout << promoted_array_[l_addr] << endl;
                }
            }
            cout << "-----------------------------------------------------------------------\n";
            const size_t pp_cut_stride = 1;
            const size_t pp_red_stride = input_size_[cut_dim_];
            size_t l_addr = lo[cut_dim_] * pp_cut_stride 
                + lo[red_dim_] * pp_red_stride;
            cout << "suffix : ";
            for (size_t i = lo[cut_dim_]; i < hi[cut_dim_]-1; ++i,
                    l_addr += pp_cut_stride) {
                cout << suffix_array_[l_addr] << ", ";
            }
            cout << suffix_array_[l_addr] << endl;

            l_addr = lo[cut_dim_] * pp_cut_stride 
                + (hi[red_dim_]-1) * pp_red_stride;
            cout << "prefix : ";
            for (size_t i = lo[cut_dim_]; i < hi[cut_dim_]-1; ++i,
                    l_addr += pp_cut_stride) {
                cout << prefix_array_[l_addr] << ", ";
            }
            cout << prefix_array_[l_addr] << endl;

            /* print sub data structure */
            size_t l_cut_lo[1], l_cut_hi[1];
            l_cut_lo[0] = lo[cut_dim_]; l_cut_hi[0] = hi[cut_dim_];
            if (begin_range[red_dim_] + 1 == end_range[red_dim_]) {
                cout << "Suffix + Prefix:" << endl;
                cout << input_1D_algo_[1][lo[red_dim_]]; 
                cout << input_1D_algo_[0][hi[red_dim_]-1];
            } else if (begin_range[red_dim_] < end_range[red_dim_]) {
                cout << "inter-block query" << endl;
                /* inter-block query */
                ++begin_range[red_dim_]; 
                begin_range[cut_dim_] = lo[cut_dim_];
                end_range[cut_dim_] = hi[cut_dim_];
                cout << (*input_2D_algo_);
                cout << input_1D_algo_[1][lo[red_dim_]];
                cout << input_1D_algo_[0][hi[red_dim_]-1];
            } else {
                cout << "intra-block query" << endl;
                /* intra-block query */
                begin_idx[cut_dim_] = lo[cut_dim_];
                end_idx[cut_dim_] = hi[cut_dim_];
                cout << meta_[begin_range[red_dim_]];
            }
 
            return;
        }
        friend ostream & operator<<(ostream & fs, Meta<T, 2, REC> const & _meta) {
            fs << "\nMeta_Algo<T, 2, " << REC << "> (input size = " 
                 << _meta.input_size_[1] << " x " << _meta.input_size_[0] 
                 << ", cut dim : " << _meta.cut_dim_
                 << ", seg_size_ = " << _meta.seg_size_ 
                 << ", n_segs_ = " << _meta.n_segs_ << ")\n";
            fs << "-----------------------------------------------------------------------\n";
            fs << "Input Array: " << endl;
            const size_t stride_1 = _meta.stride_[1];
            const size_t stride_0 = _meta.stride_[0];
            const size_t input_size_1 = _meta.input_size_[1];
            const size_t input_size_0 = _meta.input_size_[0];
            for (size_t i = 0; i < input_size_1; ++i) {
                size_t l_addr = i * stride_1;
                for (size_t j = 0; j < input_size_0-1;
                        ++j, l_addr += stride_0) {
                    fs << _meta.input_array_[l_addr] << ", ";
                }
                fs << _meta.input_array_[l_addr] << endl;
            }
            fs << "-----------------------------------------------------------------------\n";

            const unsigned short l_red_dim = _meta.red_dim_;
            const unsigned short l_cut_dim = _meta.cut_dim_;
            fs << "Prefix Array : " << endl;
            for (size_t i = 0; i < _meta.input_size_[l_red_dim]; ++i) {
                size_t l_addr = i;
                for (size_t j = 0; j < _meta.input_size_[l_cut_dim] - 1;
                        ++j, l_addr += _meta.input_size_[l_cut_dim]) {
                    fs << _meta.prefix_array_[l_addr] << ", ";
                }
                fs << _meta.prefix_array_[l_addr] << endl;
            }
            fs << "-----------------------------------------------------------------------\n";

            fs << "Suffix Array : " << endl;
            for (size_t i = 0; i < _meta.input_size_[l_red_dim]; ++i) {
                size_t l_addr = i;
                for (size_t j = 0; j < _meta.input_size_[l_cut_dim] - 1;
                        ++j, l_addr += _meta.input_size_[l_cut_dim]) {
                    fs << _meta.suffix_array_[l_addr] << ", ";
                }
                fs << _meta.suffix_array_[l_addr] << endl;
            }
            fs << "-----------------------------------------------------------------------\n";
            return fs;
        }
};

#endif // LIB_META_2D_HPP
