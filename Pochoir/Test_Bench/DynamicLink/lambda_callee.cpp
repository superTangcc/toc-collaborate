/*
 * ============================================================================
 *
 *       Filename:  lambda_callee.cpp
 *
 *    Description:  callee function for the lambda function in lambda.cpp
 *
 *        Version:  1.0
 *        Created:  12/01/2011 11:31:18 AM
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

typedef std::function<int (int, int)> T_lam;

extern "C"
int fp_lam(T_lam f, int a, int b) {
    printf("In %s: \n", __FUNCTION__);
    f(a, b);
    return 0;
}
