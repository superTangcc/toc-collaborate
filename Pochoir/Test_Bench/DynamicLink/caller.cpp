/*
 * ============================================================================
 *
 *       Filename:  caller.cpp
 *
 *    Description:  test bench for dynamic linking library of POSIX. 
 *                  This is the caller program
 *
 *        Version:  1.0
 *        Created:  11/27/2011 07:14:41 PM
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

int x = 10;

int main (int argc, char * argv[]) {
    void *handle;
    typedef int (*func_ptr)(int);
    // defined as std::function<int (int, int)> doesn't work!! will cause
    // a segmentation fault!! why??
    typedef std::function<int (int, int)> T_lambda;
    typedef int (*T_lam)(int, int);
    char * error;
    int y = 2, ret;

    if (argc >= 2) {
        y = atoi(argv[1]);
    }

    fprintf(stderr, "icpc -o callee.so -shared -nostartfiles -fPIC -O3 -std=c++0x callee.cpp\n");
    ret = system("icpc -o callee.so -shared -nostartfiles -fPIC -O3 -std=c++0x callee.cpp");

    if (ret == -1) {
        fprintf(stderr, "system() call failed!\n");
        exit(EXIT_FAILURE);
    }
    handle = dlopen("./callee.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror(); /* clear any existing error */

    T_lambda lam = T_lambda (dlsym(handle, "bar"));
    // T_lam lam = reinterpret_cast<T_lam>(dlsym(handle, "bar"));
    // *reinterpret_cast<T_lambda*>(&lam) = dlsym(handle, "bar");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    ret = (lam)(2, 3);

    func_ptr func = (func_ptr) dlsym(handle, "foo");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    ret = (*func)(y);

    dlclose(handle);

    handle = dlopen("libm.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();

    double (*cosine)(double);
    double (*sinine)(double);
    *(void **) (&cosine) = dlsym(handle, "cos");
    
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    printf("%f\n", (*cosine)(2.0));

    *(void **) (&sinine) = dlsym(handle, "sin");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    printf("%f\n", (*sinine)(2.0));

    dlclose(handle);


    return 0;
}
