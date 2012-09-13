/*
 * ============================================================================
 *
 *       Filename:  tb_thread.cpp
 *
 *    Description:  test bench of c++11's std::thread
 *
 *        Version:  1.0
 *        Created:  02/12/2012 11:29:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

/* it seems in g++ 4.4.x, the thread facility doesn't work, will have segmentation fault
 * for icpc compatible with g++ 4.4.x, it doesn't even compile
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>

void fib(int n, int * res) {
#if 0
    if (n == 0) {
        res = 0;
        return;
    } else if (n == 1) {
        res = 1;
        return;
    } else {
        int res1, res2;
        std::thread t1{std::bind(fib, (n-1), res1)};
        std::thread t2{std::bind(fib, (n-2), res2)};
        t1.join();
        t2.join();
        res = res1 + res2;
        return;
    }
#else
    printf("in fib, n = %d\n", n);
    return;
#endif
}
int main(void) {
    int n = 10, res;
    std::thread t{std::bind(fib, n, &res)};

    t.join();
    printf("fib(%d) = %d\n", n, res);
    return 0;
}
