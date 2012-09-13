/*
 * ============================================================================
 *
 *       Filename:  lib_rbt_idx.hpp
 *
 *    Description:  library of struct 'RBT_idx'
 *
 *        Version:  1.0
 *        Created:  03/09/2012 12:13:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#ifndef LIB_RBT_IDX_HPP
#define LIB_RBT_IDX_HPP

#include <iostream>
#include "lib_common.hpp"

#define REC 1
using namespace std;

struct RBT_idx {
    /* use bit-vector left-or/right-or for bit-wise or query */
    public:
    inline unsigned long query(unsigned long lo /* inclusive */, unsigned long hi /* inclusive */) { 
        /* (lo, hi) is original index pair in input array,
         * (_lo, _hi) is the rbt idx in the tree
         */
        /* lca : lowest common ancestor; lcp : longest common prefix */
        /* + leaf_size_: to get the rbt_idx of (lo, hi) */
        unsigned long lca, rbt_l_idx, rbt_r_idx;
        unsigned long _lo = lo + leaf_size_, _hi = hi + leaf_size_;
        if (_lo == _hi) {
            /* lo and hi resides in same leaf node */
            _lo >>= 1; _hi >>= 1;
            lca = _lo >> 1;
            rbt_l_idx = _lo - 1; rbt_r_idx = _hi - 1;
        } else {
            lca = lcp(_lo, _hi);
            rbt_l_idx = (lca << 1) - 1, rbt_r_idx = (lca << 1);
        }
        unsigned long rbt_idx = rbt_l_idx >> 1;
        unsigned int set = (set_[rbt_l_idx] << 1) | (set_[rbt_r_idx]);
        switch (set) {
            case 0: /* lset == 0 && rset == 0 */
                do {
                    return 0;
                } while (0);
                break;
            case 1: /* lset == 0 && rset == 1 */
                do {
                    if (hi < l1_[rbt_r_idx])
                        return 0;
                    else
                        return 1;
                } while (0);
                break;
            case 2: /* lset == 1 && rset == 0 */
                do {
                    if (lo > r1_[rbt_l_idx])
                        return 0;
                    else
                        return 1;
                } while (0);
                break;
            case 3: /* lset == 1 && rset == 1 */
                do {
                    if ((lo == hi && (hi < l1_[rbt_l_idx] || lo > r1_[rbt_r_idx])) 
                         || (lo > r1_[rbt_l_idx] && hi < l1_[rbt_r_idx]))
                        return 0;
                    else
                        return 1;
                } while (0);
                break;
            default:
                break;
        } /* end switch */
        return 0; 
    }
    inline void mkSubTree(
            unsigned long _height, /* height decides the iteration # */ 
            /* [_l_node, _r_node) decides the iteration range of 
             * the bottom level of the sub-tree
             */
            unsigned long _l_node, /* inclusive */
            unsigned long _r_node /* exclusive */) 
    {
        unsigned long rbt_idx = _l_node - 1; 
        unsigned long rbt_l_idx = (_l_node << 1) - 1, rbt_r_idx = (_l_node << 1);
        for (unsigned long l = 1; l <= _height; ++l,
                _l_node >>= 1, _r_node >>= 1,
                rbt_idx >>= 1, rbt_l_idx >>= 1, rbt_r_idx >>= 1) {
                unsigned long _rbt_idx = rbt_idx,
                              _rbt_l_idx = rbt_l_idx,
                              _rbt_r_idx = rbt_r_idx;
            for (unsigned long node = _l_node; node < _r_node; ++node) {
                unsigned int l_set = (set_[_rbt_l_idx] << 1) | (set_[_rbt_r_idx]);
                switch (l_set) {
                    case 0: /* lset == 0 && rset == 0 */
                        do {
                            set_[_rbt_idx] = false;
                            /* if set_[] == false, l1_[] r1_[] will be left undefined */
                            l1_[_rbt_idx] = INF;
                            r1_[_rbt_idx] = NINF;
                        } while (0);
                        break;
                    case 1: /* lset == 0 && rset == 1 */
                        do {
                            set_[_rbt_idx] = true;
                            l1_[_rbt_idx] = l1_[_rbt_r_idx];
                            r1_[_rbt_idx] = r1_[_rbt_r_idx];
                        } while (0);
                        break;
                    case 2: /* lset == 1 && rset == 0 */
                        do {
                            set_[_rbt_idx] = true;
                            l1_[_rbt_idx] = l1_[_rbt_l_idx];
                            r1_[_rbt_idx] = r1_[_rbt_l_idx];
                        } while (0);
                        break;
                    case 3: /* lset == 1 && rset == 1 */
                        do {
                            set_[_rbt_idx] = true;
                            l1_[_rbt_idx] = l1_[_rbt_l_idx];
                            r1_[_rbt_idx] = r1_[_rbt_r_idx];
                        } while (0);
                        break;
                    default: 
                        break;
                }
                ++_rbt_idx; _rbt_l_idx += 2; _rbt_r_idx += 2;
            }
        }
        return;
    }
    inline void mkTree_recursive(
            unsigned long _height, 
            unsigned long _l_node, /* inclusive */
            unsigned long _r_node /* exclusive */) 
    { 
        /* [_l_node, _r_node) are the rbt_idx  */
        unsigned long nnodes = _r_node - _l_node;
        // if (nnodes < thres_) {
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
        /* merge the results bottom up !!! */
        unsigned long height = _height - (_height >> 1);
        unsigned long l_node = _l_node >> (_height >> 1), r_node = _r_node >> (_height >> 1);
        mkSubTree(height, l_node, r_node);
        return; 
    }
    inline void mkTree_loop(
            unsigned long _height, 
            unsigned long l_node, 
            unsigned long r_node) 
    {
        mkSubTree(height_, l_node, r_node);
        return;
    }
    RBT_idx(unsigned long * _input_array, unsigned long _size, unsigned int _nbits) : input_size_(_size), nbits_(_nbits) {
        height_ = log2_ceil(_size);
        leaf_size_ = pow2(height_);
        node_size_ = (leaf_size_ << 1) - 1;
        /* total_storage_ includes l1_ and r1_ */
        total_storage_ = 2 * node_size_;
        l1_ = new unsigned long[node_size_];
        r1_ = new unsigned long[node_size_];
        set_ = new bool[node_size_];
        input_array_ = new unsigned long[leaf_size_];
        unsigned long l_rbt_lb = leaf_size_ - 1, l_rbt_rb = node_size_;
        unsigned long l_bmask = 1ul << (_nbits - 1);
        /* initialize the leaves with input array */
        for (unsigned long i = 0; i < _size; ++i) {
            set_[l_rbt_lb + i] = _input_array[i] & l_bmask;
            l1_[l_rbt_lb + i] = set_[l_rbt_lb + i] ? i : INF;
            r1_[l_rbt_lb + i] = set_[l_rbt_lb + i] ? i : NINF;
            input_array_[i] = _input_array[i];
        }
        for (unsigned long i = _size; i < leaf_size_; ++i) {
            set_[l_rbt_lb + i] = false;
            l1_[l_rbt_lb + i] = INF;
            r1_[l_rbt_lb + i] = NINF;
            input_array_[i] = 0;
        } 
        unsigned long l_node = pow2(height_ - 1), r_node = l_node << 1;
#if REC 
#ifdef DEBUG
        printf("RBT_idx::mkTree_recursive\n");
#endif
        mkTree_recursive(height_, l_node, r_node);
#else
#ifdef DEBUG
        printf("RBT_idx::mkTree_loop\n");
#endif
        mkTree_loop(height_, l_node, r_node);
#endif
    }
    ~RBT_idx() {
        delete [] l1_;
        delete [] r1_;
        delete [] set_;
        delete [] input_array_;
    }
    friend ostream & operator<<(std::ostream & fs, RBT_idx const & rbt) {
        unsigned long nentry = rbt.leaf_size_;
        const unsigned long bmask = 1ul << (rbt.nbits_ - 1);
        fs << "\nRBT_idx (input size = " << rbt.input_size_ << ", leaf size = " << rbt.leaf_size_
            << ", height = " << rbt.height_ << ", nbits = " << rbt.nbits_ << ")\n";
        fs << "     total nodes = " << rbt.node_size_ 
            << ", total storage = " << rbt.total_storage_ << "\n";
        fs << "-----------------------------------------------------------------------\n";
        for (unsigned int l = 0; l <= rbt.height_; ++l) {
            unsigned long l_node = pow2(l) - 1, r_node = l_node + pow2(l);
            for (unsigned long node = l_node; node < r_node; ++node) {
                fs << "[";
                if (rbt.l1_[node] == INF) 
                    fs << "INF";
                else
                    fs << rbt.l1_[node];
                fs << ", ";
                if (rbt.r1_[node] == NINF)
                    fs << "NINF";
                else 
                    fs << rbt.r1_[node];
                fs <<"]";
                fs << " (" << (rbt.set_[node] ? "1" : "0") << ")\t";
            }
            fs << "\n";
        }
        for (unsigned long i = 0; i < rbt.leaf_size_; ++i) {
            fs << "[" << rbt.input_array_[i] << "]\t";
        }
        fs << "\n-----------------------------------------------------------------------\n";
        return fs;
    }
    private:
    /* l1_: index of left-most '1'; r1_: index of right-most '1' */
    unsigned long *l1_, *r1_;
    unsigned long *input_array_;
    unsigned int nbits_;
    bool *set_;
    // node_size_ = 2^m, where m = log2_ceil(input_size_);
    unsigned long input_size_, leaf_size_, node_size_, height_, total_storage_;
    static const unsigned long INF = 0xffffffffffffffff;
    static const unsigned long NINF = 0xfffffffffffffffe;
    // static const unsigned long NINF = 0x0;
    static const unsigned long thres_ = 4;
}; 

#endif
