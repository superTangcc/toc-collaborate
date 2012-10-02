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

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "bitarray.h"
#include "ktiming.h"




// Call TEST_PASS() from your test cases to mark a test as successful
//
#define TEST_PASS() TEST_PASS_WITH_NAME(__func__, __LINE__)

#define TEST_PASS_WITH_NAME(name, line) \
    fprintf(stderr, " --> %s at line %d: PASS\n", (name), (line))

// Call TEST_FAIL from your test cases to mark a test as failed. TEST_FAIL
// should print a meaningful message with the reason that the test failed.
//
// Calling it is just like calling printf().
#define TEST_FAIL(failure_msg, args...) \
    TEST_FAIL_WITH_NAME(__func__, __LINE__, failure_msg, ##args)

#define TEST_FAIL_WITH_NAME(name, line, failure_msg, args...) do { \
    fprintf(stderr, " --> %s at line %d: FAIL\n    Reason:", (name), (line)); \
    fprintf(stderr, (failure_msg), ## args); fprintf(stderr, "\n"); \
} while (0)



/* A test case is a function that takes no arguments and returns no arguments. */
typedef void (*test_case_t)(void);

/* Some global variables to make it easier to run individual tests. */
static bitarray_t *test_ba = NULL;
static bool test_verbose = true;

/* Print a string representation of a bitarray. */
static void bitarray_fprint(FILE *f, bitarray_t *ba) {
  size_t i;
  for (i = 0; i < bitarray_get_bit_sz(ba); i++)
    fprintf(f, "%d", bitarray_get(ba, i) ? 1 : 0);
}

/* Return a single random bit. */
static bool randbit(void) {
  return ((rand() % 2) == 0) ? false : true;
}

/* Create a new bitarray in test_ba of the specified size and fill it with random data based on the
seed given. For a given seed number, the pseudorandom data will be the same (at least on the same
glibc implementation). */
static void testutil_newrand(size_t bit_sz, unsigned int seed) {
  size_t i;
  if (test_ba != NULL)
    bitarray_free(test_ba);
  test_ba = bitarray_new(bit_sz);
  assert(test_ba != NULL);
  srand(seed);
  for (i = 0; i < bit_sz; i++)
    bitarray_set(test_ba, i, randbit());
  if (test_verbose) {
    bitarray_fprint(stdout, test_ba);
    fprintf(stdout, " newrand sz=%llu, seed=%u\n", (unsigned long long) bit_sz, seed);
  }
}

static bool boolfromchar(char c) {
  assert(c == '0' || c == '1');
  return c == '1';
}

/* Verify that the specified substring of the test_ba bitarray has the expected number of
flipcounts. Output FAIL or PASS as appropriate for the Python testing script to parse. */
static void testutil_expect_flips(size_t bit_off, size_t bit_len, size_t flipcount) {
  // We do not test this.
  TEST_PASS();
}

/* Verify that the test_ba bitarray has the expected content as well as the expected number
of flipcounts as returned by bitarray_count_flips(). Output FAIL or PASS as appropriate for
the Python testing script to parse. Use the testutil_expect() macro to run this function. */
static void testutil_expect_internal(const char *bitstr, size_t flipcount,
                                     const char* func_name, int line) {
  const char *bad = NULL;
  assert(test_ba != NULL);
  size_t sl = strlen(bitstr), i;
  if (sl != bitarray_get_bit_sz(test_ba))
    bad = "bitarray size";
  for (i = 0; i < sl; i++) {
    if (bitarray_get(test_ba, i) != boolfromchar(bitstr[i]))
      bad = "bitarray content";
  }
  if (bad != NULL) {
    bitarray_fprint(stdout, test_ba);
    fprintf(stdout, " expect bits=%s \n", bitstr);
    TEST_FAIL(func_name, "incorrect %s", bad);
  } else {
    TEST_PASS_WITH_NAME(func_name, line);
  }
}

/* Invoke the testutil_expect_internal() function with the right code line number specified. */
#define testutil_expect(bitstr, flipcount) \
    testutil_expect_internal((bitstr), (flipcount), __func__, __LINE__)

/* Create a new bitarray in test_ba by parsing a string of 0s and 1s, e.g. "0101011011". */
static void testutil_frmstr(const char *bitstr) {
  size_t sl = strlen(bitstr), i;
  if (test_ba != NULL)
    bitarray_free(test_ba);
  test_ba = bitarray_new(sl);
  assert(test_ba != NULL);
  size_t myflipcount = 0;
  bool curbit, prevbit = false;
  for (i = 0; i < sl; i++) {
    curbit = boolfromchar(bitstr[i]);
    if (i != 0 && curbit != prevbit)
      myflipcount++;
    bitarray_set(test_ba, i, curbit);
    prevbit = curbit;
  }
  bitarray_fprint(stdout, test_ba);
  if (test_verbose) {
    fprintf(stdout, " newstr lit=%s\n", bitstr);
    testutil_expect(bitstr, myflipcount);
  }
}

/* Peform a rotate operation on test_ba. */
static void testutil_rotate(size_t bit_off, size_t bit_len, ssize_t bit_right_amount) {
  assert(test_ba != NULL);
  bitarray_rotate(test_ba, bit_off, bit_len, bit_right_amount);
  if (test_verbose) {
    bitarray_fprint(stdout, test_ba);
    fprintf(stdout, " rotate off=%llu, len=%llu, amnt=%lld\n",
        (unsigned long long) bit_off, (unsigned long long) bit_len, (long long) bit_right_amount);
  }
}

/* A sample long-running set of rotation operations. */
double longrunning_rotation(void) {
  test_verbose = false;
  size_t bit_sz = 12 * 1024 * 8 + 471;
  testutil_newrand(bit_sz, 0);
  clockmark_t time1 = ktiming_getmark();
  testutil_rotate(0, bit_sz, -bit_sz / 4);
  testutil_rotate(0, bit_sz, bit_sz / 4);
  testutil_rotate(0, bit_sz, bit_sz / 2);
  clockmark_t time2 = ktiming_getmark();
  return ktiming_diff_usec(&time1, &time2) / 1000000000.0;
}

/* A sample long-running set of flip count operations. */
double longrunning_flipcount(void) {
  test_verbose = false;
  size_t bit_sz = 128 * 1024 * 1024 * 8 + 531;
  testutil_newrand(bit_sz, 0);
  clockmark_t time1 = ktiming_getmark();
  for (int i = 0; i < 20; i++)
    bitarray_count_flips(test_ba, 0, bit_sz);
  clockmark_t time2 = ktiming_getmark();
  return ktiming_diff_usec(&time1, &time2) / 1000000000.0;
}

/*------------ Created Methods go here ----------------*/

/*Gets the original array and the bit_rotated array, along with appropriate shift information, and compares to make sure the rotated bits correspond correctly.*/

void compareRotation(bitarray_t* or, bitarray_t* ro, size_t bit_off, size_t bit_len, ssize_t bit_right_amount){
  
  // assert(bit_off + bit_len <= or->bit_sz);
  int i;
  bit_right_amount = (bit_right_amount >= 0) ? bit_right_amount % bit_len: -bit_right_amount % bit_len;
  for(i = 0; i < bit_len; i++){
    if (i < bit_len - bit_right_amount){
      if(bitarray_get(or, bit_off + i) != bitarray_get(ro, bit_off + bit_right_amount + i)){
	TEST_FAIL("The original bitarray and the new bitarray do not correspond.");
	return;
      }
    }
    else{
      if(bitarray_get(or, bit_off + i) != bitarray_get(ro, bit_off + i + bit_right_amount - bit_len)){
	TEST_FAIL("The original bitarray and the new bitarray do not correspond.");
	return;
      }
    }
  }
  TEST_PASS();
}

void testCompareRotation(int size, size_t bit_off, size_t bit_len, ssize_t bit_right_amount){

  assert(bit_off + bit_len <= size);
  bitarray_t* ro = bitarray_new(size);
  bitarray_t* or = bitarray_new(size);
  int i;
  for(i = 0; i < size; i++){
    int rand = randbit();
    bitarray_set(or, i, rand);
    bitarray_set(ro, i, rand);
  }
  bitarray_rotate(ro, bit_off, bit_len, bit_right_amount);
  compareRotation(or, ro, bit_off, bit_len, bit_right_amount);

}


/* ----------- Actual test methods go here ----------- */

static void test_headerexamples(void) {
  /* Verify the examples given in bitarray.h. */
  testutil_frmstr("10010110");
  testutil_expect("10010110", 5);
  testutil_rotate(0, 8, -1);
  testutil_expect("00101101", 5);
  testutil_frmstr("10010110");
  testutil_rotate(2, 5, 2);
  testutil_expect("10110100", 5);
}

static void test_8bit(void) {
  testutil_frmstr("10000101");
  testutil_rotate(0, 8, 0);
  testutil_expect("10000101", 4);
  testutil_rotate(0, 8, 1);
  testutil_expect("11000010", 3);
  testutil_rotate(0, 8, -1);
  testutil_expect("10000101", 4);
  testutil_rotate(0, 8, -1);
  testutil_expect("00001011", 3);
  testutil_rotate(0, 8, -(3 + 8));
  testutil_expect("01011000", 4);
}

static void test_moreflips(void) {
  testutil_frmstr("110001010100101101011"); /* 21 bits */
  testutil_expect_flips(0, 21, 14);
  testutil_expect_flips(0, 20, 14);
  testutil_expect_flips(0, 19, 13);
  testutil_frmstr("100000000000000101011"); /* 21 bits */
  testutil_expect_flips(0, 21, 6);
  testutil_expect_flips(0, 20, 6);
  testutil_expect_flips(0, 19, 5);
}

static void test_reversal(void) {
	testutil_frmstr("10010110"); /* 21 bits */
	// bitarray_reverse(test_ba, 0, 20);
	// bitarray_fprint(stdout, test_ba);
	// fprintf(stdout, "\n");
	bitarray_rotate(test_ba, 0, 8, 0);
	bitarray_fprint(stdout, test_ba);
	fprintf(stdout, "\n");
}

/*------------------ Actual tests cases written -----------------*/

static void test_rotations(void){
  testCompareRotation(7431, 35, 359, 213); //Test a rotation
  testCompareRotation(730973, 3782, 38319, 3132); //Test a large rotation
  testCompareRotation(3178, 0, 3150, 3145); //Starts rotation at the beginning
  testCompareRotation(3150, 50, 1900, 2800); //Test looping rotation
  testCompareRotation(1, 0, 1, 1); //Test tiny rotation
  testCompareRotation(3150, 3100, 50, 200); //Test looped rotation at end edge.
  testCompareRotation(3150, 3100, 50, -175); //Test for negative right amountl
}

static void test_12bit(void) {
  testutil_frmstr("010000101000");
  testutil_rotate(0, 12, 1);
  testutil_expect("001000010100", 6);
  
  testutil_frmstr("010000101000");
  testutil_rotate(0, 12, -1);
  testutil_expect("100001010000", 5);
  testutil_rotate(0, 12, -1);
  testutil_expect("000010100001", 5);
  testutil_rotate(0, 12, -1);
  testutil_expect("000101000010", 6);
  
  testutil_frmstr("010000101000");
  testutil_rotate(0, 12, 0);
  testutil_expect("010000101000", 6);
  testutil_rotate(0, 12, 1);
  testutil_expect("001000010100", 6);
  testutil_rotate(0, 12, -1);
  testutil_expect("010000101000", 6);
  testutil_rotate(0, 12, -1);
  testutil_expect("100001010000", 5);
  testutil_rotate(0, 12, -(3 + 12));
  testutil_expect("001010000100", 6);
}

static void test_lotsmore(void) {
  testutil_frmstr("00101");
  testutil_rotate(0, 5, 0);
  testutil_expect("00101", 3);
  testutil_rotate(0, 5, 1);
  testutil_expect("10010", 3);
  testutil_rotate(0, 5, -1);
  testutil_expect("00101", 3);
  testutil_rotate(0, 5, -1);
  testutil_expect("01010", 4);
  testutil_rotate(0, 5, -(3 + 5));
  testutil_expect("10010", 3);
  
  testutil_frmstr("11000101");
  testutil_rotate(3, 5, 0);
  testutil_expect("11000101", 4);
  testutil_rotate(3, 5, 1);
  testutil_expect("11010010", 5);
  testutil_rotate(3, 5, -1);
  testutil_expect("11000101", 4);
  testutil_rotate(3, 5, -1);
  testutil_expect("11001010", 5);
  testutil_rotate(3, 5, -(3 + 5));
  testutil_expect("11010010", 5);
  
  testutil_frmstr("11000101000010");
  testutil_rotate(3, 5, 0);
  testutil_expect("11000101000010", 7);
  testutil_rotate(3, 5, 1);
  testutil_expect("11010010000010", 7);
  testutil_rotate(3, 5, -1);
  testutil_expect("11000101000010", 7);
  testutil_rotate(3, 5, -1);
  testutil_expect("11001010000010", 7);
  testutil_rotate(3, 5, -(3 + 5 * 99));
  testutil_expect("11010010000010", 7);
  
  testutil_frmstr("");
  testutil_rotate(0, 0, -5);
  testutil_expect("", 0);
  testutil_frmstr("1");
  testutil_rotate(0, 0, -5);
  testutil_expect("1", 0);
  testutil_rotate(0, 1, -5);
  testutil_expect("1", 0);
  
  testutil_frmstr("11000101000010010100100101000110010101101001010010000100010"); /* 59 bits */
  testutil_rotate(0, 0, -5);
  testutil_expect("11000101000010010100100101000110010101101001010010000100010", 37);
  testutil_rotate(0, 59, 15);
  testutil_expect("01001000010001011000101000010010100100101000110010101101001", 37);
  testutil_rotate(14, 27, 3);
  /*           ..............***************************..................*/
  testutil_expect("01001000010001101011000101000010010100100000110010101101001", 35);
  testutil_rotate(57, 2, -3);
  testutil_expect("01001000010001101011000101000010010100100000110010101101010", 36);

  testutil_frmstr("11000101000010010100100101000110010101101001010010000100010110011001"); /* 68 bits */
  testutil_rotate(0, 0, -5);
  testutil_expect("11000101000010010100100101000110010101101001010010000100010110011001", 42);
  testutil_rotate(0, 68, 15);
  testutil_expect("10001011001100111000101000010010100100101000110010101101001010010000", 41);
  testutil_rotate(14, 27, 3);
  /*           ..............***************************...........................*/
  testutil_expect("10001011001100101111000101000010010100100000110010101101001010010000", 39);
  testutil_rotate(57, 2, -3);
   testutil_expect("10001011001100101111000101000010010100100000110010101101010010010000", 39);
}

static void test_shifts(void){
	testutil_frmstr("11010100");
	lshift(test_ba, 0, 0, 3);
	bitarray_fprint(stdout, test_ba);
	fprintf(stdout, "\n");

	testutil_frmstr("110001010100101101011");
	lshift(test_ba, 0, 2, 3);
	bitarray_fprint(stdout, test_ba);
	fprintf(stdout, "\n");
}

/*---------------------------------------------------------------*/
test_case_t test_cases[] = {
  test_headerexamples,
  test_8bit,
  test_12bit,
  test_lotsmore,
  test_moreflips,
  test_reversal,
  test_rotations,
    test_shifts,

 NULL // This marks the end of all test cases. Don't change this!
};
