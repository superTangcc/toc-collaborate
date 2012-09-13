/*
 * ============================================================================
 *
 *       Filename:  tb_boost_type_traits.cpp
 *
 *    Description:  test bench of boost's type_traits.hpp
 *
 *        Version:  1.0
 *        Created:  02/10/2012 04:36:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Tang (), yuantang@csail.mit.edu
 *        Company:  CSAIL, M.I.T.
 *
 * ============================================================================
 */

#include <boost/type_traits.hpp>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class CVector {
    public:

    ~CVector() {
        release_region(truth_type());
    }
    void addValue(const T& t) {
        values_.push_back(t);
    }

    void print() {
        for (unsigned int i = 0; i < values_.size(); i++) 
            doPrint(values_[i], truth_type());
    }


    private:
    void doPrint(const T& t, const boost::false_type&) {
        cout << "Not pointer. Value:" << t << endl;
    }

    void doPrint(const T& t, const boost::true_type&) {
        cout << "Pointer. Value: " << *t << endl;
    }

    std::vector<T> values_;
    typedef boost::integral_constant<bool,
      ::boost::is_pointer<T>::value> truth_type;
    void release_region(const boost::false_type&) {
        return;
    }
    void release_region(const boost::true_type&) {
        for (int i = 0; i < values_.size(); ++i) {
            delete values_[i];
        }
        return;
    }
};

template <int N_RANK>
struct Foo {
    int shape[N_RANK];
    friend std::ostream & operator<<(ostream & os, Foo<N_RANK> const & f) {
        int i = 0;
        for (i = 0; i < N_RANK-1; ++i) {
            os << "shape[" << i << "] = " << f.shape[i] << ", ";
        }
        os << "shape[" << i << "] = " << f.shape[i] << endl;
        return os;
    }
};

int main() {
    CVector<int> integers;
    integers.addValue(3);
    integers.addValue(5);
    integers.print();

    CVector<int*> pointers;
    int * three = new int(4);
    int * five = new int(6);
    pointers.addValue(three);
    pointers.addValue(five);
    pointers.print(); 

    CVector<Foo<1>> foo;
    Foo<1> l_foo;
    l_foo.shape[0] = 2;
    foo.addValue(l_foo);
    l_foo.shape[0] = 4;
    foo.addValue(l_foo);
    foo.print();

    CVector<Foo<2>*> foo1;
    Foo<2> * l_foo1 = new Foo<2>;
    l_foo1->shape[0] = 1;
    l_foo1->shape[1] = 3;
    foo1.addValue(l_foo1);
    Foo<2> * l_foo2 = new Foo<2>;
    l_foo2->shape[0] = 5;
    l_foo2->shape[1] = 7;
    foo1.addValue(l_foo2);
    foo1.print();
    return 0;
}

