/*
 * ============================================================================
 *
 *       Filename:  closure_callee1.cpp
 *
 *    Description:  callee 1 for closure_caller 
 *
 *        Version:  1.0
 *        Created:  12/04/2011 10:45:44 PM
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
static int stub = 1;
static int z1, &z2 = stub, *z3;

extern "C"
int callee_init(int _z1, int & _z2, int * _z3) {
    z1 = _z1; 
    z2 = _z2;
    z3 = _z3;
    z2 = 9;
    *z3 = 13;
    return 0;
}

extern "C"
int callee(int x, int y) {
    printf("In %s:\n", __FUNCTION__);
    printf("%d + %d + %d + %d = %d\n", x, y, z1, z2, x+y+z1+z2);
    return 0;
}


