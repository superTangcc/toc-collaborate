/*
 * ============================================================================
 *
 *       Filename:  callee.cpp
 *
 *    Description:  test bench for dynamic linking library of POSIX.
 *                  This is the callee program
 *
 *        Version:  1.0
 *        Created:  11/27/2011 07:16:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <cstdio>
#include <cstdlib>

extern int x;

extern "C" int foo(int y) {
    printf("foo : %d\n", y);
    printf("x = %d\n", x);
    return 0;
}

extern "C" int bar(int z, int y) { 
    printf("%d + %d = %d\n", z, y, z+y);
    return 0;
}


