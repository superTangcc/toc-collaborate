/*
 * ============================================================================
 *
 *       Filename:  lib_meta_1D.hpp
 *
 *    Description:  meta-algo for 1D partial sum query on general
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

#ifndef LIB_META_1D_HPP
#define LIB_META_1D_HPP

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cmath>
#include <iostream>
#include <functional>

#include "lib_common.hpp"
#include "lib_init_1D.hpp"

using namespace std;

template <typename T, int N_RANK, int REC>
struct Meta {
    private:
        typedef function<T (T, T)> T_Op;
        T_Op op_;
        Init_Algo<T, N_RANK> * input_algo_;
        T * input_array_;
        T * promoted_array_, * prefix_array_, * suffix_array_;
        bool stride_set_;
        size_t stride_[N_RANK];
        size_t input_size_[N_RANK], total_size_, level_;
    public:
        template <typename ... IS>
        inline void set_stride(IS ... _strides) { }
        inline T query(size_t (&lo)[N_RANK] /* inclusive */, size_t (&hi)[N_RANK] /* exclusive */) { }
        template <typename I>
        inline void set_stride(I _stride) { }
        Meta(void) { return; }
        template <typename F, typename ... IS>
        Meta(F _op, T * _input_array, IS ... _sizes) : input_array_(_input_array) { }
        ~Meta() { }
        void print_info(void) { }
        void print_range(size_t * _begin, size_t * _end) { }
        friend ostream & operator<<(ostream & fs, Meta<T, N_RANK, REC> const & meta) { return fs; }
};

template <typename T>
struct Meta<T, 1, 0> {
    private:
        typedef function<T (T, T)> T_Op;
        typedef Init_Algo<T, 1> T_Input_1D_Algo;
        T_Op op_; // op_ is the partial sum operator
        T_Input_1D_Algo * input_1D_algo_;
        T * input_array_;
        T * promoted_array_, * prefix_array_, * suffix_array_;
        bool stride_set_;
        size_t stride_[1];
        size_t input_size_[1], total_size_, level_;
    public:
        inline T query(size_t (&lo)[1] /* inclusive */, size_t (&hi)[1] /* exclusive */) {
            T res = input_1D_algo_->query(lo, hi);
            return res;
        }
        template <typename I>
        inline void set_stride(I _stride) {
            /* this function could be used to overwrite
             * the stride_[] set by init_sizes()
             */
            stride_[0] = _stride;
            input_1D_algo_->set_stride(_stride);
            stride_set_ = true;
            return;
        }
        template <typename I>
        inline void preprocess(T_Op _op, T * _input_array, I _size) {
            input_array_ = _input_array;
            op_ = _op;
            input_1D_algo_->preprocess(_op, _input_array, _size);
            return;
        }
        Meta(void) : stride_set_(false) { 
            input_1D_algo_ = new T_Input_1D_Algo();
            return; 
        }
        template <typename I>
        Meta(T_Op _op, T * _input_array, I _size): input_array_(_input_array), op_(_op), stride_set_(false) {
            input_1D_algo_ = new T_Input_1D_Algo(_op, _input_array, _size);
            return;
        }
        ~Meta() {
            delete input_1D_algo_;
        }
        void print_info(void) {
            input_1D_algo_->print_info();
            return;
        }
        void print_range(size_t (&a)[1], size_t (&b)[1]) {
            input_1D_algo_->print_range(a, b);
            return;
        }
        friend ostream & operator<<(ostream & fs, Meta<T, 1, 0> const & meta) {
            fs << (*(meta.input_1D_algo_));
            return fs;
        }
};

template <typename T, int REC>
struct Meta<T, 1, REC> {
    private:
        typedef function<T (T, T)> T_Op;
        typedef Meta<T, 1, REC-1> T_Input_Algo;
        typedef Meta<T, 1, REC> T_Meta;
        T_Op op_; // op_ is the partial sum operator
        /* May we get the input_algo_ like op_ from user's input?
         */
        T_Input_Algo * input_1D_algo_;
        /* array meta_[] is to recursively call meta algorithm
         * on segments of input array
         */
        T_Meta * meta_;
        T_Curry_Func curry_func_;
        T * input_array_;
        T * promoted_array_, * prefix_array_, * suffix_array_;
        bool stride_set_;
        size_t thres_;
        size_t seg_size_, n_segs_;
        size_t stride_[1];
        size_t input_size_[1], total_size_;
        template <typename I>
        inline void init_sizes(I _size) {
            input_size_[0] = _size; 
            if (!stride_set_)
                stride_[0] = 1;
            total_size_ = _size;

            return;
        }
        inline void init_pp(void) {
            seg_size_ = curry_func_(input_size_[0]); 
            n_segs_ = input_size_[0]/seg_size_ + (input_size_[0] % seg_size_ > 0);

            if (seg_size_ > thres_) {
                meta_ = new T_Meta[n_segs_];
            }
            /* promoted_array_[], prefix_array_[], suffix_array_[] are
             * all implicitly of stride 1, regardless of the stride of 
             * input_array_[]
             */
            promoted_array_ = new T[n_segs_];
            prefix_array_ = new T[total_size_];
            suffix_array_ = new T[total_size_];
            for (size_t i = 0; i < n_segs_; ++i) {
                /* init_pp_i() will reduce the data from input_array_
                 * to promoted_array_, prepare the prefix/suffix array,
                 * call meta_[i] on segmented array of size log(N).
                 */
                promoted_array_[i] = init_pp_i(i);
            }
            input_1D_algo_ = new T_Input_Algo(op_, promoted_array_, n_segs_);
            /* if thres_ <= 4, we can just naive scan through with no more than 3 ops */
        }
        /* init_pp_i() will reduce the data from input_array_
         * to promoted_array_, prepare the prefix/suffix array,
         * call meta_[j] on segmented array of size log(N).
         */
        inline T init_pp_i(size_t _seg_n) {
            /* [begin_idx, end_idx] will be both inclusive */
            const size_t stride_0 = stride_[0];
            size_t begin_idx = _seg_n * seg_size_;
            size_t end_idx = (_seg_n + 1) * seg_size_;
            end_idx = (end_idx > input_size_[0] ? input_size_[0] : end_idx);
            size_t len = end_idx - begin_idx - 1;
            /* res will store the data reduction result in segment
             * from begin_idx to end_idx
             */
            size_t l_suffix_addr = (end_idx-1) * stride_0;
            size_t l_prefix_addr = (begin_idx) * stride_0;
            size_t l_pp_suffix_addr = (end_idx-1);
            size_t l_pp_prefix_addr = (begin_idx);
            prefix_array_[l_pp_prefix_addr] = input_array_[l_prefix_addr];
            suffix_array_[l_pp_suffix_addr] = input_array_[l_suffix_addr];
            l_suffix_addr -= stride_0; l_prefix_addr += stride_0;
            l_pp_suffix_addr--; l_pp_prefix_addr++;
            for (size_t i = 0; i < len; ++i, 
                    l_suffix_addr -= stride_0, l_prefix_addr += stride_0,
                    --l_pp_suffix_addr, ++l_pp_prefix_addr) {
                prefix_array_[l_pp_prefix_addr] = op_(prefix_array_[l_pp_prefix_addr-1], input_array_[l_prefix_addr]);
                suffix_array_[l_pp_suffix_addr] = op_(suffix_array_[l_pp_suffix_addr+1], input_array_[l_suffix_addr]);
            }
            if (seg_size_ > thres_) {
                meta_[_seg_n].set_stride(stride_0);
                meta_[_seg_n].preprocess(op_, (input_array_ + begin_idx * stride_0), (len + 1));
            }
            assert(prefix_array_[l_pp_prefix_addr-1] 
                    == suffix_array_[l_pp_suffix_addr+1]);
            return (prefix_array_[l_pp_prefix_addr-1]);
        }
    public:
        inline T query(size_t (&lo)[1] /* inclusive */, size_t (&hi)[1] /* exclusive */) {
            const size_t stride_0 = stride_[0];
            T res;
            if (total_size_ <= thres_ || (hi[0] - lo[0]) <= thres_) {
                /* for extremely small-sized array, we just scan through 
                 */
                res = input_array_[lo[0] * stride_0];
                size_t l_addr = (lo[0]+1) * stride_0;
                for (int i = lo[0]+1; i < hi[0]; 
                        ++i, l_addr += stride_0) {
                    res = op_(res, input_array_[l_addr]);
                }
                return res;
            }
            size_t begin_range[1], end_range[1];
            size_t begin_idx[1], end_idx[1];

            begin_range[0] = lo[0] / seg_size_;
            end_range[0] = (hi[0] - 1) / seg_size_;
            begin_idx[0] = lo[0] % seg_size_;
            end_idx[0] = (hi[0] - 1) % seg_size_ + 1;
            if (begin_range[0] + 1 == end_range[0]) {
                res = op_(suffix_array_[lo[0]], prefix_array_[hi[0]-1]);
                return res;
            }
            if (begin_range[0] < end_range[0]) {
                /* inter-block query */
                ++begin_range[0]; 
                res = input_1D_algo_->query(begin_range, end_range);
                res = op_(suffix_array_[lo[0]], res);
                res = op_(res, prefix_array_[hi[0]-1]);
                return res;
            } else {
                /* intra-block query */
                assert(begin_range[0] == end_range[0]);
                res = meta_[begin_range[0]].query(begin_idx, end_idx);
                return res;
            }
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
        void preprocess(T_Op _op, T * _input_array, I _size) {
            input_array_ = _input_array;
            op_ = _op;
            init_sizes(_size);
            /* prevent extremely small-sized array cut */
            if (total_size_ <= thres_) 
                return;
            init_pp();
            return;
        }
        Meta(void) : stride_set_(false) {
            // T_Curry_Func log_helper = [](T_Data x) { return (63 - __builtin_clzl(x)); };
            /* the size of thres_ plays a significant role in preprocess/query
             * overhead
             */
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            curry_func_ = log2_helper;
            for (int i = 0; i < REC; ++i) {
                curry_func_ = bind(star, curry_func_, _1);
            }
            input_1D_algo_ = NULL; meta_ = NULL; 
            promoted_array_ = NULL; prefix_array_ = NULL; suffix_array_ = NULL;
            return;
        }
        template <typename I>
        Meta(T_Op _op, T * _input_array, I _size) : input_array_(_input_array), op_(_op), stride_set_(false) {
            // T_Curry_Func log_helper = [](T_Data x) { return (63 - __builtin_clzl(x)); };
            /* the size of thres_ plays a significant role in preprocess/query
             * overhead
             */
            thres_ = bind(star, log2_helper, _1)(1ul << 63);
            curry_func_ = log2_helper;
            for (int i = 0; i < REC-1; ++i) {
                curry_func_ = bind(star, curry_func_, _1);
            }
            input_1D_algo_ = NULL; meta_ = NULL; 
            promoted_array_ = NULL; prefix_array_ = NULL; suffix_array_ = NULL;
            init_sizes(_size);
            if (total_size_ <= thres_) 
                return;
            init_pp();
            return;
        }
        ~Meta() {
            delete input_1D_algo_;
            delete [] meta_;
            delete [] promoted_array_;
            delete [] prefix_array_;
            delete [] suffix_array_;
        }
        void print_info(void) {
            cout << "\nMeta_Algo<1, T, 1> (input size = " 
                 << input_size_[0] << ", seg_size_ = " << seg_size_ 
                 << ", n_segs_ = " << n_segs_ << ")\n";
            cout << "-----------------------------------------------------------------------\n";

            return;
        }
        void print_range(size_t (&lo)[1], size_t (&hi)[1]) {
            const size_t l_stride = stride_[0];
            cout << "\nMeta_Algo<1, T, 1> (input size = " 
                 << input_size_[0] << ", seg_size_ = " << seg_size_ 
                 << ", n_segs_ = " << n_segs_ << ")\n";
            cout << "-----------------------------------------------------------------------\n";
            if (total_size_ <= thres_) {
                cout << "[";
                size_t l_addr = lo[0] * l_stride;
                for (int i = lo[0]; i < hi[0]-1; 
                        ++i, l_addr += l_stride) {
                    cout << input_array_[l_addr] << ", ";
                }
                cout << input_array_[l_addr] << "]" << endl;
                return;
            }

            size_t begin_range[1], end_range[1];
            size_t begin_idx[1], end_idx[1];

            begin_range[0] = lo[0] / seg_size_;
            end_range[0] = (hi[0] - 1) / seg_size_;
            begin_idx[0] = lo[0] % seg_size_;
            end_idx[0] = hi[0] % seg_size_;
            if (begin_range[0] < end_range[0]) {
                /* inter-block query */
                ++end_range[0];
                cout << "suffix_[" << lo[0] << "] = " << suffix_array_[lo[0]]
                     << ", [";
                for (int i = begin_range[0]; i < end_range[0]-1; ++i) {
                    cout << promoted_array_[i] << ", ";
                }
                cout << promoted_array_[end_range[0]-1] << "] ";
                cout << "(" << input_1D_algo_->query(begin_range, end_range) 
                     << ") ";

                cout << "prefix_[" << hi[0]-1 << "] = " << prefix_array_[hi[0]-1] << endl;
                return;
            } else {
                /* intra-block query */
                assert(begin_range[0] == end_range[0]);
                meta_[begin_range[0]].print_range(begin_idx, end_idx);
                return;
            }
        }
        friend ostream & operator<<(ostream & fs, Meta<T, 1, REC> const & _meta) {
            const size_t l_stride = _meta.stride_[0];
            fs << "\nMeta_Algo<1, T, " << REC << "> (input size = " 
                 << _meta.input_size_[0] 
                 << ", seg_size_ = " << _meta.seg_size_ 
                 << ", n_segs_ = " << _meta.n_segs_ << ")\n";
            fs << "-----------------------------------------------------------------------\n";

            if (_meta.total_size_ <= _meta.thres_) {
                fs << "[";
                size_t l_addr = 0 * l_stride;
                for (int i = 0; i < _meta.input_size_[0]-1; 
                        ++i, l_addr += l_stride) {
                    fs << _meta.input_array_[l_addr] << ", ";
                }
                fs << _meta.input_array_[l_addr] << "]" << endl;
                return fs;
            }

            fs << "Promoted Array: " << endl;
            fs << "[" ;
            for (int i = 0; i < _meta.n_segs_-1; ++i) {
                fs << _meta.promoted_array_[i] << ", ";
            }
            fs << _meta.promoted_array_[_meta.n_segs_-1] << "]" << endl;

            fs << "Prefix (Suffix) Array: " << endl;
            for (size_t i = 0; i < _meta.n_segs_; ++i) {
                size_t begin_idx = i * _meta.seg_size_, end_idx = (i+1) * _meta.seg_size_;
                end_idx = end_idx > _meta.input_size_[0]-1 ? _meta.input_size_[0]-1 : end_idx;
                fs << "[" ;
                for (size_t j = begin_idx; j < end_idx-1; ++j) {
                    fs << _meta.prefix_array_[j] << "(" 
                       << _meta.suffix_array_[j] << "), ";
                }
                fs << _meta.prefix_array_[end_idx-1] << "("
                   << _meta.suffix_array_[end_idx-1] << ") " << "]" << endl;
                if (_meta.meta_ != NULL) {
                    fs << _meta.meta_[i];
                }
                fs << "-----------------------------------------------------------------------\n";
            }
            
            return fs;
        }
};
#endif // LIB_META_1D_HPP
