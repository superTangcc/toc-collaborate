/*
 * ============================================================================
 *
 *       Filename:  tb_move.cpp
 *
 *    Description:  test bench for move semantics in C++11
 *
 *        Version:  1.0
 *        Created:  02/05/2012 10:32:23 AM
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
#include <iostream>

template <typename T> 
void lswap (T & a, T & b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template <typename T> 
void rswap (T && a, T && b) {
    T tmp = a;
    a = b;
    b = tmp;
}

int main(void) {
    int a = 1, b = 2;
    int c = 3, d = 4;
    int && e = 5;
    lswap(a, b);
    rswap(c, d);
    // rswap(a, b);
    printf("a = %d, b = %d\n", a, b);
    printf("c = %d, d = %d\n", c, d);
    printf("e = %d\n", e);
    return 0;
}
