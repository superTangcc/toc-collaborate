/*
 * ============================================================================
 *
 *       Filename:  closure_caller.cpp
 *
 *    Description:  small toy benchmark to illustrate the dynamic loading
 *                  of pseudo-function object in C++
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

class DynamicLoader
{
public:
    DynamicLoader(const char * filename)
    {
        char cmd[200];
        char cpp_filename[100], so_filename[100];

        sprintf(cpp_filename, "%s.cpp", filename);
        sprintf(so_filename, "%s.so", filename);
        sprintf(cmd, "icpc -o %s -shared -nostartfiles -fPIC -O0 -g -std=c++0x %s\0", so_filename, cpp_filename); 

        printf("%s\n", cmd);
        int ret = system(cmd);
        if (ret == -1) {
            fprintf(stderr, "system() call failed!\n");
            exit(EXIT_FAILURE);
        }

        m_handle = dlopen(so_filename, RTLD_LAZY);
        if (!m_handle) {
            fprintf(stderr, "can't load library named %s\n", so_filename);
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

    void close(void) { dlclose(m_handle); }
private:
    void * m_handle;
    char * error;
};

int main(int argc, char * argv[]) {
    int a = 1, b = 2, z1 = 3, z2 = 4, z3 = 5;
    void *handle0, *handle1;
    char *error;

    if (argc == 3) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }

    DynamicLoader load0("./closure_callee0");
    DynamicLoader load1("./closure_callee1");
    DynamicLoader load2("./closure_callee2");
    DynamicLoader load3("./closure_callee3");

    std::function<int (int)> init_0 = load0.load<int (int)>("callee_init");
    std::function<int (int, int&, int*)> init_1 = load1.load<int (int, int&, int*)>("callee_init");
    std::function<int (int, int&, int*)> init_3 = load3.load<int (int, int&, int*)>("create_callee");
    std::function<int (void)> del_3 = load3.load<int (void)>("destroy_callee");
    std::function<int (int, int)> callee_0 = load0.load<int (int, int)>("callee");
    std::function<int (int, int)> callee_1 = load1.load<int (int, int)>("callee");
    std::function<int (int, int)> callee_3 = load3.load<int (int, int)>("lam");

    typedef std::function<int (int, int)> T_lam;

    std::function<int (T_lam, int, int)> callee_2 = load2.load<int (T_lam, int, int)>("callee");

    init_0(z1); 
    init_1(z1, z2, &z3);
    printf("<%s:%d> : z1 = %d, z2 = %d, z3 = %d\n", __FUNCTION__, __LINE__, z1, z2, z3);
    init_3(z1, z2, &z3);
    printf("<%s:%d> : z1 = %d, z2 = %d, z3 = %d\n", __FUNCTION__, __LINE__, z1, z2, z3);
    
    callee_0(a, b);
    callee_1(a, b);
    // callee_3(a, b);

    callee_2(callee_0, a, b);
    callee_2(callee_1, a, b);
    printf("<%s:%d> : z1 = %d, z2 = %d, z3 = %d\n", __FUNCTION__, __LINE__, z1, z2, z3);
    callee_2(callee_3, a, b);
    printf("<%s:%d> : z1 = %d, z2 = %d, z3 = %d\n", __FUNCTION__, __LINE__, z1, z2, z3);
    del_3();
    load0.close();
    load1.close();
    load2.close();
    load3.close();
    return 0;
}
