/*
 * ============================================================================
 *
 *       Filename:  closure_callee2.cpp
 *
 *    Description:  callee 2 for closure_caller
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
#include <functional>

extern "C"
int callee(std::function<int (int, int)> f, int x, int y) {
    printf("In %s:\n", __FUNCTION__);
    int ret = f(x, y);
    return ret;
}
