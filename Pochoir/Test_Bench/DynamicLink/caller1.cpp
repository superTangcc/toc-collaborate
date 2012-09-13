/*
 * ============================================================================
 *
 *       Filename:  caller1.cpp
 *
 *    Description:  test bench for dynamic loading library
 *                  caller function 1
 *
 *        Version:  1.0
 *        Created:  11/28/2011 02:32:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <dlfcn.h>

class DynamicLoader
{
public:
    DynamicLoader(const char * filename)
    {
        m_handle = dlopen(filename, RTLD_LAZY);
        if (!m_handle) {
            fprintf(stderr, "can't load library named %s\n", filename);
        }
        dlerror();
    }

    template<class T>
    std::function<T> load(const char * functionName)
    {
        void* result = dlsym(m_handle, functionName);
        if ((error = dlerror()) != NULL) {
            fprintf(stderr, "can't find symbol named %s\n", functionName);
        }
        return reinterpret_cast<T*>(result);
    }

private:
    void * m_handle;
    char * error;
};

template <typename T>
std::function<T> dloader(void * handle, const char * func_name) {
    void * result = dlsym(handle, func_name);
    char * error;

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "can't find symbol named %s\n", func_name);
    }
    return reinterpret_cast<T*>(result);
};

int x = 0;

int main(int argc, char * argv[])
{
    typedef std::function<int (int, int)> (T_lambda);
    typedef std::function<double (double)> (T_trifunc);

    void * handle;
    char * error;

    fprintf(stderr, "icpc -o callee.so -shared -nostartfiles -fPIC -O3 -std=c++0x callee.cpp\n");
    int ret = system("icpc -o callee.so -shared -nostartfiles -fPIC -O3 -std=c++0x callee.cpp");
    if (ret == -1) {
        fprintf(stderr, "system() call failed!\n");
        exit(EXIT_FAILURE);
    }

    DynamicLoader tri_loader("libm.so");
    T_trifunc tri_func = tri_loader.load<double (double)>("cos");
    printf("cos(%f) = %f\n", 2.0, tri_func(2.0));

    handle = dlopen("./callee.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror(); /* clear any existing error */

    T_lambda lam0 = dloader<int (int, int)>(handle, "bar");
    std::cout << "bar(2, 3): " << lam0(2,3) << std::endl;
    dlclose(handle);

//    DynamicLoader loader("/home/yuantang/Git/Pochoir/DynamicLink/callee.so");
    DynamicLoader loader("./callee.so");
    T_lambda lam1 = loader.load<int (int, int)>("bar");
    std::cout << "bar(2, 3): " << lam1(2,3) << std::endl;
    return 0;
}


