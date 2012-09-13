/*
 * ============================================================================
 *
 *       Filename:  tb_alpha.cpp
 *
 *    Description:  test bench for the alpha function implemented via
 *                  std::bind
 *
 *        Version:  1.0
 *        Created:  06/18/2012 07:24:11 PM
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
#include <cassert>
#include <cstddef>
#include <cstring>
#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <exception>
#include <functional>
#include "lib_common.hpp"

using namespace std;
#ifndef BOOST
using namespace placeholders;
#endif

int multiply (int x, int y) {
    printf("x = %d, y = %d\n", x, y);
    return (x * y);
}
int main(int argc, char ** argv) {
    if (argc < 2) {
        printf("argc < 2, quit!\n");
        exit(1);
    }

    size_t N = atoi(argv[1]);
    cout << "alpha(" << N << ") = " << alpha(N) << endl;
    cout << alpha(2) << endl;
    cout << alpha(10) << endl;
    cout << alpha(100000) << endl;
    cout << alpha(1000000000000) << endl;
    cout << alpha(100000000000000000) << endl;
    cout << "alpha(1048576) = " << alpha(1048576) << endl;
    cout << "log^*(1048576) = " << bind(star, log2_helper, _1)(1048576) << endl;
#ifdef BOOST
    auto f = boost::bind(multiply, 5, _1);
#else
    auto f = bind(multiply, 5, _1);
#endif
    cout << "5 * " << N << " = " << f(N) << endl;
}

