/*
 * ============================================================================
 *
 *       Filename:  lambda.cpp
 *
 *    Description:  small toy benchmark to illustrate the usage of lambda
 *                  function in C++
 *
 *        Version:  1.0
 *        Created:  12/01/2011 11:11:54 AM
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
#include <dlfcn.h>
#include <functional>

typedef std::function<int (int, int)> T_lam;

template <typename F>
int fp_calc(F f, int a, int b) {
    printf("In %s: \n", __FUNCTION__);
    f(a, b);
    return 0;
};

int main(int argc, char * argv[]) {
    int a = 1, b = 2, z = 3;
    void * handle;
    char * error;

    typedef int (*T_func) (T_lam, int, int);

    if (argc == 3) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    auto calc = [&] (int x, int y) -> int { 
        printf("%d + %d + %d = %d\n", x, y, z, x+y+z);
        return 0;
    };
    printf("In %s: \n", __FUNCTION__);
    calc(a, b);
    fp_calc(calc, a+1, b+1);

    int ret = system("icpc -o lambda_callee.so -shared -nostartfiles -fPIC -O3 -std=c++0x lambda_callee.cpp");
    if (ret == -1) {
        fprintf(stderr, "system() call failed!\n");
        exit(EXIT_FAILURE);
    }

    handle = dlopen("./lambda_callee.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror(); /* clear any existing error */

    T_func func = (T_func) dlsym(handle, "fp_lam");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    ret = (*func)(calc, a+2, b+2);
    dlclose(handle);

    return 0;
}
