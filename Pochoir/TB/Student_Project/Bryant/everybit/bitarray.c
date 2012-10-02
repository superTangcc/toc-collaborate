/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

// Implements the ADT specified in bitarray.h as a packed array of bits; a bit
// array containing bit_sz bits will consume roughly bit_sz/8 bytes of
// memory.


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>

#include "./bitarray.h"
//Precomputed lookup table that contains reversals of all 16-bit words
#include "./sixteen_bit_table.h"

// ********************************* Types **********************************

// Concrete data type representing an array of bits.
struct bitarray {
  // The number of bits represented by this bit array.
  // Need not be divisible by 8.
  size_t bit_sz;

  // The underlying memory buffer that stores the bits in
  // packed form (8 per byte).
  char *buf;
};


// ******************** Prototypes for static functions *********************

// Rotates a subarray left by an arbitrary number of bits.
//
// bit_offset is the index of the start of the subarray
// bit_length is the length of the subarray, in bits
// bit_left_amount is the number of places to rotate the
//                    subarray left
//
// The subarray spans the half-open interval
// [bit_offset, bit_offset + bit_length)
// That is, the start is inclusive, but the end is exclusive.
static void bitarray_rotate_left(bitarray_t *const bitarray,
                                  const size_t bit_offset,
                                  const size_t bit_length,
                                  const size_t bit_left_amount);

// Rotates a subarray left by one bit.
//
// bit_offset is the index of the start of the subarray
// bit_length is the length of the subarray, in bits
//
// The subarray spans the half-open interval
// [bit_offset, bit_offset + bit_length)
// That is, the start is inclusive, but the end is exclusive.
static void bitarray_rotate_left_one(bitarray_t *const bitarray,
                                     const size_t bit_offset,
                                     const size_t bit_length);

// Portable modulo operation that supports negative dividends.
//
// Many programming languages define modulo in a manner incompatible with its
// widely-accepted mathematical definition.
// http://stackoverflow.com/questions/1907565/c-python-different-behaviour-of-the-modulo-operation
// provides details; in particular, C's modulo
// operator (which the standard calls a "remainder" operator) yields a result
// signed identically to the dividend e.g., -1 % 10 yields -1.
// This is obviously unacceptable for a function which returns size_t, so we
// define our own.
//
// n is the dividend and m is the divisor
//
// Returns a positive integer r = n (mod m), in the range
// 0 <= r < m.
static size_t modulo(const ssize_t n, const size_t m);

// Produces a mask which, when ANDed with a byte, retains only the
// bit_index th byte.
//
// Example: bitmask(5) produces the byte 0b00100000.
//
// (Note that here the index is counted from right
// to left, which is different from how we represent bitarrays in the
// tests.  This function is only used by bitarray_get and bitarray_set,
// however, so as long as you always use bitarray_get and bitarray_set
// to access bits in your bitarray, this reverse representation should
// not matter.
static char bitmask(const size_t bit_index);


// ******************************* Functions ********************************

bitarray_t *bitarray_new(const size_t bit_sz) {
  // Allocate an underlying buffer of ceil(bit_sz/8) bytes.
  char *const buf = calloc(1, bit_sz / 8 + ((bit_sz % 8 == 0) ? 0 : 1));
  if (buf == NULL) {
    return NULL;
  }

  // Allocate space for the struct.
  bitarray_t *const bitarray = malloc(sizeof(struct bitarray));
  if (bitarray == NULL) {
    free(buf);
    return NULL;
  }

  bitarray->buf = buf;
  bitarray->bit_sz = bit_sz;
  return bitarray;
}

void bitarray_free(bitarray_t *const bitarray) {
  if (bitarray == NULL) {
    return;
  }
  free(bitarray->buf);
  bitarray->buf = NULL;
  free(bitarray);
}

size_t bitarray_get_bit_sz(const bitarray_t *const bitarray) {
  return bitarray->bit_sz;
}

inline bool bitarray_get(const bitarray_t *const bitarray, const size_t bit_index) {
  assert(bit_index < bitarray->bit_sz);

  // We're storing bits in packed form, 8 per byte.  So to get the nth
  // bit, we want to look at the (n mod 8)th bit of the (floor(n/8)th)
  // byte.
  //
  // In C, integer division is floored explicitly, so we can just do it to
  // get the byte; we then bitwise-and the byte with an appropriate mask
  // to produce either a zero byte (if the bit was 0) or a nonzero byte
  // (if it wasn't).  Finally, we convert that to a boolean.
  return (bitarray->buf[bit_index / 8] & bitmask(bit_index)) ?
             true : false;
}

inline void bitarray_set(bitarray_t *const bitarray,
                  const size_t bit_index,
                  const bool value) {
  assert(bit_index < bitarray->bit_sz);

  // We're storing bits in packed form, 8 per byte.  So to set the nth
  // bit, we want to set the (n mod 8)th bit of the (floor(n/8)th) byte.
  //
  // In C, integer division is floored explicitly, so we can just do it to
  // get the byte; we then bitwise-and the byte with an appropriate mask
  // to clear out the bit we're about to set.  We bitwise-or the result
  // with a byte that has either a 1 or a 0 in the correct place.
  bitarray->buf[bit_index / 8] =
      (bitarray->buf[bit_index / 8] & ~bitmask(bit_index)) |
           (value ? bitmask(bit_index) : 0);
}

// original given implementation
/*
void bitarray_rotate(bitarray_t *const bitarray, 
                      const size_t bit_offset,
                      const size_t bit_length,
                      const ssize_t bit_right_amount) {
   assert(bit_offset + bit_length <= bitarray->bit_sz);

   if (bit_length == 0) {
     return; 
   }

   // Convert a rotate left or right to a left rotate only, and eliminate
   // multiple full rotations.
   bitarray_rotate_left(bitarray, bit_offset, bit_length,
            modulo(-bit_right_amount, bit_length)); 
 } 
*/

static void bitarray_rotate_left(bitarray_t *const bitarray,
                                 const size_t bit_offset,
                                 const size_t bit_length,
                                 const size_t bit_left_amount) {
  for (size_t i = 0; i < bit_left_amount; i++) {
    bitarray_rotate_left_one(bitarray, bit_offset, bit_length);
  }
}

uint8_t head_masks[9] = { 0, 1, 3, 7, 15, 31, 63, 127, 255};
uint8_t tail_masks[9] = { 0, 128, 192, 224, 240, 248, 252, 254, 255};
uint8_t table[256] = { 0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254, 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241, 9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245, 13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255 };

// 8-bit version of the sixteen bitarray_reverse subroutine
// refer to bitarray_reverse for documentation
inline void bitarray_reverse_by_byte(bitarray_t *const bitarray,
                             const size_t bit_offset,
                             const size_t bit_length) {
  if (bit_length == 0) {
    return;
  }

  uint8_t* left_ptr_initial = (uint8_t*)bitarray->buf + (bit_offset/8);
  uint8_t* right_ptr_initial = (uint8_t*)bitarray->buf + (bit_offset + bit_length - 1) / 8;


  uint8_t head_length = bit_offset % 8;
  uint8_t tail_length = (8 - (bit_offset + bit_length) % 8) % 8;
  uint8_t head_bits = *left_ptr_initial & head_masks[head_length];
  uint8_t tail_bits = *right_ptr_initial & tail_masks[tail_length];

  uint8_t* left_ptr = left_ptr_initial;
  uint8_t* right_ptr = right_ptr_initial;
  uint8_t tmp;
  while (left_ptr < right_ptr) {
    tmp = *right_ptr;
    *right_ptr = table[*left_ptr];
    *left_ptr = table[tmp];
    right_ptr--;
    left_ptr++;
  }
  if (left_ptr == right_ptr) {
    *left_ptr = table[*left_ptr];
  }

  if (head_length > tail_length) {
    uint8_t shift_amt = head_length - tail_length;
    uint8_t back_shift_amt = 8 - shift_amt;
    uint8_t* right_ptr = right_ptr_initial;
    uint8_t* right_ptr_lagging = right_ptr_initial;
    while (right_ptr >= left_ptr_initial) {
      *right_ptr = *right_ptr << shift_amt;
      right_ptr--;
      uint8_t extra_bits = (*right_ptr & tail_masks[shift_amt]) >> back_shift_amt;
      *right_ptr_lagging |= extra_bits;
      right_ptr_lagging--;
    }
  } else if (tail_length > head_length) {
    uint8_t shift_amt = tail_length - head_length;
    uint8_t back_shift_amt = 8 - shift_amt;
    uint8_t* left_ptr = left_ptr_initial;
    uint8_t* left_ptr_lagging = left_ptr_initial;
    while (left_ptr <= right_ptr_initial) {
      *left_ptr = *left_ptr >> shift_amt;
      left_ptr++;
      uint8_t extra_bits = (*left_ptr & head_masks[shift_amt]) << back_shift_amt;
      *left_ptr_lagging |= extra_bits;
      left_ptr_lagging++;
    }
  }

  *left_ptr_initial &= tail_masks[8 - head_length];
  *left_ptr_initial |= head_bits;

  *right_ptr_initial &= head_masks[8 - tail_length];
  *right_ptr_initial |= tail_bits;
}

uint16_t sixteen_bit_head_masks[17] = { 0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535 };
uint16_t sixteen_bit_tail_masks[17] = { 0, 32768, 49152, 57344, 61440, 63488, 64512, 65024, 65280, 65408, 65472, 65504, 65520, 65528, 65532, 65534, 65535};

inline void bitarray_reverse(bitarray_t *const bitarray,
                             const size_t bit_offset,
                             const size_t bit_length) {
  if (bit_length == 0) {
    return;
  }

  uint16_t* left_ptr_initial = (uint16_t*)bitarray->buf + (bit_offset/16);
  uint16_t* right_ptr_initial = (uint16_t*)bitarray->buf + (bit_offset + bit_length - 1) / 16;

  // extra bits outside the subarray to be rotated, but within the 16-bit words that the subarray is contained in
  uint16_t head_length = bit_offset % 16;
  uint16_t tail_length = (16 - (bit_offset + bit_length) % 16) % 16;
  uint16_t head_bits = *left_ptr_initial & sixteen_bit_head_masks[head_length];
  uint16_t tail_bits = *right_ptr_initial & sixteen_bit_tail_masks[tail_length];

  uint16_t* left_ptr = left_ptr_initial;
  uint16_t* right_ptr = right_ptr_initial;
  uint16_t tmp;

  // reversing and swapping 16-bit words from outwards in
  while (left_ptr < right_ptr) {
    tmp = *right_ptr;
    *right_ptr = sixteen_bit_reversal_table[*left_ptr];
    *left_ptr = sixteen_bit_reversal_table[tmp];
    right_ptr--;
    left_ptr++;
  }
  if (left_ptr == right_ptr) {
    *left_ptr = sixteen_bit_reversal_table[*left_ptr];
  }

  // shifting final array to adjust for head and tail bits
  // Note: if head_length == tail_length, no shifting is necessary
  if (head_length > tail_length) {
    uint16_t shift_amt = head_length - tail_length;
    uint16_t back_shift_amt = 16 - shift_amt;
    uint16_t* right_ptr = right_ptr_initial;
    uint16_t* right_ptr_lagging = right_ptr_initial;
    uint16_t extra_bits_mask = sixteen_bit_tail_masks[shift_amt];
    while (right_ptr >= left_ptr_initial) {
      *right_ptr = *right_ptr << shift_amt;
      right_ptr--;
      uint16_t extra_bits = (*right_ptr & extra_bits_mask) >> back_shift_amt;
      *right_ptr_lagging |= extra_bits;
      right_ptr_lagging--;
    }

  } else if (tail_length > head_length) {
    uint16_t shift_amt = tail_length - head_length;
    uint16_t back_shift_amt = 16 - shift_amt;
    uint16_t* left_ptr = left_ptr_initial;
    uint16_t* left_ptr_lagging = left_ptr_initial;
    uint16_t extra_bits_mask = sixteen_bit_head_masks[shift_amt];
    while (left_ptr <= right_ptr_initial) {
      *left_ptr = *left_ptr >> shift_amt;
      left_ptr++;
      uint16_t extra_bits = (*left_ptr & extra_bits_mask) << back_shift_amt;
      *left_ptr_lagging |= extra_bits;
      left_ptr_lagging++;
    }
  }

  // gluing original head and tail bits back to the bit array
  *left_ptr_initial &= sixteen_bit_tail_masks[16 - head_length];
  *left_ptr_initial |= head_bits;

  *right_ptr_initial &= sixteen_bit_head_masks[16 - tail_length];
  *right_ptr_initial |= tail_bits;
}

// final implementation

void bitarray_rotate(bitarray_t *const bitarray,
                                 const size_t bit_offset,
                                 const size_t bit_length,
                                 const ssize_t bit_right_amount) {
  assert(bit_offset + bit_length <= bitarray->bit_sz);
  if (bit_length == 0) {
    return;
  }

  size_t length_b = modulo(bit_right_amount, bit_length);
  size_t length_a = bit_length - length_b;

  // call bitarray_reverse 3 times
  // first on a, then on b, then on the result
  if (bit_length >= 10000000) {
    bitarray_reverse(bitarray, bit_offset, length_a);
    bitarray_reverse(bitarray, bit_offset + length_a, length_b);
    bitarray_reverse(bitarray, bit_offset, bit_length);
  }
  else {
    bitarray_reverse_by_byte(bitarray, bit_offset, length_a);
    bitarray_reverse_by_byte(bitarray, bit_offset + length_a, length_b);
    bitarray_reverse_by_byte(bitarray, bit_offset, bit_length);

  }
}

static void bitarray_rotate_left_one(bitarray_t *const bitarray,
                                     const size_t bit_offset,
                                     const size_t bit_length) {
  // Grab the first bit in the range, shift everything left by one, and
  // then stick the first bit at the end.
  const bool first_bit = bitarray_get(bitarray, bit_offset);
  size_t i;
  for (i = bit_offset; i + 1 < bit_offset + bit_length; i++) {
    bitarray_set(bitarray, i, bitarray_get(bitarray, i + 1));
  }
  bitarray_set(bitarray, i, first_bit);
}

static size_t modulo(const ssize_t n, const size_t m) {
  const ssize_t signed_m = (ssize_t)m;
  assert(signed_m > 0);
  const ssize_t result = ((n % signed_m) + signed_m) % signed_m;
  assert(result >= 0);
  return (size_t)result;
}

static char bitmask(const size_t bit_index) {
  return 1 << (bit_index % 8);
}

