/*
 * ============================================================================
 *
 *       Filename:  closure_callee0.cpp
 *
 *    Description:  callee 0 for closure_caller
 *
 *        Version:  1.0
 *        Created:  12/04/2011 10:41:04 PM
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

/* mark it 'static', so is local to this file  */
static int z1;

extern "C"
int callee_init(int _z1) {
    z1 = _z1;
    return 0;
}

extern "C"
int callee(int x, int y) {
    printf("In %s:\n", __FUNCTION__);
    printf("%d + %d + %d = %d\n", x, y, z1, x+y+z1);
    return 0;
}

