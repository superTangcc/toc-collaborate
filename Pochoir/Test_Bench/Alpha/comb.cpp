/*
 * ============================================================================
 *
 *       Filename:  comb.cpp
 *
 *    Description:  test bench for combinatorial questions of throwing n identical
 *                  balls into m different (labeled) bins
 *                  ?=
 *                  choose n items from a set of m elements with replacement?
 *
 *        Version:  1.0
 *        Created:  05/09/2012 10:04:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <cmath>

/* return the factorial of n: n! */
unsigned long fac(unsigned long n) {
    unsigned long tmp = 1;
    for (int i = n ; i >= 1; --i)
        tmp *= i;
    return tmp;
}

unsigned long yuan_rec(unsigned long m, unsigned long n) {
    if (m == 1) {
        return 1;
    } else if (m == 2) {
        return (n+1);
    } else {
        unsigned long tmp = 0, res = 0;
        for (int i = n; i >= 0; --i) {
            tmp = yuan_rec(m-1, i);
            res += tmp;
        }
        return res;
    }
}

unsigned long rezaul_rec(unsigned long m, unsigned long n) {
    /* choose(m+n-1, n) */
    unsigned long tmp = 1;
    unsigned long max = ((m-1)>n ? (m-1) : n);
    unsigned long min = ((m-1)>n ? n : (m-1));
    for (int i = m+n-1; i > max; --i)
        tmp *= i;
    return (tmp/fac(min));
}

int main(int argc, char * argv[]) {
    if (argc < 3) {
        printf("argc < 3: quit! \n");
        exit(1);
    }
    unsigned long m = (unsigned long) atoi(argv[1]);
    unsigned long n = (unsigned long) atoi(argv[2]);
    printf("m = %ld, n = %ld\n", m, n);
    printf("fac(m) = %ld, fac(n) = %ld\n", fac(m), fac(n));
    printf("yuan_rec(%ld, %ld) = %ld, rezaul_rec(%ld, %ld) = %ld\n",
            m, n, yuan_rec(m, n), m, n, rezaul_rec(m, n));
    return 0;
}
