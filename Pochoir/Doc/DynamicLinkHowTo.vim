# courtesy of Jason Ansel @ CSAIL (jansel@csail.mit.edu)

in callee.cpp

extern "C" /* extern "C" is to deal with the name mangling issue in C++ */ 

foo(int y) {...};

in caller.cpp

typedef int (*func_ptr)(int);
system ("gcc -shared ... -o callee.so");

handle = dlopen("callee.so");

func = (func_ptr) dlsym(handle, "foo");

ret = (*func)(y);

dlclose(handle);

The Caller file will be compiled as follows:

gcc -rdynamic -o caller caller.c -ldl

The Callee file will be compiled as follows:

gcc -shared -nostartfiles -fPIC -o callee callee.c

/* reference 'man dlopen' */
===========================================================================

We can call 'mprotect' to set protection on a region of memory,
such as changing a data region to executable.

POSIX says that the behavior of mprotect() is unspecified if it
is applied to a region of memory that was not obtained via mmap(2)

===========================================================================

Two ways to extract symbols from dynamically loaded library:

1) 
typedef void (*sdl_init_function_type)(void);
sdl_init_function_type init_func = (sdl_init_function_type)initializer;

The above snippet will give a warning on some compilers: warning:
dereferencing type-punned pointer will break strict-aliasing
rules. Another workaround is:

2)
typedef void (*sdl_init_function_type)(void);
union { sdl_init_function_type func; void * obj; } alias;
alias.obj = initializer;
sdl_init_function_type init_func = alias.func;

which disables the warning even if strict aliasing is in effect. This
makes use of the fact that reading from a different union member than
the one most recently written to (called "type punning") is common,
and explicitly allowed even if strict aliasing is in force, provided the
memory is accessed through the union type directly. However, this is
not strictly the case here, since the function pointer is copied to be
used outside the union.

==========================================================================
Both Windows and UNIX implementations of dynamic loading allow programmers
to extract symbols from the currently executing process. In both of these
APIs, the currently executing process can be "loaded" such that the result
can be used in the same manner as the result from dynamically loading a
library with LoadLibrary or dlopen. UNIX-like operating systems (Linux,
*BSD, Mac OS X, Solaris, etc.)

void* this_process = dlopen(NULL,0);

===========================================================================

There are two different forms of the extern "C" declaration: extern "C"
as used above, and extern "C" { … } with the declarations between the
braces. The first (inline) form is a declaration with extern linkage and
with C language linkage; the second only affects language linkage. The
following two declarations are thus equivalent:

extern "C" int foo;
extern "C" void bar();

and

extern "C" {
     extern int foo;
     extern void bar();
 }

As there is no difference between an extern and a non-extern function
declaration, this is no problem as long as you are not declaring any
variables. If you declare variables, keep in mind that

extern "C" int foo;

and

extern "C" {
    int foo;
}

are not the same thing.

===========================================================================
Loading Classes

Loading classes is a bit more difficult because we need an instance of
a class, not just a pointer to a function.

We cannot create the instance of the class using new because the class
is not defined in the executable, and because (under some circumstances)
we don't even know its name.

The solution is achieved through polymorphism. We define a base,
interface class with virtual members in the executable, and a derived,
implementation class in the module. Generally the interface class is
abstract (a class is abstract if it has pure virtual functions).

As dynamic loading of classes is generally used for plug-ins — which
must expose a clearly defined interface — we would have had to define
an interface and derived implementation classes anyway.

Next, while still in the module, we define two additional helper
functions, known as class factory functions. One of these functions
creates an instance of the class and returns a pointer to it. The other
function takes a pointer to a class created by the factory and destroys
it. These two functions are qualified as extern "C".

To use the class from the module, load the two factory functions using
dlsym just as we loaded the the hello function; then, we can create and
destroy as many instances as we wish.

Example 2. Loading a Class

Here we use a generic polygon class as interface and the derived class
triangle as implementation.

main.cpp:

#include "polygon.hpp" 
#include <iostream> 
#include <dlfcn.h>

int main() {
    using std::cout; using std::cerr;

    // load the triangle library 
    void* triangle = dlopen("./triangle.so", RTLD_LAZY); 
    if (!triangle) {
        cerr << "Cannot load library: " << dlerror() << '\n'; return 1;
    }

    // load the symbols create_t* create_triangle = (create_t*)
    dlsym(triangle, "create"); 
    destroy_t* destroy_triangle = (destroy_t*) dlsym(triangle, "destroy"); 
    
    if (!create_triangle || !destroy_triangle) {
        cerr << "Cannot load symbols: " << dlerror() << '\n'; return 1;
    }

    // create an instance of the class 
    polygon* poly = create_triangle();

    // use the class 
    poly->set_side_length(7);
    cout << "The area is: " << poly->area() << '\n';

    // destroy the class 
    destroy_triangle(poly);

    // unload the triangle library 
    dlclose(triangle);
}

polygon.hpp:

#ifndef POLYGON_HPP #define POLYGON_HPP

class polygon { protected:
    double side_length_;

public:
    polygon()
        : side_length_(0) {}

    void set_side_length(double side_length) {
        side_length_ = side_length;
    }

    virtual double area() const = 0;
};

// the types of the class factories typedef polygon* create_t(); typedef
void destroy_t(polygon*);

#endif

triangle.cpp:

#include "polygon.hpp" 
#include <cmath>

class triangle : public polygon { 
public:
    virtual double area() const {
        return side_length_ * side_length_ * sqrt(3) / 2;
    }
};

// the class factories
extern "C" 
polygon* create() {
    return new triangle;
}

extern "C" 
void destroy(polygon* p) {
    delete p;
}

There are a few things to note when loading classes:

    You must provide both a creation and a destruction function; you must
    not destroy the instances using delete from inside the executable,
    but always pass it back to the module. This is due to the fact that
    in C++ the operators new and delete may be overloaded; this would
    cause a non-matching new and delete to be called, which could cause
    anything from nothing to memory leaks and segmentation faults. The
    same is true if different standard libraries are used to link the
    module and the executable.

    The destructor of the interface class should be virtual in any
    case. There might be very rare cases where that would not be
    necessary, but it is not worth the risk, because the additional
    overhead can generally be ignored.

    If your base class needs no destructor, define an empty (and virtual)
    one anyway; otherwise you will have problems sooner or later;
    I can guarantee you that. You can read more about this problem in
    the comp.lang.c++ FAQ at http://www.parashift.com/c++-faq-lite/,
    in section 20.


===========================================================================
V8 : an infrastructure underlying Chrome to JIT compile java scripts.




