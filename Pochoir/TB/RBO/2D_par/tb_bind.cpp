/*
 * ============================================================================
 *
 *       Filename:  tb_bind.cpp
 *
 *    Description:  testbench for the std::bind() in icpc
 *
 *        Version:  1.0
 *        Created:  06/29/2012 02:09:47 PM
 *       Revision:  none
 *       Compiler:  icpc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <iostream>
#include <functional>
using namespace std;
using namespace placeholders;

typedef unsigned long T_Data;
typedef function<T_Data (T_Data)> T_Curry_Func;
#define THRES 2

static inline T_Data log2_helper (T_Data a) {
    return 63-__builtin_clzl(a);
}
static inline T_Data star(T_Curry_Func f, T_Data N) {
    T_Data n = N, res = 0;
    while (n > THRES) {
        n = f(n);
        ++res;
    }
    return res;
}

int main(void) {
    T_Data val = bind(star, log2_helper, _1)(1ul << 63);
    cout << "val = " << val << endl;
    return 0;
}
