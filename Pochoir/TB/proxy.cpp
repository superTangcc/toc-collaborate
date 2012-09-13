// an example showing how to design Proxy class
//
// by Dahua Lin
// modified by Yuan Tang
//

#include <chrono>
#include <ratio>
#include <iostream>
#include <cstdio>
#include <cstdlib>

// do whatever you want for setting
template<typename T>
inline void trace_setter(T v)
{
    std::cout << "setting value " << v << std::endl;
}


template<typename T>
class Proxy
{
public:
    explicit Proxy(T * v) : m_ref(v), m_value(*v) { }
    explicit Proxy(T v) : m_value(v), m_ref(&m_value) { }

    operator T() const  // the implicit conversion makes a proxy just like the value itself
    {
	    return (*m_ref);
    }
    operator T& () {
        return (*m_ref);
    }
    T * operator->() {
        return m_ref;
    }

    Proxy<T> & operator= (T const & rhs)
    {
        trace_setter(rhs);
        (*m_ref) = rhs;
        return (*this);
    }

    Proxy<T> & operator= (Proxy<T> & rhs)
    {
        T const & l_rhs = T(rhs);
        trace_setter(l_rhs);
        (*m_ref) = l_rhs;
        return (*this);
    }

private:
    T * m_ref;
    T m_value;
};


template<typename T>
class Array
{
public:
    Array(int n, const T& initvalue) {
	m_num = n;
	m_data = new T[n];
	for (int i = 0; i < n; ++i) 
	    m_data[i] = initvalue;	
    }

    Array(int n) {
        m_num = n;
        m_data = new T[n];
    }

    ~Array() {
	    delete[] m_data;
    }

    int size(void) { return m_num; }

    T operator() (int i) const {
        std::cout << "T operator() () const is called!" << std::endl;
        // return m_data[i];
        return T();
    }
    Proxy<T> operator() (int i) {
        if (i < 0 || i >= m_num)
            return Proxy<T>(const_cast< Array<T> const & >(*this)(i));
	    else
            return Proxy<T>(&(m_data[i]));
    }
    friend std::ostream & operator<<(std::ostream & os, Array<T> & a) {
        const int l_size = a.size();
        for (int i = 0; i < l_size; ++i) {
            os << a(i) << " ";
        }
        return os;
    }   

private:
    // disable copying
    // (For simplicity, I just don't want to implement the copy constructor and assignment)
    Array(const Array& );
    Array& operator = (const Array& );

private:
    int m_num;
    T *m_data;
};

struct lcs {
    lcs() : value(-1), fvalue(-1) {}
    lcs(int _v, double _fv) : value(_v), fvalue(_fv) {}
    lcs(lcs const & _l) {
        value = _l.value;
        fvalue = _l.fvalue;
    }
    lcs & operator= (lcs const & _l) {
        value = _l.value;
        fvalue = _l.fvalue;
        return (*this);
    }
    friend std::ostream & operator<<(std::ostream & os, lcs & a) {
        os << "int = " << a.value << ", fvalue = " << a.fvalue << std::endl;
        return os;
    }   

    int value;
    double fvalue;
};

int main(int argc, char *argv[])
{
    lcs l_lcs(0, 0);
    Array<lcs> a(3, l_lcs);
    Array<lcs> b(3);

    auto t = std::chrono::monotonic_clock::now();
    static_cast<lcs&>(a(0)).value = lcs(b(0)).value + 10;
    b(1)->fvalue = a(1)->fvalue + a(-1)->fvalue;
    a(2)->value = b(2)->value + b(-1)->value;
    b(2)->value = a(2)->value + a(1)->value;
    auto d = std::chrono::monotonic_clock::now() - t;
    std::cout << "it took " << d.count() << " ticks\n";

    std::cout << "a" << std::endl << a << std::endl;
    std::cout << "b" << std::endl << b << std::endl;
    return 0;
}


