/*
 * ============================================================================
 *
 *       Filename:  tb_string.cpp
 *
 *    Description:  test bench for getting the string length
 *
 *        Version:  1.0
 *        Created:  01/30/2012 10:08:27 AM
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
#include <cstring>

int psize(const char * fname) {
    printf("<%s:%d> sizeof(fname) = %d, %d\n", __FUNCTION__, __LINE__, (int)sizeof(*fname), (int)strlen(fname));
    char * fname_ = new char[strlen(fname)+10];
    memcpy(fname_, fname, strlen(fname));
    sprintf(fname_, "%s_%d.cpp", fname_, 0);
    printf("<%s:%d> fname_ = %s (%d)\n", __FUNCTION__, __LINE__, fname_, (int)strlen(fname_));
    return strlen(fname);
}

int main(void) {
    const char * fname = "I love superTang";
    printf("<%s:%d> sizeof(fname) = %d, %d\n", __FUNCTION__, __LINE__, (int)sizeof(*fname), (int)strlen(fname));
    psize(fname);
    return 0;
}
