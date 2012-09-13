/*
 * ============================================================================
 *
 *       Filename:  closure_callee1.cpp
 *
 *    Description:  callee 3 for closure_caller 
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
#include <functional>

struct callee {
    public:
        callee(int _z1, int & _z2, int * _z3) : z1(_z1), z2(_z2), z3(_z3) {}
        int operator()(int x, int y) {
            printf("In %s:\n", __FUNCTION__);
            printf("%d + %d + %d + %d + %d = %d\n", x, y, z1, z2, (*z3), x+y+z1+z2+(*z3));
            z2 = 12; *z3 = 13;
            return 0;
        }
    private: 
        int z1, & z2, * z3;
};

template <int N_RANK>
struct Pochoir_Kernel {
    virtual int operator() (int x, int y) = 0;
};

template <typename F, int N_RANK>
struct Pochoir_Obase_Kernel : public Pochoir_Kernel<N_RANK> {
    F & kernel_;
    Pochoir_Obase_Kernel(F & _kernel) : kernel_(_kernel) {}
    int operator() (int x, int y) {
        printf("in Pochoir_Obase_Kernel: N_RANK = %d\n", N_RANK);
        return kernel_(x, y);
    }
};

static callee * _callee = NULL;
static Pochoir_Kernel<1> * _okernel = NULL; 

extern "C"
int create_callee(int z1, int & z2, int * z3) {
    _callee = new callee(z1, z2, z3);
    Pochoir_Obase_Kernel<decltype(*_callee), 1> * l_okernel = new Pochoir_Obase_Kernel<decltype(*_callee), 1>(*_callee);
    _okernel = l_okernel;
    return 0;
}

extern "C"
int destroy_callee(void) {
    delete _callee;
    delete _okernel;
    return 0;
}

extern "C"
int lam(int x, int y) {
    if (_callee != NULL) {
        printf("directly _callee:\n");
        (*_callee)(x, y);
    }
    if (_okernel != NULL) {
        printf("Pochoir_Obase_Kernel:\n");
        (*_okernel)(x, y);
    }
    return 0;
}

