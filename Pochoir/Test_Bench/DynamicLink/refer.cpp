/*
 * ============================================================================
 *
 *       Filename:  refer.cpp
 *
 *    Description:  callee of tb_ref.cpp
 *
 *        Version:  1.0
 *        Created:  12/06/2011 06:28:50 AM
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

static int stub;
static int & _z1_;

extern "C"
int ref(int _z0, int & _z1) {
    int z0 = _z0, & z1 = _z1;

    z0 = 12; z1 = 13;

    _z1_ = _z1;
    _z1_ = 23;
    printf("<%s:%d> : _z1_ = %d, stub = %d\n", __FUNCTION__, __LINE__, _z1_, stub);

    return 0;
}

