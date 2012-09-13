/*
 * ============================================================================
 *
 *       Filename:  lib_rbt_bvector.hpp
 *
 *    Description:  library of RBT_bvector
 *
 *        Version:  1.0
 *        Created:  03/09/2012 12:14:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#ifndef LIB_RBT_BVECTOR_HPP
#define LIB_RBT_BVECTOR_HPP

#include <iostream>
#include "lib_common.hpp"

#define REC 1

using namespace std;
struct RBT_bvector {
    /* use bit-vector left-or/right-or for bit-wise or query */
    public:
    inline unsigned long query(unsigned long lo, unsigned long hi) {
        /* lca: lowest common ancestor; lcp: longest common prefix */
        unsigned long lca = lcp(lo + leaf_size_, hi + leaf_size_);
        unsigned long height = log2_ceil(lca);
        height = height > height_ ? height - 1 : height;
        const unsigned long bmask = 1ul << (nbits_ - 1);
        unsigned long l_idx = leaf_size_ * (height) + lo,
                      r_idx = leaf_size_ * (height) + hi;
        return ((ror_[l_idx] | lor_[r_idx]) & bmask); 
    }
    inline void mkSubTree(
            unsigned long _height, /* _height determines the iteration # */
            /* [_l_node, _r_node) decides the iteration range,
             * it's also the rbt_idx in the tree
             */
            unsigned long _l_node, /* inclusive */
            unsigned long _r_node /* exclusive */
            ) 
    {
        /* construct the left-or/right-or tree bottom up */
        const unsigned long bmask = 1ul << (nbits_ - 1);
        const unsigned long level_mask = pow2(log2_floor(_l_node));
        unsigned long l_order = level_mask ^ _l_node, 
                      r_order = level_mask ^ _r_node;
        unsigned long subtree_height = log2_ceil(_l_node);
        unsigned long nentry = pow2(height_ - subtree_height + 1);
        unsigned long nentry_child = nentry >> 1;
        unsigned long l_idx = leaf_size_ * (subtree_height - 1) + l_order * nentry;
        unsigned long r_idx = l_idx + nentry - 1;
        unsigned long ll_idx = l_idx + leaf_size_;
        unsigned long rr_idx = r_idx + leaf_size_;
        unsigned long rbt_idx = _l_node - 1; 
        unsigned long rbt_l_idx = (_l_node << 1) - 1, rbt_r_idx = (_l_node << 1);
        for (unsigned int l = 1; l <= _height; ++l, 
                nentry <<= 1, nentry_child <<= 1, 
                _l_node >>= 1, _r_node >>= 1,
                l_idx -= leaf_size_, 
                // r_idx -= (leaf_size_ - nentry_child), 
                r_idx = l_idx + nentry - 1,
                ll_idx -= leaf_size_, 
                // rr_idx -= (leaf_size_ - nentry_child),
                rr_idx = r_idx + leaf_size_,
                rbt_idx >>= 1, 
                rbt_l_idx >>= 1, 
                rbt_r_idx >>= 1) {
            unsigned long  _l_idx    = l_idx, 
                           _r_idx    = r_idx,
                          _ll_idx    = ll_idx,
                          _rr_idx    = rr_idx, 
                          _rbt_idx   = rbt_idx, 
                          _rbt_l_idx = rbt_l_idx, 
                          _rbt_r_idx = rbt_r_idx;
            // cilk_for (unsigned long node = _l_node; node < _r_node; ++node) {
            /* why it's un-parallelize-able by cilk_for ??? */
            for (unsigned long node = _l_node; node < _r_node; ++node) {
                unsigned long __l_idx  = _l_idx, 
                              __r_idx  = _r_idx, 
                              __ll_idx = _ll_idx, 
                              __rr_idx = _rr_idx;
                for (unsigned long i = 0;
                     i < nentry_child; 
                     ++i, 
                     ++__l_idx, 
                     ++__ll_idx, 
                     --__r_idx, 
                     --__rr_idx) {
                    lor_[__l_idx] = lor_[__ll_idx];
                    ror_[__r_idx] = ror_[__rr_idx];
                }
                unsigned int set = (lset_[_rbt_l_idx] << 1) | (rset_[_rbt_r_idx]);
                switch (set) {
                    case 0:
                        do {
                        /* lset_[_rbt_l_idx] == 0 */
                        /* rset_[_rbt_r_idx] == 0 */
                        bool l_set = lor_[__ll_idx] & bmask;
                        bool r_set = ror_[__rr_idx] & bmask;
                        for (unsigned long i = 0; 
                             i < nentry_child; 
                             ++i, 
                             ++__l_idx, 
                             ++__ll_idx, 
                             --__r_idx, 
                             --__rr_idx) {
                            lor_[__l_idx] = lor_[__ll_idx];
                            l_set |= lor_[_ll_idx];
                            ror_[__r_idx] = ror_[__rr_idx];
                            r_set |= ror_[__rr_idx];
                        }
                        lset_[_rbt_idx] = l_set & bmask;
                        rset_[_rbt_idx] = r_set & bmask;
                        } while(0);
                        break;
                    case 1:
                        do {
                        /* lset_[_rbt_l_idx] == 0 */
                        /* rset_[_rbt_r_idx] == 1 */
                        bool l_set = lor_[__ll_idx] & bmask;
                        for (unsigned long i = 0; 
                             i < nentry_child; 
                             ++i, 
                             ++__l_idx, 
                             ++__ll_idx, 
                             --__r_idx, 
                             --__rr_idx) {
                            lor_[__l_idx] = lor_[__ll_idx];
                            l_set |= lor_[__ll_idx];
                            ror_[__r_idx] = ror_[__rr_idx] | bmask;
                        }
                        lset_[_rbt_idx] = l_set & bmask;
                        rset_[_rbt_idx] = true;
                        } while (0);
                        break;
                    case 2:
                        do {
                        /* lset_[_rbt_l_idx] == 1 */
                        /* rset_[_rbt_r_idx] == 0 */
                        bool r_set = ror_[__rr_idx] & bmask;
                        for (unsigned long i = 0; 
                             i < nentry_child; 
                             ++i, 
                             ++__l_idx, 
                             ++__ll_idx, 
                             --__r_idx, 
                             --__rr_idx) {
                            lor_[__l_idx] = lor_[__ll_idx] | bmask;
                            ror_[__r_idx] = ror_[__rr_idx];
                            r_set |= ror_[__rr_idx];
                        }
                        lset_[_rbt_idx] = true;
                        rset_[_rbt_idx] = r_set & bmask;
                        } while(0);
                        break;
                    case 3:
                        do {
                        /* lset_[rbt_l_idx] == 1 */
                        /* rset_[rbt_r_idx] == 1 */
                        for (unsigned long i = 0; 
                             i < nentry_child; 
                             ++i, 
                             ++__l_idx, 
                             ++__ll_idx, 
                             --__r_idx, 
                             --__rr_idx) {
                            lor_[__l_idx] = lor_[__ll_idx] | bmask;
                            ror_[__r_idx] = ror_[__rr_idx] | bmask;
                        }
                        lset_[_rbt_idx] = true;
                        rset_[_rbt_idx] = true;
                        } while(0);
                        break;
                    default:
                        break;
                } /* end switch */
                _l_idx += nentry; 
                _r_idx += nentry; 
                _ll_idx += nentry; 
                _rr_idx += nentry;
                ++_rbt_idx;
                _rbt_l_idx += 2;
                _rbt_r_idx += 2;       
            }
        }
        return;
    }
    inline void mkTree_recursive(
            unsigned long _height,
            unsigned long _l_node,
            unsigned long _r_node) 
    { 
        /* [_l_node, _r_node) are the rbt_idx  */
        unsigned long nnodes = _r_node - _l_node;
        if (_height <= thres_) {
            /* do the base case construction of tree bottom up */
            /* get the height of sub-tree */
            // unsigned long l_node = pow2(height_ - height), r_node = l_node << 1;
            mkSubTree(_height, _l_node, _r_node);
            return;
        }
        /* do the recursion */
        cilk_spawn mkTree_recursive(_height >> 1, _l_node, _l_node + (nnodes >> 1));
        mkTree_recursive(_height >> 1, _l_node + (nnodes >> 1), _r_node);
        cilk_sync;
        /* merge the results bottom up !!! -- bookmark */
        unsigned long height = _height - (_height >> 1);
        unsigned long l_node = _l_node >> (_height >> 1), r_node = _r_node >> (_height >> 1);
        mkSubTree(height, l_node, r_node);
        return; 
    }
    inline void mkTree_loop(
            unsigned long _height,
            unsigned long _l_node,
            unsigned long _r_node) 
    {
        mkSubTree(_height, _l_node, _r_node);
        return;
    }
    RBT_bvector(unsigned long * _input_array, unsigned long _size, unsigned int _nbits) : input_size_(_size), nbits_(_nbits) {
        height_ = log2_ceil(_size);
        leaf_size_ = pow2(height_);
        node_size_ = (leaf_size_ << 1) - 1;
        total_storage_ = leaf_size_ * (height_ + 1);
        lor_ = new unsigned long[total_storage_];
        ror_ = new unsigned long[total_storage_];
        lset_ = new bool[node_size_];
        rset_ = new bool[node_size_];
        unsigned long l_lb = leaf_size_ * height_, l_rb = leaf_size_ * (height_ + 1);
        unsigned long l_rbt_lb = leaf_size_ - 1, l_rbt_rb = node_size_;
        unsigned long l_bmask = 1ul << (_nbits - 1);
        /* initialize the leaves with input array */
        for (unsigned long i = 0; i < _size; ++i) {
            lor_[l_lb + i] = _input_array[i];
            lset_[l_rbt_lb + i] = (_input_array[i] & l_bmask);
            ror_[l_lb + i] = _input_array[i];
            rset_[l_rbt_lb + i] = (_input_array[i] & l_bmask);
        }
        for (unsigned long i = _size; i < leaf_size_; ++i) {
            lor_[l_lb + i] = ror_[l_lb + i] = 0;
            lset_[l_rbt_lb + i] = rset_[l_rbt_lb + i] = false;
        } 
        unsigned long l_node = pow2(height_ - 1), r_node = l_node << 1;
#if REC 
#ifdef DEBUG
        printf("RBT_bvector::mkTree_recursive\n");
#endif
        mkTree_recursive(height_, l_node, r_node);
#else
#ifdef DEBUG
        printf("RBT_bvector::mkTree_loop\n");
#endif
        mkTree_loop(height_, l_node, r_node);
#endif
    }
    ~RBT_bvector() {
        delete [] lor_;
        delete [] ror_;
        delete [] lset_;
        delete [] rset_;
    }
    friend ostream & operator<<(std::ostream & fs, RBT_bvector const & rbt) {
        unsigned long nentry = rbt.leaf_size_;
        const unsigned long bmask = 1ul << (rbt.nbits_ - 1);
        fs << "\nRBT_bvector (input size = " << rbt.input_size_ << ", leaf size = " << rbt.leaf_size_
            << ", height = " << rbt.height_ << ", nbits = " << rbt.nbits_ << ")\n";
        fs << "     total nodes = " << rbt.node_size_ 
            << ", total storage = " << rbt.total_storage_ << "\n";
        fs << "-----------------------------------------------------------------------\n";
        fs << "left-or : \n";
        for (unsigned int l = 0; l <= rbt.height_; ++l) {
            unsigned long l_node = pow2(l), r_node = l_node << 1;
            for (unsigned long node = l_node; node < r_node; ++node) {
                fs << "[";
                const unsigned long l_idx = rbt.leaf_size_ * l + nentry * (node - l_node);
                const unsigned long r_idx = l_idx + nentry;
                const unsigned long rbt_idx = node; 
                for (unsigned long i = l_idx; i < r_idx; ++i) {
                    char c = (rbt.lor_[i] & bmask) ? '1' : '0';
                    fs << c;
                }
#if 0
                fs << " (";
                char c = (rbt.lset_[rbt_idx]) ? '1' : '0';
                fs << c;
                fs << ") ";
#endif
                fs << "]\t";
            }
            fs << "\n";
            nentry >>= 1;
        }
        nentry = rbt.leaf_size_;
        fs << "-----------------------------------------------------------------------\n";
        fs << "right-or : \n";
        for (unsigned int l = 0; l <= rbt.height_; ++l) {
            unsigned long l_node = pow2(l), r_node = l_node << 1;
            for (unsigned long node = l_node; node < r_node; ++node) {
                fs << "[";
                const unsigned long l_idx = rbt.leaf_size_ * l + nentry * (node - l_node);
                const unsigned long r_idx = l_idx + nentry;
                const unsigned long rbt_idx = node; 
                for (unsigned long i = l_idx; i < r_idx; ++i) {
                    char c = (rbt.ror_[i] & bmask) ? '1' : '0';
                    fs << c;
                }
#if 0
                fs << " (";
                c = (rbt.rset_[rbt_idx]) ? '1' : '0';
                fs << c;
                fs << ") ";
#endif
                fs << "]\t";
            }
            fs << "\n";
            nentry >>= 1;
        }
        fs << "-----------------------------------------------------------------------\n";
        return fs;
    }
    private:
    unsigned long *lor_, *ror_;
    unsigned int nbits_;
    bool *lset_, *rset_;
    // node_size_ = 2^m, where m = log2_ceil(input_size_);
    unsigned long input_size_, leaf_size_, node_size_, height_, total_storage_;
    static const unsigned long thres_ = 4;
}; 

#endif
