/*======================================================================
1. Code for incrementing a number x interleaved with other bits The
   variable mask tells which bits of word v belong to x.  For example,
   if v is a 32-bit Morton number, the bits containing x are
   0xAAAAAAAA, and the bits of y are the complement 0x5555555.
----------------------------------------------------------------------*/

// Increment the number x represented by the masked bits of v without
// disturbing the other bits.

r = v ^ ((v ^ ((v | ~mask) + 1)) & mask);


/*======================================================================
2. Code for computing a + b mod n when 0 <= a < n and 0 <= b < n.
   This problem often comes up in periodic stencil computations, where
   the array wraps around in 1 or more dimensions.  In a stencil, each
   point is updated by its nearest neighbors mod n, and you'd like to
   avoid a divide or branch to compute the modulo operation.
----------------------------------------------------------------------*/

z = a + b;
r = z - (n & -(z >= n));

/*======================================================================
3. Code for computing a - b mod n when 0 <= a < n and 0 <= b < n.
----------------------------------------------------------------------*/

z = a - b;
r =  z + (n & -(z < 0));

/*======================================================================
4. Code for population count with automatic generation of masks rather
than table lookup.  The shift amounts can themselves be generated
automatically.
----------------------------------------------------------------------*/

// Create masks
B4 = ~((-1) << 16);
B3 = B4 ^ (B4 << 8);
B2 = B3 ^ (B3 << 4);
B1 = B2 ^ (B2 << 2);
B0 = B1 ^ (B1 << 1);

// Pop count
x = ((x >>  1) & B0) + (x & B0);
x = ((x >>  2) & B1) + (x & B1);
x = ((x >>  4) + x) & B2;
x = ((x >>  8) + x) & B3;
x = ((x >> 16) + x) & B4;


/*======================================================================
5. Convert a binary number to binary reflecting Gray code.  
----------------------------------------------------------------------*/

r = x ^ (x >> 1);

/*======================================================================
6. Convert binary reflecting Gray code to binary.  Note that the
low-order bit of the Gray code is the parity of the input.
----------------------------------------------------------------------*/

r = x ^ (x >>  1);
r = r ^ (r >>  2);
r = r ^ (r >>  4);
r = r ^ (r >>  8);
r = r ^ (r >> 16);

