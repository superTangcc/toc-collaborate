/*
 * ============================================================================
 *
 *       Filename:  tb_ref.cpp
 *
 *    Description:  test bench for references and pointers
 *
 *        Version:  1.0
 *        Created:  12/05/2011 10:47:04 PM
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

int ref(int _z0, int & _z1) {
    int z0 = _z0, & z1 = _z1;

    z0 = 2; z1 = 3;

    return 0;
}

int main(void) {
    int z0 = 0, z1 = 1;
    
    ref(z0, z1);

    printf("<%s:%d> : z0 = %d, z1 = %d\n", __FUNCTION__, __LINE__, z0, z1);

    void * handle; 
    char * error;
    char cmd[200];
    const char * so_filename = "./refer.so";
    const char * cpp_filename = "refer.cpp";
    const char * functionName = "ref";
    typedef int (*T_func) (int, int &);

    sprintf(cmd, "icpc -o %s -shared -nostartfiles -fPIC -O0 -g -std=c++0x %s\0", so_filename, cpp_filename);

    printf("%s\n", cmd);
    int ret = system(cmd);
    if (ret == -1) {
        fprintf(stderr, "system() call failed!\n");
        exit(EXIT_FAILURE);
    }

    handle = dlopen(so_filename, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "can't load library named %s\n", so_filename);
    }
    dlerror();

    T_func func = (T_func) dlsym(handle, functionName);
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "can't find symbol named %s\n", functionName);
    }
    (*func)(z0, z1);
    printf("<%s:%d> : z0 = %d, z1 = %d\n", __FUNCTION__, __LINE__, z0, z1);
    dlclose(handle);

    return 0;
}
