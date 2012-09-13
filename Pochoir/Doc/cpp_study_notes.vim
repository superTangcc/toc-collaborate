# C++ study notes from "The C++ Programming Language" 
        -- Special Edition, Bjarne Stroustrup

Exception Handling:

In C++, it's the caller (who invoke the operation), rather than the
callee (who find the error while trying to perform the operation) to do
the exception handling. The 'throw' acts as a multi-level return. The
implementation will unwind the function call stack as needed to get back
to the context of the caller.

A simple stack example:

namespace Stack {
    void push(char);
    char pop();
    class Overflow {}; // type representing overflow exceptions
}

void Stack::push(char c) {
    if (top == max_size) throw Overflow();
    // ...
}

void f() {
    // The caller
    //..
    try { //exception here are handled by the handler defined below
        while (true) Stack::push('c');
    } catch (Stack::Overflow) {
        //oops: stack overflow: take appropriate action
    }
}

A simple declaration of 

struct Rep;

says that Rep is the name of a type, but it leaves the type to be defined
later. Later on, we could even use this to-define type in typedef,

typedef Rep & stack;

<vector> in standard library doesn't support mathematical vector
operations. Adding such operations to vector would be easy, but its
generality and flexibility precludes optimizations that are often
considered essential for serious numeric work. Consequently, the standard
library provides a vector, called valarray, that is less general and
more amenable to optimization for ``numerical computation''.

Basic Types and Declarations:

Wide character literals are of the form L'ab', where the number of
characters between the quotes and their meanings is implementation-defined
to match the wchar_t type. A wide character literal has type ``wchar_t''.

The suffix U can be used to write explicitly unsigned (integer) literals.
Similarly, the suffix L can be used to write explicitly long literals.

Floating-Point Types:

float (single-precision), double (double-precision), and long double
(extended-precision).

By default, a floating-point literal is of type double. If you want a
floating-point literal of type float, you can define one using the suffix
``f'' or ``F''. If you want a floating-point literal of type long double, 
you can define one using the suffix l or L.

By ``new'' operator, when it exhausts memory, it will throw a bad_alloc
exception. e.g.

try {
    for (;;) new char[10000000];
} catch (bad_alloc) {
    cerr << "Memory exhausted!";
}

We can specify what ``new'' should do upon memory exhaustion. When
``new'' fails, it first calls a function specified by a call to
``set_new_handler()'' declared in <new>, if any. e.g.

void out_of_mem() {
    cerr << "operator new failed: out of memory!\n";
    throw bad_alloc();
}

int main(void) {
    set_new_handler(out_of_mem); // make out_of_mem the new_handler
    for (;;) new char[100000000];
    cout << "done!\n";
}

The static_cast operator converts between related types such as one
pointer type to another in the same class hierarchy, an enumeration
to an integral type, or a floating-point type to an integral type. The
reinterpret_cast handles conversions between unrelated types such as an
integer to a pointer or a pointer to an unrelated pointer type. e.g.

int * p = static_cast<int*>(malloc(100)); // new allocation used as ints
IO_device * dl = reinterpret_cast<IO_device*>(0xff00); // device at 0xff00

A form of run-time checked conversion, dynamic_cast, and a cast for
removing const qualifiers, const_cast, are also provided.

The T(e) construct is sometimes referred to as a function-style cast. For
a built-in type T, T(e) is equivalent to static_cast<T>(e). Pointer conversions
cannot be expressed directly using the T(e) notation. For example, char*(2)
is a syntax error. The constructor notation T() is used to express the default
value of type T.

A static variable provides a function with ``a memory'' without introducing
a global variable that might be accessed and corrupted by other functions.

Using the same name for operations on different types is called ``overloading''
Return types are not considered in overload resolution. The reason is to keep
resolution for an individual operator /or function call context-independent.
Functions declared in different non-namespace scopes do not overload.

Dereferencing of a pointer to function using * is optional. Similarly, using &
to get the address of a function is optional. e.g.

void (*f1) (string) = &error; //ok
void (*f2) (string) = error; /also ok; same meaning as &error

void g() {
    f1("Vasa"); //ok
    (*f1)("Mary"); // also ok;
}

It is often convenient to define a name for a pointer-to-function type to avoid
using the some what nonobvious declaration syntax all the time. e.g.

typedef void (*SIG_TYP)(int); // from <signal.h>
typedef void (*SIG_ARG_TYP)(int); 
SIG_TYP signal(int, SIG_ARG_TYP);

An array of pointers to functions is often useful:

typedef void (*PF)();

PF edit_ops[] = { &cut, &paste, &copy, &search }
PF * button = edit_ops;
button[2](); // call button's 3rd function

Exceptions in C++ is a struct/class:

struct Range_error {
    int i;
    Range_error(int ii) { i = ii; }
};

char to_char(int i) {
    if (i < numeric_limits<char>::min() || numeric_limits<char>::max() < i)
        throw Range_error(i);
    return i;
}

void g(int i) {
    try {
        char c = to_char(i);
    } catch (Range_error x) {
        cerr << oops: to_char(" << x.i << ")\n";
    }
}

linkage block: adding extern "C" to a lot of declaration in a group:

#ifdef __cplusplus
extern "C" {
#endif
    char * strcpy(...);
    int strcmp(...);
    int strlen(...);
    ...
#ifdef __cplusplus
}
#endif

The predefined macro __cplusplus is used to ensure that the C++ constructs
are edited out when the file is used as a C header.

A variable that is part of a class, yet is not part of an object of that 
class, is called a static member. There is exactly one copy of a static member
instead of one copy per object, as for ordinary non-static members. Similarly,
a function that needs access to members of a class, yet doesn't need to be 
invoked for a particular object, is called a static member function.

Class X's copy constructor: X::X(const X &). The const after the (empty)
argument list in the funciton declarations indicates that these functions
don't modify the state of an object.

The storage specifier ``mutable'' specifies that a member should be stored
in a way that allows updating -- even when it is a member of a const object.

class Date {
    mutable bool cache_valid;
    mutable string cache;
    void compute_cache_value() const; // fill (mutable) cache.
};

Usually we put the helper functions with associated class in the same header
file, the same name space. e.g.

namespace Chrono {
    class Date { /* ... */ }
    int diff (Date a, Date b);
    bool leapyear (int y);
    Date next_weekday(Date d);
    ...
}

It's also possible to initialize a static integral constant member by adding
a constant-expression initializer to its member declaration. e.g.

class Curious {
    static const int c1 = 7;
    static int c2 = 11;
    ...
}

If an object of a class can be constructed without supplying an explicit 
initializer, then arrays of that class can be defined! Except by using an
initializer list, there is no way to specify explicit arguments for a 
constructor in an array declaration. If you absolutely must initialize
members of an array with different values, you can write a default 
constructor that generates the desired values.

The constructor for a local static object is called the first time the
thread of control passes through the object's definition.

Operator new creates its object on the free store by default. But we 
could overload the new operator to place objects anywhere by providing
extra arguments. e.g.

void * operator new (size_t, void * p) { return p; } // explicit placement
operator

void * buf = reinterpret_cast<void *>(0xf00f); // significant address

X * p2 = new (buf) X; // construct an X at 'buf'; invokes operator 
new(sizeof(X), buf) -- placement syntax.

The placement new construct can also be used to allocate memory from
a specific arena.

class Arena {
    public:
        virtual void * alloc(size_t) = 0;
        virtual void free(void *) = 0;
        //...
};

void * operator new(size_t sz, Arena * a) { return a->alloc(sz); }

Now objects of arbitrary types can be allocated from different Arenas as
needed. e.g.

extern Arena * Persistent;
extern Arena * Shared;

void g(int i) {
    X * p = new(Persistent) X(i); // X in persistent storage
    X * q = new(Shared) X(i); // X in shared memory
}

Placing an object in an area that is not (directly) controlled by the 
standard free-store manager implies that some care is required when destroying
the object. The basic mechanism for that is an explicit call of a destructor:

void destroy(X * p, Arena * a) {
    p->~X(); // call destructor
    a->free(p); // free memory
}

A named union is defined as a struct, where every member has the same address. 
A union can have member functions but not static members. A union may not have
members with constructors or destructors.

An ordinary member function declaration specifies three logically distinct things:
1) The function can access the private part of the class declaration.
2) The function is in the scope of the class
3) The function must be invoked on an object (has a this pointer)

By declaring a member function static, we give it first two properties only. By
declaring a function a friend, we give it the first property only.

The standard library provides the template class auto_ptr, which supports the 
"resource acquisition is initialization" technique. Basically, an auto_ptr is
initialized by a pointer and can be dereferenced in the way that a pointer can.
Also, the object pointed to will be implicitly deleted at the end of the auto_ptr's
scope. When one auto_ptr is copied into another, the source no longer points to
anything. Because copying an auto_ptr modifies it, a const auto_ptr cannot be 
copied (destructive copy semantic). e.g.

void f (Point p1, Point p2, auto_ptr<Circle> pc, Shape * pb) // remember to delete pb on exit
{
    auto_ptr<Shape> p(new Rectangle(p1, p2)); // p points to a rectangle
    auto_ptr<Shape> pbox(pb);

    auto_ptr<Circle> p2(pc); // now p2 is responsible for deletion
    auto_ptr<Circle> p3(p2); // now p3 is responsible for deletion (and p2 isn't)
    p2->m = 8; // programmer error: p2.get() == 0
    p->rotate(45); // use auto_ptr<Shape> exactly asa a Shape *
    // ...
}

On exit of function f, all Shape, Rectangle pointed to by auto_ptr will be deleted
whether or not an exception is thrown.

The auto_ptr template is declared in <memory>. The effect of having more than one
auto_ptr own an object is undefined. Most likely, the object will be deleted twice
(with bad effects).

dynamic_cast is to deal with the case in which the correctness of the conversion
cannot be determined by the compiler. e.g.

dynamic_cast<T*>(p)

looks at the object pointed to by p (if any). If that object is of class T or has
a unique base class of type T, then dynamic_cast returns a pointer of type T* to
that object; otherwise, 0 is returned. If the value of p is 0, dynamic_cast<T*>(p)
returns 0. -- dynamic_cast is to cast between inherited classes. dynamic_cast has
a run-time overhead associated with it.

dynamic_cast cannot cast from void*, but static_cast can.

typeid operator yields an object representing the type of its operand. A typeid() is
most commonly used to find the type of an object referred to by a reference or a 
pointer. The type_info returned from typeid() operator can be compared for equality.

A variable of type ``pointer to member of class X'' is declared using a declarator
of the form X::*. e.g.

class Std_interface {
public :
    virtual void start() = 0;
    virtual void suspend() = 0;
    ...
};

typedef void (Std_interface::* Pstd_mem) ();

void f(Std_interface * p) {
    Pstd_mem s = & Std_interface::suspend;
    p->suspend(); //direct call
    (p->*s)(); //call through pointer to member
}

p->*m binds m to the object pointed to by p, and obj.*m binds m to the object obj.
A pointer to member isn't a pointer to a piece of memory the way a pointer to a 
variable or a pointer to a function is. It is more like an offset into a structure
or an index into an array. When a pointer to member is combined with a pointer to
an object of the right type, it yields something that identifies a particular member
of a particular object.

new(), delete() operator can be overloaded for a specific class instead of gloablly.
Member operator new()s and operator delete()s are implicitly static members. 
Consequently, they don't have a this pointer and do not modify an object. They provide 
storage that a constructor can initialize and a destructor can clean up.
