/*
 * ============================================================================
 *
 *       Filename:  lib_rbo_counter_d.hpp
 *
 *    Description:  library of d-dimensional m-bits RBO implemented by numbered value
 *                  RBO: Range Bit-wise Operation
 *                  Preprocessing:
 *                  Storage: m * N/log(N) * log (N/log(N)) bits
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

#ifndef LIB_RBO_COLOR_ARRAY_HPP
#define LIB_RBO_COLOR_ARRAY_HPP

#include <iostream>
#include "lib_common.hpp"

using namespace std;

template <int N_RANK, int COMPACT>
struct RBO_counter_d {
    public:
    unsigned long query_or(unsigned long (&lo)[N_RANK] /* inclusive */, unsigned long (&hi)[N_RANK] /* exclusive */) { 
    template <typename ... IS>
    RBO_counter_d(unsigned int _nbits, unsigned long * _input_array, IS ... _sizes) : input_array_(_input_array), nbits_(_nbits) { }
    ~RBO_counter_d() { }
    void print_info(void) { }
    void print_range(unsigned long * a, unsigned long * b) { }
    friend ostream & operator<<(std::ostream & fs, RBO_counter_d<N_RANK, COMPACT> const & rbo) { return fs; }
    private:
    unsigned long * input_array_;
    unsigned long * counter_d_;
    unsigned long stride_[N_RANK];
    unsigned int nbits_;
    unsigned long input_size_[N_RANK], total_size_;
}; 

template <int COMPACT>
struct RBO_counter_d <3, COMPACT> {
    public:
    inline unsigned long query_or(unsigned long (&lo)[3] /* inclusive */, unsigned long (&hi)[3] /* exclusive */) { 
        /* query the range [lo[], hi[]) */
        unsigned long _lo[3], _hi[3];
        _lo[0] = lo[0] - 1; _lo[1] = lo[1] - 1; _lo[2] = lo[2] - 1;
        _hi[0] = hi[0] - 1; _hi[1] = hi[1] - 1; _hi[2] = hi[2] - 1;
        unsigned long uuu = counter_d_[_hi[2] * stride_[2] + _hi[1] * stride_[1] + _hi[0]];
        unsigned long uul = (lo[0] == 0 ? 0 : counter_d_[_hi[2] * stride_[2] + _hi[1] * stride_[1] + _lo[0]]);
        unsigned long ulu = (lo[1] == 0 ? 0 : counter_d_[_hi[2] * stride_[2] + _lo[1] * stride_[1] + _hi[0]]);
        unsigned long luu = (lo[2] == 0 ? 0 : counter_d_[_lo[2] * stride_[2] + _hi[1] * stride_[1] + _hi[0]]);
        unsigned long ull = ((lo[1] == 0 | lo[0] == 0) ? 0 : counter_d_[_hi[2] * stride_[2] + _lo[1] * stride_[1] + _lo[0]]);
        unsigned long lul = ((lo[2] == 0 | lo[0] == 0) ? 0 : counter_d_[_lo[2] * stride_[2] + _hi[1] * stride_[1] + _lo[0]]);
        unsigned long llu = ((lo[2] == 0 | lo[1] == 0) ? 0 : counter_d_[_lo[2] * stride_[2] + _lo[1] * stride_[1] + _hi[0]]);
        unsigned long lll = ((lo[2] == 0 | lo[1] == 0 | lo[0] == 0) ? 0 : counter_d_[_lo[2] * stride_[2] + _lo[1] * stride_[1] + _lo[0] * stride_[0]]);
        return ((uuu + ull + lul + llu - uul - ulu - luu - lll) > 0);
    }
    inline void init_counter_d(void) {
        counter_d_ = new unsigned long[total_size_];
        const unsigned long bmask = 1ul << (nbits_ - 1);
        counter_d_[0] = ((input_array_[0] & bmask) > 0);
        /* initialize dim 0 */
        for (unsigned long i = 1; i < input_size_[0]; ++i) {
            counter_d_[i] = ((input_array_[i] & bmask) > 0) 
                            + counter_d_[i-1];
        }
        /* initialize dim 1 */
        for (unsigned long j = 1; j < input_size_[1]; ++j) {
            unsigned long l_idx = j * stride_[1];
            counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) 
                                + counter_d_[l_idx - stride_[1]];
        }
        /* initialize dim 2 */
        for (unsigned long k = 1; k < input_size_[2]; ++k) {
            unsigned long l_idx = k * stride_[2];
            counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) 
                                + counter_d_[l_idx - stride_[2]];
        }
        /* initialize the dim 0,1 */
        for (unsigned long j = 1; j < input_size_[1]; ++j) {
            for (unsigned long i = 1; i < input_size_[0]; ++i) {
                unsigned long l_idx = j * stride_[1] + i;
                counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) 
                                    + counter_d_[l_idx - 1] 
                                    + counter_d_[l_idx - stride_[1]] 
                                    - counter_d_[l_idx - stride_[1] - 1];
            } }
        /* initialize the dim 0,2 */
        for (unsigned long k = 1; k < input_size_[2]; ++k) {
            for (unsigned long i = 1; i < input_size_[0]; ++i) {
                unsigned long l_idx = k * stride_[2] + i;
                counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) 
                                    + counter_d_[l_idx - 1] 
                                    + counter_d_[l_idx - stride_[2]] 
                                    - counter_d_[l_idx - stride_[2] - 1];
            } }
        /* initialize the dim 1,2 */
        for (unsigned long k = 1; k < input_size_[2]; ++k) {
            for (unsigned long j = 1; j < input_size_[1]; ++j) {
                unsigned long l_idx = k * stride_[2] + j * stride_[1];
                counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) 
                                    + counter_d_[l_idx - stride_[2]] 
                                    + counter_d_[l_idx - stride_[1]] 
                                    - counter_d_[l_idx - stride_[2] - stride_[1]];
            } }
        /* initialize the dim 0,1,2 */
        for (unsigned long k = 1; k < input_size_[2]; ++k) {
            for (unsigned long j = 1; j < input_size_[1]; ++j) {
        for (unsigned long i = 1; i < input_size_[0]; ++i) {
            unsigned long l_idx = k * stride_[2] + j * stride_[1] + i;
            counter_d_[l_idx] = (((input_array_[l_idx] & bmask) > 0) 
                                + counter_d_[l_idx - stride_[2]] 
                                + counter_d_[l_idx - stride_[1]]
                                + counter_d_[l_idx - 1]
                                - counter_d_[l_idx - stride_[2] - stride_[1]]
                                - counter_d_[l_idx - stride_[2] - 1]
                                - counter_d_[l_idx - stride_[1] - 1]
                                + counter_d_[l_idx - stride_[2] - stride_[1] - 1]);

        } } }
        return;
    }
    template <typename I>
    inline void init_sizes(I _size) {
        input_size_[0] = _size; stride_[0] = 1;
        total_size_ = _size; 
        for (unsigned int i = 1; i < 3; ++i) {
            stride_[i] = input_size_[i-1] * stride_[i-1];
            total_size_ *= input_size_[i];
        }
    }
    template <typename I, typename ... IS>
    inline void init_sizes(I _size, IS ... _sizes) {
        unsigned int l_dim = sizeof...(IS);
        input_size_[l_dim] = _size;
        init_sizes(_sizes ...);
    }
    template <typename ... IS>
    RBO_counter_d(unsigned int _nbits, unsigned long * _input_array, IS ... _sizes) : input_array_(_input_array), nbits_(_nbits) {
        /* looks like for multi-dimensional space, the compression doesn't deserve its
         * existence since the auxillary array l_counter_[], r_counter_[] will be \Theta(N),
         * so the total storage and construction time will be 2 * N + N/log(N) > N
         */
        assert(COMPACT == 1);
        /* assuming the input is NOT bit-stream, we have to first convert it to bit-stream */
        /* first convert it to bit-stream */
        init_sizes(_sizes ...);
        struct timeval start, end;
        gettimeofday(&start, 0);
        init_counter_d();
        gettimeofday(&end, 0);
        printf("init_counter_d consumes %.6f\n", 1.0e3 * tdiff(&end, &start));

    }
    ~RBO_counter_d() {
        delete [] counter_d_;
    }
    void print_info(void) {
        cout << "\nRBO_counter_d (input size = [" << 
                input_size_[1] << ", " << input_size_[0] << "], nbits = " << nbits_ << ")\n";
        cout << "Total Storage = " << total_size_ << " words, or " <<
            total_size_ << " x (" << sizeof(unsigned long) << ") bits\n";
        cout << "-----------------------------------------------------------------------\n";
    }
    void print_range(unsigned long * a, unsigned long * b) {
        const unsigned long bmask = 1ul << (nbits_ - 1);
        cout << "\nRBO_counter_d (input size = [" << 
                input_size_[1] << ", " << input_size_[0] << "], nbits = " << nbits_ << ")\n";
        cout << "Total Storage = " << total_size_ << " words, or " <<
            total_size_ << " x (" << sizeof(unsigned long) << ") bits\n";
        cout << "-----------------------------------------------------------------------\n";
        for (unsigned long k = a[2]; k < b[2]; ++k) {
            for (unsigned long j = a[1]; j < b[1]; ++j) {
        unsigned long i;
        for (i = a[0]; i < b[0]-1; ++i) {
            cout << counter_d_[k * stride_[2] + j * stride_[1] + i] << ", ";
        } 
        cout << counter_d_[k * stride_[2] + j * stride_[1] + i] << "\n";
            }
            cout << "\n-----------------------------------------------------------------------\n";
        }
        cout << "\n-----------------------------------------------------------------------\n";
    }
    friend ostream & operator<<(std::ostream & fs, RBO_counter_d<3, COMPACT> const & rbo) {
        const unsigned long bmask = 1ul << (rbo.nbits_ - 1);
        fs << "\nRBO_counter_d (input size = [" << 
              rbo.input_size_[1] << ", " << rbo.input_size_[0] << "], nbits = " << rbo.nbits_ << ")\n";
        fs << "Total Storage = " << rbo.total_size_ << " words, or " <<
            rbo.total_size_ << " x (" << sizeof(unsigned long) << ") bits\n";
        fs << "-----------------------------------------------------------------------\n";
        for (unsigned long k = 0; k < rbo.input_size_[2]; ++k) {
            for (unsigned long j = 0; j < rbo.input_size_[1]; ++j) {
        unsigned long i;
        for (i = 0; i < rbo.input_size_[0]-1; ++i) {
            cout << rbo.input_array_[k * rbo.stride_[2] + j * rbo.stride_[1] + i] << " (" <<
                    rbo.counter_d_[k * rbo.stride_[2] + j * rbo.stride_[1] + i] << "), ";
        } 
        cout << rbo.input_array_[k * rbo.stride_[2] + j * rbo.stride_[1] + i] << " (" <<
                rbo.counter_d_[k * rbo.stride_[2] + j * rbo.stride_[1] + i] << ")\n";
            }
            fs << "\n-----------------------------------------------------------------------\n";
        }
        fs << "\n-----------------------------------------------------------------------\n";
        return fs;
    }
    private:
    unsigned long * input_array_;
    unsigned long * counter_d_;
    unsigned long stride_[3];
    unsigned int nbits_;
    unsigned long input_size_[3], total_size_;
}; 

template <int COMPACT>
struct RBO_counter_d <2, COMPACT> {
    public:
    inline unsigned long query_or(unsigned long (&lo)[2] /* inclusive */, unsigned long (&hi)[2] /* exclusive */) { 
        /* query the range [lo[], hi[]) */
        unsigned long _lo[2], _hi[2];
        _lo[0] = lo[0] - 1; _lo[1] = lo[1] - 1;
        _hi[0] = hi[0] - 1; _hi[1] = hi[1] - 1;
        unsigned long uu = counter_d_[_hi[1] * stride_[1] + _hi[0]];
        unsigned long ul = (lo[0] == 0 ? 0 : counter_d_[_hi[1] * stride_[1] + _lo[0]]);
        unsigned long lu = (lo[1] == 0 ? 0 : counter_d_[_lo[1] * stride_[1] + _hi[0]]);
        unsigned long ll = ((lo[1] == 0 | lo[0] == 0) ? 0 : counter_d_[_lo[1] * stride_[1] + _lo[0]]);
        return ((uu + ll - ul - lu) > 0);
    }
    inline void init_counter_d(void) {
        counter_d_ = new unsigned long[total_size_];
        const unsigned long bmask = 1ul << (nbits_ - 1);
        counter_d_[0] = ((input_array_[0] & bmask) > 0);
        /* initialize 0th row */
        for (unsigned long i = 1; i < input_size_[0]; ++i) {
            counter_d_[i] = ((input_array_[i] & bmask) > 0) + counter_d_[i-1];
        }
        /* initialize 0th column */
        for (unsigned long j = 1; j < input_size_[1]; ++j) {
            unsigned long l_idx = j * stride_[1];
            counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) + counter_d_[l_idx - stride_[1]];
        }
        /* initialize the middle range */
        for (unsigned long j = 1; j < input_size_[1]; ++j) {
            for (unsigned long i = 1; i < input_size_[0]; ++i) {
                unsigned long l_idx = j * stride_[1] + i;
                counter_d_[l_idx] = ((input_array_[l_idx] & bmask) > 0) 
                                    + counter_d_[l_idx - 1] 
                                    + counter_d_[l_idx - stride_[1]] 
                                    - counter_d_[l_idx - stride_[1] - 1];
            }
        }
        return;
    }
    template <typename I>
    inline void init_sizes(I _size) {
        input_size_[0] = _size; stride_[0] = 1;
        total_size_ = _size; 
        for (unsigned int i = 1; i < 2; ++i) {
            stride_[i] = input_size_[i-1] * stride_[i-1];
            total_size_ *= input_size_[i];
        }
    }
    template <typename I, typename ... IS>
    inline void init_sizes(I _size, IS ... _sizes) {
        unsigned int l_dim = sizeof...(IS);
        input_size_[l_dim] = _size;
        init_sizes(_sizes ...);
    }
    template <typename ... IS>
    RBO_counter_d(unsigned int _nbits, unsigned long * _input_array, IS ... _sizes) : input_array_(_input_array), nbits_(_nbits) {
        /* looks like for multi-dimensional space, the compression doesn't deserve its
         * existence since the auxillary array l_counter_[], r_counter_[] will be \Theta(N),
         * so the total storage and construction time will be 2 * N + N/log(N) > N
         */
        assert(COMPACT == 1);
        /* assuming the input is NOT bit-stream, we have to first convert it to bit-stream */
        /* first convert it to bit-stream */
        init_sizes(_sizes ...);
        struct timeval start, end;
        gettimeofday(&start, 0);
        init_counter_d();
        gettimeofday(&end, 0);
        printf("init_counter_d consumes %.6f\n", 1.0e3 * tdiff(&end, &start));

    }
    ~RBO_counter_d() {
        delete [] counter_d_;
    }
    void print_info(void) {
        cout << "\nRBO_counter_d (input size = [" << 
                input_size_[1] << ", " << input_size_[0] << "], nbits = " << nbits_ << ")\n";
        cout << "Total Storage = " << total_size_ << " words, or " <<
            total_size_ << " x (" << sizeof(unsigned long) << ") bits\n";
        cout << "-----------------------------------------------------------------------\n";
    }
    void print_range(unsigned long * a, unsigned long * b) {
        const unsigned long bmask = 1ul << (nbits_ - 1);
        cout << "\nRBO_counter_d (input size = [" << 
                input_size_[1] << ", " << input_size_[0] << "], nbits = " << nbits_ << ")\n";
        cout << "Total Storage = " << total_size_ << " words, or " <<
            total_size_ << " x (" << sizeof(unsigned long) << ") bits\n";
        cout << "-----------------------------------------------------------------------\n";
        for (unsigned long j = a[1]; j < b[1]; ++j) {
            unsigned long i;
            for (i = a[0]; i < b[0]-1; ++i) {
                cout << counter_d_[j * stride_[1] + i] << ", ";
            } 
            cout << counter_d_[j * stride_[1] + i] << "\n";
        }
        cout << "\n-----------------------------------------------------------------------\n";
    }
    friend ostream & operator<<(std::ostream & fs, RBO_counter_d<2, COMPACT> const & rbo) {
        const unsigned long bmask = 1ul << (rbo.nbits_ - 1);
        fs << "\nRBO_counter_d (input size = [" << 
              rbo.input_size_[1] << ", " << rbo.input_size_[0] << "], nbits = " << rbo.nbits_ << ")\n";
        fs << "Total Storage = " << rbo.total_size_ << " words, or " <<
            rbo.total_size_ << " x (" << sizeof(unsigned long) << ") bits\n";
        fs << "-----------------------------------------------------------------------\n";
        for (unsigned long j = 0; j < rbo.input_size_[1]; ++j) {
            unsigned long i;
            for (i = 0; i < rbo.input_size_[0]-1; ++i) {
                cout << rbo.input_array_[j * rbo.stride_[1] + i] << " (" <<
                        rbo.counter_d_[j * rbo.stride_[1] + i] << "), ";
            } 
            cout << rbo.input_array_[j * rbo.stride_[1] + i] << " (" <<
                    rbo.counter_d_[j * rbo.stride_[1] + i] << ")\n";
        }
        fs << "\n-----------------------------------------------------------------------\n";
        return fs;
    }
    private:
    unsigned long * input_array_;
    unsigned long * counter_d_;
    unsigned long stride_[2];
    unsigned int nbits_;
    unsigned long input_size_[2], total_size_;
}; 

template <int COMPACT>
struct RBO_counter_d <1, COMPACT> {
    public:
    inline unsigned long query_or(unsigned long lo /* inclusive */, unsigned long hi /* exclusive */) { 
        /* query the range [lo, hi) => [_lo, _hi] */
        unsigned long _lo = lo, _hi = hi - 1;

        unsigned long g_lo_pos = div<COMPACT>(_lo), g_hi_pos = div<COMPACT>(_hi);
        unsigned long l_lo_pos = mod<COMPACT>(_lo), l_hi_pos = mod<COMPACT>(_hi);
        if (g_lo_pos == g_hi_pos) {
            /* bit-trick for intra-group query */
            return (((bstream_[g_lo_pos] >> l_lo_pos) << (l_lo_pos + 63 - l_hi_pos)) > 0);
        } else {
            assert(g_hi_pos - g_lo_pos >= 1);
            unsigned long msb_lo = msb_i(bstream_[g_lo_pos], l_lo_pos);
            unsigned long lsb_hi = lsb_i(bstream_[g_hi_pos], l_hi_pos+1);
            
            return (((counter_d_[g_hi_pos-1] - counter_d_[g_lo_pos]) | msb_lo | lsb_hi) > 0);
        }
    }

    inline void init_bstream(unsigned long * _input_array, unsigned long _size) {
        bstream_size_ = div_ceil<COMPACT>(_size);
        bstream_ = new unsigned long[bstream_size_];
        memset(bstream_, 0, bstream_size_ * sizeof(unsigned long));
        // for (unsigned long i = 0; i < bstream_size_; ++i) 
        //     bstream_[i] = 0;
        const unsigned long bmask = 0x1 << (nbits_ - 1);
        unsigned long i = 0;
        unsigned long g_pos = 0;
        const unsigned long l_loop = _size - mod<COMPACT>(_size);
        for (i = 0; i < l_loop; i+=COMPACT, ++g_pos) {
            bstream_[g_pos] = unfold_compact<COMPACT>(_input_array, i, bmask);
        }
        unsigned long l_pos = 0;
        for (; i < _size; ++i, ++l_pos) {
            bstream_[g_pos] |= ((_input_array[i] & bmask) << l_pos);
        }
        return;
    }
    inline void init_counter_d(void) {
        counter_d_ = new unsigned long[bstream_size_];
        unsigned int nbits = __builtin_popcountl(bstream_[0]);
        unsigned int inc = (nbits == COMPACT ? 2 : (nbits > 0 ? 1 : 0));
        counter_d_[0] = inc;
        for (unsigned long i = 1; i <= bstream_size_; ++i) {
            nbits = __builtin_popcountl(bstream_[i]);
            inc = (nbits == COMPACT ? 2 : (nbits > 0 ? 1 : 0));
            counter_d_[i] = counter_d_[i-1] + inc;
        }
        return;
    }
    RBO_counter_d(unsigned int _nbits, unsigned long * _input_array, unsigned long _size) : input_size_(_size), nbits_(_nbits) {
        /* assuming the input is NOT bit-stream, we have to first convert it to bit-stream */
        /* first convert it to bit-stream */
        struct timeval start, end;
        gettimeofday(&start, 0);
        init_bstream(_input_array, _size);
        gettimeofday(&end, 0);
        printf("init_stream consumes %.6f\n", 1.0e3 * tdiff(&end, &start));
        gettimeofday(&start, 0);
        init_counter_d();
        gettimeofday(&end, 0);
        printf("init_counter_d consumes %.6f\n", 1.0e3 * tdiff(&end, &start));

    }
    ~RBO_counter_d() {
        delete [] bstream_;
        delete [] counter_d_;
    }
    void print_info(void) {
        const unsigned long bmask = 1ul << (nbits_ - 1);
        cout << "\nRBO_counter_d (input size = " << input_size_ << ", nbits = " << nbits_ << ")\n";
        cout << "Total Storage = " << bstream_size_ << " words, or " <<
            bstream_size_ << " x (" << COMPACT << ") bits\n";
        cout << "-----------------------------------------------------------------------\n";
    }
    void print_range(unsigned long a, unsigned long b) {
        const unsigned long bmask = 1ul << (nbits_ - 1);
        cout << "\nRBO_counter_d (input size = " << input_size_ << ", nbits = " << nbits_ << ")\n";
        cout << "Total Storage = " << bstream_size_ << " words, or " <<
            bstream_size_ << " x (" << COMPACT << ") bits\n";
        cout << "-----------------------------------------------------------------------\n";
        for (unsigned long i = a; i < b; i+=4) {
            cout << "[";
            for (unsigned long j = i; j < i+4 && j < b; ++j) {
                unsigned long g_pos = div<COMPACT>(j), l_pos = mod<COMPACT>(i);
                cout << ((bstream_[g_pos] & (bmask << l_pos)) > 0);
            }
            cout << "] ";
        } 
        cout << "\n-----------------------------------------------------------------------\n";

        unsigned long _lo = a, _hi = b - 1;

        unsigned long g_lo_pos = div<COMPACT>(_lo), g_hi_pos = div<COMPACT>(_hi);
        unsigned long l_lo_pos = mod<COMPACT>(_lo), l_hi_pos = mod<COMPACT>(_hi);
        if (g_lo_pos == g_hi_pos) {
            /* bit-trick for intra-group query */
            cout << "g_lo_pos = g_hi_pos = " << g_lo_pos << endl;
            cout << "l_lo_pos = " << l_lo_pos << ", l_hi_pos = " << l_hi_pos << endl;
            cout << "bstream_[" << g_lo_pos << "] = " << hex << bstream_[g_lo_pos] << endl;
            cout << hex << ((bstream_[g_lo_pos] >> l_lo_pos) << (l_lo_pos + 63 - l_hi_pos)) << endl;
        } else {
            assert(g_hi_pos - g_lo_pos >= 1);
            unsigned long msb_lo = msb_i(bstream_[g_lo_pos], l_lo_pos);
            unsigned long lsb_hi = lsb_i(bstream_[g_hi_pos], l_hi_pos+1);
            
            cout << "g_lo_pos = " << g_lo_pos << ", g_hi_pos = " << g_hi_pos << endl;
            cout << "l_lo_pos = " << l_lo_pos << ", l_hi_pos = " << l_hi_pos << endl;
            cout << "msb_lo = [";
            for (unsigned long i = l_lo_pos; i < 64; ++i) 
                cout << ((bstream_[g_lo_pos] & (bmask << i)) > 0);
            cout << "] (" << msb_lo << ")\t";

            cout << "lsb_hi = [";
            for (unsigned long i = 0; i <= l_hi_pos; ++i) 
                cout << ((bstream_[g_hi_pos] & (bmask << i)) > 0);
            cout << "] (" << lsb_hi << ")\n";

            cout << "counter_d_[" << g_lo_pos << "] = " << counter_d_[g_lo_pos] <<
                ", counter_d_[" << g_hi_pos - 1 << "] = " << counter_d_[g_hi_pos-1] <<
                ", counter_d_[" << g_hi_pos << "] = " << counter_d_[g_hi_pos] << endl;
        }
    }
    friend ostream & operator<<(std::ostream & fs, RBO_counter_d<1, COMPACT> const & rbo) {
        const unsigned long bmask = 1ul << (rbo.nbits_ - 1);
        fs << "\nRBO_counter_d (input size = " << rbo.input_size_ << ", nbits = " << rbo.nbits_ << ")\n";
        fs << "Total Storage = " << rbo.bstream_size_ << " words, or " <<
            rbo.bstream_size_ << " x (" << COMPACT << ") bits\n";
        fs << "-----------------------------------------------------------------------\n";
        const unsigned long l_input_size = rbo.input_size_;
        for (unsigned long i = 0; i < l_input_size; i+=4) {
            fs << "[";
            for (unsigned long j = i; j < i+4 && j < l_input_size; ++j) {
                unsigned long g_pos = div<COMPACT>(j), l_pos = mod<COMPACT>(i);
                fs << ((rbo.bstream_[g_pos] & (bmask << l_pos)) > 0);
            }
            fs << "] ";
        } 
        fs << "\n-----------------------------------------------------------------------\n";
        return fs;
    }
    private:
    unsigned long * bstream_;
    unsigned long * counter_d_;
    unsigned int nbits_;
    unsigned long input_size_;
    unsigned long bstream_size_;
}; 

#endif
