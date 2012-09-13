-- Following notes are adapted from the email conversation with Dahua Lin@csail.mit

According to the C++ standard, the C++ compiler should resolve which 
overloading version of function/operator to use based on the types of 
input arguments, and the resolution does not use any information of how 
you return the result.

In your program, the following two declaration of operators:

int const& operator() (int n) const
int operator() (int n) const

can be conceptually understood of two overloaded functions like:

int const& operator() (const A& self, int n);
int              operator() (const A& self, int n);

Comparing their signatures (the sequence of types of input arguments), 
they are exactly the same. Therefore, C++ consider them as identical. A 
strict compiler will raise an error about overloading a function with 
identical signature.

Well, to support the syntax like:

a(5) = 1 + a(2).

You should notice that the getting does not modify the object, while 
setting modifies the object. Hence, you can write the following:

int operator() (int n) const;   // for getting
int& operator() (int n);           // for setting

For the overloaded version of getting, you associate a "const" attribute 
to the function, and thus distinguish its signature from the one for 
setting. In this way, the syntax that you desire is accomplished.

However, you need to keep in mind, that the overload resolves which 
version to use purely based on whether the object is a const object, but 
not how your calling statement looks like.

For example,

void fun1(A& a)
{
      a(5) = a(2) + 1;            // both a(5) and a(2) actually call 
the "setter", however, it works fine.
}

void fun1(const A& a)
{
      a(5) = a(2) + 1;           // error:  both call the "getter", you 
cannot set a value a(5) here. 
                                          // this is expected, since you 
use "const" in argument, you are supposed not to modify a
}

In the statement:

a(5) = a(2) + 1.

No matter how you design the class A, a(5) and a(2) will call exactly 
the same version. This is due to the overload mechanism of C++, which 
makes the decision purely based on input (but not whether the thing is 
placed left or right hand side).

If you really want to have distinct behavior while keeping a concise 
syntax. There is a way to do so -- return a proxy rather than the value 
itself.

a(5) -> Proxy(5);
a(2) -> Proxy(2);

when do a(5) = a(2) + 1,  it will call the Proxy(5)'s assignment 
operator.  Note that only when setting is invoked, this assignment 
operator will be called. This distinction give you the flexibility to 
implement different behavior for getting and setting.

Be cautious, this kind of tricks will sometimes lead to codes that are 
complicated and difficult to comprehend, so use it only when necessary. 
Also, indirection layer can always give you flexibility to accomplish 
subtle behavior, but it might compromise efficiency in some cases.
