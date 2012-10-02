/*  Copyright (c) 2010 6.172 Staff

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

/* Implements the ADT specified in bitarray.h as a packed array of bits; a
 * bitarray containing bit_sz bits will consume roughly bit_sz/8 bytes of
 * memory. */

#include <assert.h>
#include <stdio.h>

#include "bitarray.h"

// Byte Reversal Lookup Table
static const unsigned char BitReverseTable256[] = 
{
	  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
	  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
	  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
	  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
	  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
	  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
	  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
	  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
	  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
	  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
	  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
	  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
	  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
	  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
	  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
	  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

/* Internal representation of the bit array. */
struct bitarray {
  /* The number of bits represented by this bit array. Need not be divisible by 8. */
  size_t bit_sz;
  /* The underlying memory buffer that stores the bits in packed form (8 per byte). */
  unsigned char *buf;
};

bitarray_t *bitarray_new(size_t bit_sz) {
  /* Allocate an underlying buffer of ceil(bit_sz/8) bytes. */
  unsigned char *buf = calloc(1, bit_sz / 8 + ((bit_sz % 8 == 0) ? 0 : 1));
  if (buf == NULL)
    return NULL;
  bitarray_t *ret = malloc(sizeof(struct bitarray));
  if (ret == NULL) {
    free(buf);
    return NULL;
  }
  ret->buf = buf;
  ret->bit_sz = bit_sz;
  return ret;
}

void bitarray_free(bitarray_t *ba) {
  if (ba == NULL)
    return;
  free(ba->buf);
  ba->buf = NULL;
  free(ba);
}

size_t bitarray_get_bit_sz(bitarray_t *ba) {
  return ba->bit_sz;
}

/* Portable modulo operation that supports negative dividends. */
static size_t modulo(ssize_t n, size_t m) {
  /* See
  http://stackoverflow.com/questions/1907565/c-python-different-behaviour-of-the-modulo-operation */
  /* Mod may give different result if divisor is signed. */
  ssize_t sm = (ssize_t) m;
  assert(sm > 0);
  ssize_t ret = ((n % sm) + sm) % sm;
  assert(ret >= 0);
  return (size_t) ret;
}

// Given a bit index, returns the mask to be applied to a byte to get the right bit at that index.
#define bitmask(bit_index) (1 << (bit_index % 8))

//Provided function, get ba[bit_index]
bool bitarray_get(bitarray_t *ba, size_t bit_index) {
  assert(bit_index < ba->bit_sz);
  return (ba->buf[bit_index >> 3] & bitmask(bit_index)) ? true : false;
}

//Provided function, set ba[bit_index] to val
void bitarray_set(bitarray_t *ba, size_t bit_index, bool val) {
  assert(bit_index < ba->bit_sz);
  ba->buf[bit_index >> 3]
	  = (ba->buf[bit_index >> 3] & ~bitmask(bit_index)) | (val ? bitmask(bit_index) : 0);

}

size_t bitarray_count_flips(bitarray_t *ba, size_t bit_off, size_t bit_len) {
  assert(bit_off + bit_len <= ba->bit_sz);
  size_t i, ret = 0;
  /* Go from the first bit in the substring to the second to last one. For each bit, count another
  transition if the bit is different from the next one. Note: do "i + 1 < bit_off + bit_len" instead
  of "i < bit_off + bit_len - 1" to prevent wraparound in the case where bit_off + bit_len == 0. */
  for (i = bit_off; i + 1 < bit_off + bit_len; i++) {
    if (bitarray_get(ba, i) != bitarray_get(ba, i + 1))
      ret++;
  }
  return ret;
}

//Rotates a bitarray ba, starting at bit_off and ending at bit_len.  Rotate around bit_right_amount.
void bitarray_rotate(bitarray_t *ba, size_t bit_off, size_t bit_len, ssize_t bit_right_amount) {
  assert(bit_off + bit_len <= ba->bit_sz);
  if ((bit_len == 0) || !(bit_off + bit_len <= ba->bit_sz)) return;

	size_t l = bit_off;
	size_t r = bit_off + bit_len - 1;
	size_t m = l + modulo(-bit_right_amount, bit_len);
	
	if ( m == 0) return;

  /* Convert a rotate left or right to a left rotate only, and eliminate multiple full rotations. */
	  reverse(ba, l, m - 1);
	  reverse(ba, m, r);
	  reverse(ba, l, r);
}

//Returns a byte mask that will cover the left most bits until bit_index
inline static char leftmask(size_t bit_index){
	return (((unsigned char) 0xFF) >> (8 - (bit_index % 8)));
}

//Returns a byte mask that will cover the right most bits, starting at bit_index
inline static char rightmask(size_t bit_index){
	return (((unsigned char) 0xFF) << ((bit_index % 8) < 7 ? (bit_index + 1) % 8 : 8));
} 

//Right shifts a segment of the bitarray from start to end by 0 <= amount <= 8.
void rshift(bitarray_t *ba, size_t start, size_t end, unsigned char amount){	
	if (start == end){
		ba->buf[start] = (ba->buf[start] << amount);
	} else {
		size_t i = start;
		unsigned char prevchar = 0;
		while (i <= end){
			unsigned char finalchar = ((ba->buf[i] & ~leftmask(8 - amount)) >> (8 - amount));
			ba->buf[i] <<= amount;						
			ba->buf[i] |= prevchar;
			prevchar = finalchar;
			i++;
		}
	}
}

//Left shifts a segment of the bitaray from start to end by 0 <= amount <= 8.
void lshift(bitarray_t *ba, size_t start, size_t end, unsigned char amount){	
	if (start == end){
		ba->buf[start] = (ba->buf[start] >> amount);
	} else {
		size_t i = end;
		unsigned char prevchar = 0;
		while (i >= start){
			unsigned char finalchar = ((ba->buf[i] & leftmask(amount)) << (8 - amount));
			ba->buf[i] >>= amount;
			ba->buf[i] |= prevchar;
			prevchar = finalchar;
			i--;
		}
	}
}

//Reverses a segment of bitarray ba, from start to end
static void reverse(bitarray_t *ba, size_t start, size_t end){
	//Protects the left-most and right-most bits that should not be rotated.
	char leftdata = ba->buf[start >> 3] & leftmask(start);	
	char rightdata = ba->buf[end >> 3] & rightmask(end);
	
	size_t left = start >> 3;
	size_t right = end >> 3;
	
	//Reverses the bits.
	while (left < right){
		char t1 = BitReverseTable256[ba->buf[left]];
		ba->buf[left] = BitReverseTable256[ba->buf[right]];
		ba->buf[right] = t1;
		
		left++; right--;
	}
	
	if (left == right){
		ba->buf[left] = BitReverseTable256[ba->buf[left]];
	}

 	int diff = start%8 - ((7 - end)%8);
	
	//Shifts left or right based to adjust for the reversal.
	if (diff > 0){
		rshift(ba, start>>3, end >> 3, diff);
	} else if (diff < 0){
		lshift(ba, start>>3, end >> 3, abs(diff));
	}

	//Replaces the left-most and right-most bits after the rotation, assure correctness
	ba->buf[start >> 3] = (ba->buf[start >> 3] & ~leftmask(start)) | leftdata;
	ba->buf[end >> 3] = (ba->buf[end >> 3] & ~rightmask(end)) | rightdata;
}

