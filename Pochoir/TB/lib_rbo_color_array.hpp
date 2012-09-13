/*
 * ============================================================================
 *
 *       Filename:  lib_rbo_color_array.hpp
 *
 *    Description:  library of RBT implemented by color array 
 *                  RBO: Range Bit-wise operations
 *                  Preprocessing:
 *                  Storage: N/64 * log (N/64) bits
 *                  computing complexity: N or N/64 depending on the input
 *                  Query: \Theta(1)
 *
 *        Version:  1.0
 *        Created:  03/09/2012 06:26:14 PM
 *       Revision:  none
 *       Compiler:  gcc/icc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#ifndef LIB_RBT_COLOR_ARRAY_HPP
#define LIB_RBT_COLOR_ARRAY_HPP

#include <iostream>
#include "lib_common.hpp"

using namespace std;

struct RBT_color_array {
    /* use bit-vector left-or/right-or for bit-wise or query */
    public:
    inline unsigned long query_or(unsigned long lo /* inclusive */, unsigned long hi /* exclusive */) { 
        /* query the range [lo, hi) => [_lo, _hi] */
        unsigned long _lo = lo, _hi = hi - 1;

        unsigned long g_lo_pos = div<64>(_lo), g_hi_pos = div<64>(_hi);
        unsigned long l_lo_pos = mod<64>(_lo), l_hi_pos = mod<64>(_hi);
        if (g_lo_pos == g_hi_pos) {
            /* bit-trick for intra-group query */
            return (((bstream_[g_lo_pos] >> l_lo_pos) << (l_lo_pos + 63 - l_hi_pos)) > 0);
        } else if (color_array_[g_lo_pos] == color_array_[g_hi_pos]) {
            return (bstream_[g_lo_pos] > 0);
        } else if (color_array_[g_lo_pos] + 1 == color_array_[g_hi_pos]) {
            /* bit-trick for inter-group query */
            unsigned long msb_lo = msb_i(bstream_[g_lo_pos], l_lo_pos);
            unsigned long lsb_hi = lsb_i(bstream_[g_hi_pos], l_hi_pos);
            // return ((msb_lo != lsb_hi) | (msb_lo > 0)); 
            return ((msb_lo | lsb_hi) > 0); 
        } else
            return 1;
    }

    inline void init_bstream(unsigned long * _input_array, unsigned long _size, unsigned int _nbits) {
        bstream_size_ = div_ceil<64>(_size);
        bstream_ = new unsigned long[bstream_size_];
        for (unsigned long i = 0; i < bstream_size_; ++i) 
            bstream_[i] = 0;
        const unsigned long bmask = 0x1 << (_nbits - 1);
        unsigned long i = 0;
        unsigned long g_pos = 0;
        const unsigned long l_loop = _size - mod<64>(_size);
        for (i = 0; i < l_loop; i+=64, ++g_pos) {
            bstream_[g_pos] = unfold_compact<64>(_input_array, i, bmask); 
        }
        unsigned long l_pos = 0;
        for (; i < _size; ++i, ++l_pos) {
            bstream_[g_pos] |= ((_input_array[i] & bmask) << l_pos);
        }
        return;
    }
    inline void init_color_array(void) {
        color_array_ = new unsigned long[bstream_size_];
        unsigned long color = 0;
        color_array_[0] = 0;
        for (unsigned long i = 1; i < bstream_size_; ++i) {
            unsigned long inc_color = 1 - ((bstream_[i] == bstream_[i-1]) & ((bstream_[i] == ALLZERO64) | (bstream_[i] == ALLONE64)));
            color += inc_color;
            color_array_[i] = color;
        }
        return;
    }
    RBT_color_array(unsigned long * _input_array, unsigned long _size, unsigned int _nbits) : input_size_(_size), nbits_(_nbits) {
        /* assuming the input is NOT bit-stream, we have to first convert it to bit-stream */
        /* first convert it to bit-stream */
        struct timeval start, end;
        gettimeofday(&start, 0);
        init_bstream(_input_array, _size, _nbits);
        gettimeofday(&end, 0);
        printf("init_stream consumes %.6f\n", 1.0e3 * tdiff(&end, &start));
        gettimeofday(&start, 0);
        init_color_array();
        gettimeofday(&end, 0);
        printf("init_color_array consumes %.6f\n", 1.0e3 * tdiff(&end, &start));

    }
    ~RBT_color_array() {
        delete [] bstream_;
        delete [] color_array_;
    }
    friend ostream & operator<<(std::ostream & fs, RBT_color_array const & rbo) {
        const unsigned long bmask = 1ul << (rbo.nbits_ - 1);
        fs << "\nRBT_color_array (input size = " << rbo.input_size_ << ", bstream size = " << rbo.bstream_size_ << ", nbits = " << rbo.nbits_ << ")\n";
        fs << "-----------------------------------------------------------------------\n";
        const unsigned long l_input_size = rbo.input_size_;
        for (unsigned long i = 0; i < l_input_size; i+=4) {
            fs << "[";
            for (unsigned long j = i; j < i+4 && j < l_input_size; ++j) {
                unsigned long g_pos = div<64>(j), l_pos = mod<64>(i);
                fs << ((rbo.bstream_[g_pos] & (bmask << l_pos)) > 0);
            }
            fs << "] ";
        } 
        fs << "\n-----------------------------------------------------------------------\n";
        return fs;
    }
    private:
    unsigned long * bstream_;
    unsigned long * color_array_;
    unsigned int nbits_;
    unsigned long input_size_, bstream_size_;
}; 

#endif
