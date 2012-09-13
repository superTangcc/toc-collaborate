array-old.h: is the old-style include, pulls in most of Blitz++, including vector ET.

array.h: pulls in much less of the library, and in particular excludes the vector ET code.

With array-old.h, one gets TinyVector ET automatically, with array.h, one must now also include <tinyvec-et.h> to get TinyVector expressions.

The implementation of Array<T, N> has been moved to <blitz/array-impl.h>

array-impl.h: def. of Array<T, N> class, interesting headers include:
1) blitz.h 
2) memblock.h
3) range.h
4) indexexpr.h
5) array/storage.h
6) tinyvec.h

-----------------------------------------array-impl.h--------------------------------------
template<typename T_numtype, int N_rank>
class ArrayIterator;

template<typename T_numtype, int N_rank>
class ConstArrayIterator;

template<typename T_numtype, int N_rank>
class FastArrayIterator;

template<typename P_expr>
class _bz_ArrayExpr;

template<typename T_array, typename T_index>
class IndirectArray;

template <typename P_numtype, int N_RANK>
class Array : public MemoryBlockReference<P_numtype>
#ifdef BZ_NEW_EXPRESSION_TEMPLATES
, public ETBase<Array<P_numtype, N_RANK> >
#endif
/* PUBLIC TYPE
 */
/* class 'TinyVector' serves as the 'size_info' array in Pochoir
 */
/* T_index is a vector type which can be used to access elements of many-dimensional arrays.
 */
typedef TinyVector<int, N_RANK> T_index;
/* T_iterator is a fast iterator for the array, used for expression templates 
 */
typedef FastArrayIterator<T_numtype, N_RANK> T_iterator;
/* iterator is an STL-style iterator */
typedef ArrayIterator<T_numtype, N_RANK> iterator;
/* const_iterator is an STL-style const iterator */
typedef ConstArrayIterator<T_numtype, N_RANK> const_iterator;
/* T_array is the array type itself -- Array<T_numtype, N_RANK> */
typedef Array<T_numtype, N_RANK> T_array;

static const int _bz_rank = N_RANK;

/* class 'GeneralArrayStorage' storage_ in class 'Array' defines the underlying 
 * storage FORMAT rather than the real physical storage space. -- similar to SAView
 */
/* class 'MemoryBlock' provides a reference-counted block of memory. This block
 * may be referred to by multiple vector, matrix and array objects. The memory 
 * is automatically deallocated when the last referring object is destructed.
 * MemoryBlock may be sub-classed to provide speical allocators
 */
/* It seems the class 'MemoryBlockReference' is built on top of class 'MemoryBlock',
 * and it's the actual physical layer of storage for Array<T, N_RANK>
 */
/*
 * Create a reference of another array
 */
Array(const Array<T_numtype, N_rank>& array)
#ifdef BZ_NEW_EXPRESSION_TEMPLATES
    : MemoryBlockReference<T_numtype>(),
	/* Pay attention to 'ETBase' */
      ETBase< Array<T_numtype, N_rank> >(array)
#else
    : MemoryBlockReference<T_numtype>()
#endif
/* For Array constructor which comes with 'Range', it just integrates the 'first_' 
 * and 'length_' member directly into 'Array', while WITHOUT the 'stride_' !!!
 * -- In these constructors, it asserts that the 'stride_' == 1!
 * -- for 'stride_' != 1, it's handled in Array<>::slice() ???
 */
/* in constructors of Array, 'stride_[]' is computed in member function 
 * 'setupStorage(lastRankInitialized)' -> 'computeStrides()'
 * The 'stride_[]' is computed just on 'length_[]', and ascending/descending
 * order of each dimension - it has nothing to do with the 'stride_[]' in 'Range'
 * -- Range.isAscendingContiguous(): 
 * return ((first_ < last_) && (stride_ == 1) || (first_ == last_));
 */
-------------------------------------------------------------------------------------
/* T_iterator is a fast iterator for the array, used for expression templates 
 */
typedef FastArrayIterator<T_numtype, N_RANK> T_iterator;
T_iterator beginFast() const { return T_iterator(*this); }

/* BZ_PROMOTE is basically a type traits to promote the types 
 * _bz_meta_vectorDot<N_length, 0> is a class that uses meta-programming technique
 * to expand and compute the dot-product of vectors
 */
/* noConst() == const_cast<T_array &>(*this) 
 * BZPRECONDITION(0) : you should NOT call this function
 * typedef IndexPlaceHolder<0> firstIndex;
 * template <int N> class IndexPlaceHolder:
 * operator() is the only useful function inside class 'IndexPlaceHolder', which
 * simply returns the 'N's element of the input TinyVector<>.
 * BZ_ETPARM(T) -> T const &
 */
/*
 * The array expression templates iterator interface is followed by
 * these classes:
 *
 * FastArrayIterator          <blitz/array/fastiter.h>
 * _bz_ArrayExpr              <blitz/array/expr.h>
 * _bz_ArrayExprUnaryOp               "
 * _bz_ArrayExprBinaryOp              "
 * _bz_ArrayExprTernaryOp             "
 * _bz_ArrayExprConstant              "
 * _bz_ArrayMap               <blitz/array/map.h>
 * _bz_ArrayExprReduce        <blitz/array/reduce.h>
 * IndexPlaceholder           <blitz/indexexpr.h>
 */

/* class 'IndirectArray' should work like class 'A_Subscript()' in Pochoir 
 */
/* Indirection */
template<typename T_indexContainer>
IndirectArray<T_array, T_indexContainer>
operator[](const T_indexContainer& index) {
	return IndirectArray<T_array, T_indexContainer>(*this, 
					const_cast<T_indexContainer &> (index));
}

/* The assignment operator in class 'IndirectArray' uses iterator, and
 * its associated dereference operator '*' and '++' to traverse the array
 */
template<typename T_array, typename T_index> template<typename T_rhs>
void IndirectArray<T_array, T_index>::operator=(T_rhs rhs)
{ 
	typedef _bz_typename asExpr<T_rhs>::T_expr T_expr; 
	T_expr expr(rhs); 
	_bz_typename T_array::T_iterator arrayIter(array_); 
	_bz_typename T_index::iterator iter = index_.begin(), end = index_.end(); 
	
	for (; iter != end; ++iter) { 
		_bz_typename T_index::value_type subdomain = *iter; 
		applyOverSubdomain(array_, arrayIter, subdomain, expr); 
	} 
}

/* Assignment 'operator=' in 'Array' for : A = 5;
 * Scalar operand
 * NEEDS_WORK : need a precondition check on
 * isStorageContiguous when operator is used.
 */
ListInitializationSwitch<T_array,T_numtype*> operator=(T_numtype x) {
	return ListInitializationSwitch<T_array,T_numtype*>(*this, x); 
}

ListInitializationSwitch(T_array& array, T_numtype value)
	        : array_(array), value_(value), wipeOnDestruct_(true)
{ } 
				        
~ListInitializationSwitch() { 
	if (wipeOnDestruct_) 
		array_.initialize(value_); 
}

/* overload the 'operator,' in 'ListInitializer<>' to initialize the 
 * array with a list of values. -- unroll the loop by a factor of 2??
 */
ListInitializer<T_numtype, T_iterator> operator,(T_numtype x) { 
	wipeOnDestruct_ = false; 
	T_iterator iter = array_.getInitializationIterator(); 
	*iter = value_; 
	T_iterator iter2 = iter + 1; 
	*iter2 = x; 
	return ListInitializer<T_numtype, T_iterator>(iter2 + 1); 
}
/* The keyword 'mutable' is used to allow a particular data member of 
 * const object to be modified. This is particularly useful if most 
 * of the members should be constant but a few need to be updateable. 
 */

template<typename T_expr>
T_array& operator=(const ETBase<T_expr>&);
T_array& operator=(const Array<T_numtype,N_rank>&);

template<typename T_expr, typename T_update>
inline T_array& evaluate(T_expr expr, T_update);

/* BZ_HAVE_STD is defined if compiler has ISO C++ standard library
 */
#ifdef BZ_HAVE_STD
/* BZ_ARRAY_SPACE_FILLING_TRAVERSAL is undefined!
 */
#ifdef BZ_ARRAY_SPACE_FILLING_TRAVERSAL
template<typename T_expr, typename T_update>
inline T_array& evaluateWithFastTraversal(
    const TraversalOrder<N_rank - 1>& order,
    T_expr expr, T_update);
#endif
#endif

/* BZ_ARRAY_2D_STENCIL_TILING is defined in blitz/tuning.h
 */
#ifdef BZ_ARRAY_2D_STENCIL_TILING
template<typename T_expr, typename T_update>
inline T_array& evaluateWithTiled2DTraversal(
    T_expr expr, T_update);
#endif

template<typename T_expr, typename T_update> 
inline T_array& evaluateWithIndexTraversal1( T_expr expr, T_update); 

template<typename T_expr, typename T_update> 
inline T_array& evaluateWithIndexTraversalN( T_expr expr, T_update); 

template<typename T_expr, typename T_update> 
inline T_array& evaluateWithStackTraversal1( T_expr expr, T_update); 

template<typename T_expr, typename T_update> 
inline T_array& evaluateWithStackTraversalN( T_expr expr, T_update); 

T_numtype* restrict getInitializationIterator() { return dataFirst(); }
/*
 * Include implementations of the member functions and some additional
 * global functions.
 */

#include <blitz/array/iter.h>       // Array iterators
#include <blitz/array/fastiter.h>   // Fast Array iterators (for et)
#include <blitz/array/expr.h>       // Array expression objects
#include <blitz/array/methods.cc>   // Member functions
#include <blitz/array/eval.cc>      // Array expression evaluation
#include <blitz/array/ops.cc>       // Assignment operators
#include <blitz/array/io.cc>        // Output formatting
#include <blitz/array/et.h>         // Expression templates
#include <blitz/array/reduce.h>     // Array reduction expression templates
#include <blitz/array/interlace.cc> // Allocation of interlaced arrays
#include <blitz/array/resize.cc>    // Array resize, resizeAndPreserve
#include <blitz/array/slicing.cc>   // Slicing and subarrays
#include <blitz/array/cycle.cc>     // Cycling arrays
#include <blitz/array/complex.cc>   // Special support for complex arrays
#include <blitz/array/zip.h>        // Zipping multicomponent types
#include <blitz/array/where.h>      // where(X,Y,Z)
#include <blitz/array/indirect.h>   // Indirection
#include <blitz/array/stencils.h>   // Stencil objects

-----------------------------------blitz/array/iter.h------------------------------------
/* Basic iterator for arrays */
#include <iterator>

/* Helper class ConstPointerStack */
template<typename P_numtype, int N_rank>
class ConstPointerStack {
private: 
	const T_numtype * stack_[N_rank]; 
public:
    typedef P_numtype T_numtype;
	
	void operator=(const ConstPointerStack<P_numtype,N_rank>& rhs) { 
		for (int i=0; i<N_rank; ++i) 
			stack_[i] = rhs.stack_[i]; 
	} 
	
	const T_numtype*& operator[](int position) { 
		return stack_[position]; 
	} 
};

/* the implementation of this operator++ looks very similar to that of 'updateIndex'
 * in Pochoir
 */
template<typename T, int N>
ConstArrayIterator<T,N>& ConstArrayIterator<T,N>::operator++();

----------------------------------blitz/array/fastiter.h---------------------------------
/* stringstream provides an interface to manipulate strings as if they were input/output
 * streams
 */
#include <sstream>
#include <blitz/array/iter.h>

template<typename P_numtype, int N_rank>
class FastArrayIterator {
private:
	/* restrict pointer means there's no Alias of the pointer to the same block of data,
	 * thus enable some optimization from compiler
	 */
    const T_numtype * restrict data_;
	const T_array & array_;
	ConstPointerStack<T_numtype,N_rank> stack_; 
	int stride_;

public: 
	typedef P_numtype T_numtype; 
	typedef Array<T_numtype, N_rank> T_array; 
	typedef FastArrayIterator<P_numtype, N_rank> T_iterator; 
	typedef const T_array& T_ctorArg1; 
	typedef int            T_ctorArg2;    /* dummy */
	
	static const int 
		numArrayOperands = 1, 
		numIndexPlaceholders = 0, 
		rank = N_rank;
	/* The rest of this iterator's function has no more functionality than that has
	 * been implemented in Pochoir
	 */
---------------------------------------------array/et.h-----------------------------------
#ifdef BZ_NEW_EXPRESSION_TEMPLATES
#include <blitz/array/newet.h>     // Expression templates
#else
#include <blitz/array/bops.cc>     // Expression templates, two operands
#include <blitz/array/uops.cc>     // Expression templates, math functions
#include <blitz/array/misc.cc>     // Expression templates, miscellaneous
#endif

--------------------------------------------array/newet.h---------------------------------
// Gang include of new expression templates implementation.

#include <blitz/array/ops.h>
#include <blitz/array/funcs.h>

// ET support for functors acting on Arrays

#include <blitz/array/functorExpr.h>

-------------------------------------------array/ops.h------------------------------------
BZ_DECLARE_ARRAY_ET_BINARY(operator+,  Add)
BZ_DECLARE_ARRAY_ET_BINARY(operator-,  Subtract)
BZ_DECLARE_ARRAY_ET_BINARY(operator*,  Multiply)
BZ_DECLARE_ARRAY_ET_BINARY(operator/,  Divide)

------------------------------------------array/newet-macros.h----------------------------
/*
 * Array expression templates: the macro BZ_DECLARE_ARRAY_ET_BINARY(X,Y)
 * declares a function or operator which takes two operands.
 * X is the function name (or operator), and Y is the functor object
 * which implements the operation.
 */

#define BZ_DECLARE_ARRAY_ET_BINARY(name, applic)                          \
                                                                          \
template <typename T1,typename T2>                                        \
_bz_inline_et                                                             \
typename BzBinaryExprResult<applic,T1,T2>::T_result                       \
name(const ETBase<T1>& d1,const ETBase<T2>& d2)                           \
{                                                                         \
    typedef typename BzBinaryExprResult<applic,T1,T2>::T_result result;   \
    return result(asExpr<T1>::getExpr(d1.unwrap()),                       \
                  asExpr<T2>::getExpr(d2.unwrap()));                      \
}

-----------------------------------------array/asexpr.h-----------------------------------
template <template <typename T1, typename T2> class OP,
          typename O1, typename O2>
struct BzBinaryExprResult { 
	typedef _bz_ArrayExpr<_bz_ArrayExprBinaryOp< 
		typename asExpr<O1>::T_expr, 
		typename asExpr<O2>::T_expr, 
		OP<typename asExpr<O1>::T_expr::T_numtype, 
		   typename asExpr<O2>::T_expr::T_numtype> > > T_result; 
};

----------------------------------------array/etbase.h------------------------------------
template<typename T>
class ETBase { 
public:
    ETBase() { } 
	
	ETBase(const ETBase<T>&) { } 
	
	/* static_cast<type-id>(expression):
	 * convert expression to the type of type-id based solely on the types
	 * present in the expression
	 * - 'static_cast' operator can be used for operations such as converting a pointer
	 * to a base class to a pointer to a derived class. Such conversions are not always
	 * safe.
	 * - In general, you use 'static_cast' when you want to convert numeric data types
	 * such as enums to ints or ints to floats, and you are certain of the data types
	 * involved in the conversion. 'static_cast' conversions are not as safe as 
	 * 'dynamic_cast' conversions, because 'static_cast' does no run-time type check,
	 * while 'dynamic_cast' does. A 'dynamic_cast' to an ambiguous pointer will fail, 
	 * while a 'static_cast' returns as if nothing were wrong; this can be dangerous.
	 * although 'dynamic_cast' conversions are safer, 'dynamic_cast' only works on 
	 * pointers or references, and the run-time type check is an overhead.
	 */

	T& unwrap() { return static_cast<T&>(*this); } 
	
	const T& unwrap() const { return static_cast<const T&>(*this); } 
};

// The traits class asExpr converts arbitrary things to
// expression templatable operands.

//  Default to scalar.
template <typename T>
struct asExpr {
	/* _bz_ArrayExprConstant<T> looks like the A_Scalar<T> in Pochoir
	 */
    typedef _bz_ArrayExprConstant<T> T_expr; 
	static T_expr getExpr(const T& x) { 
		return T_expr(x); 
	} 
};

//  Already an expression template term
struct asExpr<_bz_ArrayExpr<T> > {
    typedef _bz_ArrayExpr<T> T_expr;
    static const T_expr& getExpr(const T_expr& x) { return x; }
};

//  An array operand
template <typename T,int N>
struct asExpr<Array<T,N> > {
    typedef FastArrayIterator<T,N> T_expr;
	/* T_iterator beginFast() const {return T_iterator(*this); }
    static T_expr getExpr(const Array<T,N>& x) { return x.beginFast(); }
};

//  Index placeholder

template <int N>
struct asExpr<IndexPlaceholder<N> > {
    typedef IndexPlaceholder<N> T_expr;
    static T_expr getExpr(T_expr x) { 
		return x; 
	}
};         

-----------------------------------------array/expr.h----------------------------------
template<typename T1, typename T2>
class _bz_ExprPair {
	protected: T1 first_; T2 second_; 
public:
    _bz_ExprPair(const T1& a, const T2& b) : first_(a), second_(b) { }

	const T1& first() const { return first_; }

    const T2& second() const { return second_; } 
};

template<typename T1, typename T2>
inline _bz_ExprPair<T1,T2> makeExprPair(const T1& a, const T2& b)
{
    return _bz_ExprPair<T1,T2>(a,b);
}

template<typename P_expr>
class _bz_ArrayExpr
#ifdef BZ_NEW_EXPRESSION_TEMPLATES
    : public ETBase<_bz_ArrayExpr<P_expr> >
#endif
{
protected:
    _bz_ArrayExpr() { }
    T_expr iter_;

public: 
	typedef P_expr T_expr; 
	typedef _bz_typename T_expr::T_numtype T_numtype; 
	typedef T_expr T_ctorArg1; 
	typedef int    T_ctorArg2;    // dummy 
	
	static const int 
		numArrayOperands = T_expr::numArrayOperands, 
		numIndexPlaceholders = T_expr::numIndexPlaceholders, 
		rank = T_expr::rank; 
		
	_bz_ArrayExpr(const _bz_ArrayExpr<T_expr>& a) 
#ifdef BZ_NEW_EXPRESSION_TEMPLATES 
	: ETBase< _bz_ArrayExpr<T_expr> >(a), iter_(a.iter_) 
#else 
	: iter_(a.iter_) 
#endif 
	{ }

#if defined(BZ_NEW_EXPRESSION_TEMPLATES) && ! defined(__MWERKS__)
    template<typename T>
	_bz_ArrayExpr(const T& a)
	    : iter_(a) { }
#else

    /* BZ_ETPARM(T_expr) == T_expr const & */
    _bz_ArrayExpr(BZ_ETPARM(T_expr) a)
        : iter_(a) { }

#if !defined(__MWERKS__)
    _bz_ArrayExpr(BZ_ETPARM(_bz_typename T_expr::T_ctorArg1) a) 
		: iter_(a) { } 
#endif 
#endif

   template<typename T1, typename T2> 
   _bz_ArrayExpr(BZ_ETPARM(T1) a, BZ_ETPARM(T2) b) 
		: iter_(a, b) { }

	template<typename T1, typename T2, typename T3>
	_bz_ArrayExpr(BZ_ETPARM(T1) a, BZ_ETPARM(T2) b, BZ_ETPARM(T3) c) : iter_(a, b, c) { }

	template<typename T1, typename T2, typename T3, typename T4> 
	_bz_ArrayExpr(BZ_ETPARM(T1) a, BZ_ETPARM(T2) b, BZ_ETPARM(T3) c, BZ_ETPARM(T4) d) : 
		iter_(a, b, c, d) { }

	template<typename T1, typename T2> 
	_bz_ArrayExpr(const _bz_ExprPair<T1,T2>& pair) : iter_(pair.first(), pair.second()) { } 
	
	/* dereference the data pointed by iter_ */ 
	T_numtype operator*() { return *iter_; } 
};

----------------------------------------array/ops.cc--------------------------------------
template<typename P_numtype, int N_rank> template<typename T_expr>
inline Array<P_numtype,N_rank>&
Array<P_numtype,N_rank>::operator=(const ETBase<T_expr>& expr)
{
	/*_bz_update is just a type promotion */
    evaluate(expr.unwrap(), 
		_bz_update<T_numtype, _bz_typename T_expr::T_numtype>());
	return *this;
}   

template<typename P_numtype, int N_rank>
inline Array<P_numtype, N_rank>&
Array<P_numtype, N_rank>::operator=(const Array<T_numtype,N_rank>& x)
{     
    (*this) = _bz_ArrayExpr<FastArrayIterator<T_numtype, N_rank> >
	        (x.beginFast()); 
    return *this;
}       

----------------------------------------array/eval.cc---------------------------------------
template<typename T_numtype, int N_rank> template<typename T_expr, typename T_update>
inline Array<T_numtype, N_rank>&
Array<T_numtype, N_rank>::evaluate(T_expr expr, T_update) {
	/* Check shape! */
    // Determine which evaluation mechanism to use 
	if (T_expr::numIndexPlaceholders > 0) {
        // The expression involves index placeholders, so have to
        // use index traversal rather than stack traversal.
		if (N_rank == 1) 
			return evaluateWithIndexTraversal1(expr, T_update()); 
		else 
			return evaluateWithIndexTraversalN(expr, T_update()); 
	} else { 
		// If this expression looks like an array stencil, then attempt to 
		// use a fast traversal order.  
		// Fast traversals require <set> from the ISO/ANSI C++ standard 
		// library.  
#ifdef BZ_HAVE_STD 
		/* BZ_ARRAY_SPACE_FILLING_TRAVERSAL is NOT defined! */
#ifdef BZ_ARRAY_SPACE_FILLING_TRAVERSAL 
		enum { isStencil = (N_rank >= 3) && (T_expr::numArrayOperands > 6) 
			&& (T_expr::numIndexPlaceholders == 0) }; 
		
		if (_bz_tryFastTraversal<isStencil>::tryFast(*this, expr, T_update())) 
			return *this; 
#endif 
#endif 

		/* BZ_ARRAY_2D_STENCIL_TILING is defined! */
#ifdef BZ_ARRAY_2D_STENCIL_TILING 
		// Does this look like a 2-dimensional stencil on a largeish 
		// array?  
		
		if ((N_rank == 2) && (T_expr::numArrayOperands >= 5)) { 
			// Use a heuristic to determine whether a tiled traversal 
			// is desirable.  First, estimate how much L1 cache is needed 
			// to achieve a high hit rate using the stack traversal.  
			// Try to err on the side of using tiled traversal even when 
			// it isn't strictly needed.  
			
			// Assumptions: 
			//    Stencil width 3 
			//    3 arrays involved in stencil 
			//    Uniform data type in arrays (all T_numtype) 
			
			int cacheNeeded = 3 * 3 * sizeof(T_numtype) * length(ordering(0)); 
			if (cacheNeeded > BZ_L1_CACHE_ESTIMATED_SIZE) 
				return evaluateWithTiled2DTraversal(expr, T_update()); 
		} 
#endif 
        // If fast traversal isn't available or appropriate, then just
		// do a stack traversal.
		if (N_rank == 1)
		   return evaluateWithStackTraversal1(expr, T_update());
		else
		   return evaluateWithStackTraversalN(expr, T_update()); 
	}
}
-----------------------------------------------------------------------------------------
template <template <typename T1, typename T2> class OP,
          typename O1, typename O2>
struct BzBinaryExprResult { 
	typedef _bz_ArrayExpr<_bz_ArrayExprBinaryOp< 
		typename asExpr<O1>::T_expr, 
		typename asExpr<O2>::T_expr, 
		OP<typename asExpr<O1>::T_expr::T_numtype, 
		   typename asExpr<O2>::T_expr::T_numtype> > > T_result; };  

template<typename P_expr>
class _bz_ArrayExpr : public ETBase<_bz_ArrayExpr<P_expr> > {
	public:
		typedef P_expr T_expr;
	protected:
		T_expr iter_;
}

template<typename P_expr1, typename P_expr2, typename P_op>
class _bz_ArrayExprBinaryOp {
public:
    typedef P_expr1 T_expr1; 
	typedef P_expr2 T_expr2; 
	typedef P_op T_op; 
	typedef _bz_typename T_expr1::T_numtype T_numtype1; 
	typedef _bz_typename T_expr2::T_numtype T_numtype2; 
	typedef _bz_typename T_op::T_numtype T_numtype; 
	typedef T_expr1 T_ctorArg1; 
	typedef T_expr2 T_ctorArg2;

    _bz_ArrayExprBinaryOp(
	    const _bz_ArrayExprBinaryOp<T_expr1, T_expr2, T_op>& a)
	    : iter1_(a.iter1_), iter2_(a.iter2_)
	{ }

	template<typename T1, typename T2>
	_bz_ArrayExprBinaryOp(BZ_ETPARM(T1) a, BZ_ETPARM(T2) b)
	    : iter1_(a), iter2_(b)
	{ }

    T_numtype operator*()
	{ return T_op::apply(*iter1_, *iter2_); }
}

template<typename P_numtype, int N_rank> template<typename T_expr>
inline Array<P_numtype, N_rank> &
Array<P_numtype, N_rank>::operator=(const ETBase<T_expr>& expr) {
	evaluate(expr.unwrap(), _bz_update<T_numtype, _bz_typename T_expr::T_numtype>());
}
==>
template<typename T_numtype, int N_rank> template<typename T_expr, typename T_update>
inline Array<T_numtype, N_rank>&
Array<T_numtype, N_rank>::evaluate(T_expr expr, T_update);
==>
evaluateWithStackTraversalN(expr, T_update());
/*
 * A stack traversal replaces the usual nested loops:
 *
 * for (int i=A.lbound(firstDim); i <= A.ubound(firstDim); ++i)
 *   for (int j=A.lbound(secondDim); j <= A.ubound(secondDim); ++j)
 *     for (int k=A.lbound(thirdDim); k <= A.ubound(thirdDim); ++k)
 *       A(i,j,k) = 0;
 *
 * with a stack data structure.  The stack allows this single
 * routine to replace any number of nested loops.
 *
 * For each dimension (loop), these quantities are needed:
 * - a pointer to the first element encountered in the loop
 * - the stride associated with the dimension/loop
 * - a pointer to the last element encountered in the loop
 *
 * The basic idea is that entering each loop is a "push" onto the
 * stack, and exiting each loop is a "pop".  In practice, this
 * routine treats accesses the stack in a random-access way,
 * which confuses the picture a bit.  But conceptually, that's
 * what is going on.
 */

/*
 * ordering(0) gives the dimension associated with the smallest
 * stride (usually; the exceptions have to do with subarrays and
 * are uninteresting).  We call this dimension maxRank; it will
 * become the innermost "loop".
 *
 * Ordering the loops from ordering(N_rank-1) down to
 * ordering(0) ensures that the largest stride is associated
 * with the outermost loop, and the smallest stride with the
 * innermost.  This is critical for good performance on
 * cached machines.
 */

	const int maxRank = ordering(0);
	// const int secondLastRank = ordering(1);

	// Create an iterator for the array receiving the result
	FastArrayIterator<T_numtype, N_rank> iter(*this);

	// Set the initial stack configuration by pushing the pointer
	// to the first element of the array onto the stack N times.

	int i;
	for (i=1; i < N_rank; ++i)
    {
        iter.push(i);
        expr.push(i);
    }

    // Load the strides associated with the innermost loop.
    iter.loadStride(maxRank);
    expr.loadStride(maxRank);

    /* 
	 * Is the stride in the innermost loop equal to 1?  If so,
	 * we might take advantage of this and generate more
	 * efficient code.
	 */
	bool useUnitStride = iter.isUnitStride(maxRank)
	                      && expr.isUnitStride(maxRank);

    /*
     * Do all array operands share a common stride in the innermost
     * loop?  If so, we can generate more efficient code (but only
     * if this optimization has been enabled).
     */
#ifdef BZ_ARRAY_EXPR_USE_COMMON_STRIDE
    int commonStride = expr.suggestStride(maxRank);
    if (iter.suggestStride(maxRank) > commonStride)
        commonStride = iter.suggestStride(maxRank);
    bool useCommonStride = iter.isStride(maxRank,commonStride)
        && expr.isStride(maxRank,commonStride);

#ifdef BZ_DEBUG_TRAVERSE
    BZ_DEBUG_MESSAGE("BZ_ARRAY_EXPR_USE_COMMON_STRIDE" << endl
        << "commonStride = " << commonStride << " useCommonStride = "
        << useCommonStride);
#endif

#else
    int commonStride = 1;
    bool useCommonStride = false;
#endif

    /*
     * The "last" array contains a pointer to the last element
     * encountered in each "loop".
     */
    const T_numtype* last[N_rank];

    // Set up the initial state of the "last" array
    for (i=1; i < N_rank; ++i)
        last[i] = iter.data() + length(ordering(i)) * stride(ordering(i));

    int lastLength = length(maxRank);
    int firstNoncollapsedLoop = 1;

#ifdef BZ_COLLAPSE_LOOPS

    /*
     * This bit of code handles collapsing loops.  When possible,
     * the N nested loops are converted into a single loop (basically,
     * the N-dimensional array is treated as a long vector).
     * This is important for cases where the length of the innermost
     * loop is very small, for example a 100x100x3 array.
     * If this code can't collapse all the loops into a single loop,
     * it will collapse as many loops as possible starting from the
     * innermost and working out.
     */

     // Collapse loops when possible
     for (i=1; i < N_rank; ++i)
     {
         // Figure out which pair of loops we are considering combining.
         int outerLoopRank = ordering(i);
         int innerLoopRank = ordering(i-1);

         /*
          * The canCollapse() routines look at the strides and extents
          * of the loops, and determine if they can be combined into
          * one loop.
          */

         if (canCollapse(outerLoopRank,innerLoopRank)
            && expr.canCollapse(outerLoopRank,innerLoopRank))
         {
#ifdef BZ_DEBUG_TRAVERSE
			cout << "Collapsing " << outerLoopRank << " and "
			     << innerLoopRank << endl;
#endif
            lastLength *= length(outerLoopRank);
            firstNoncollapsedLoop = i+1;
         }
         else
             break;
      }
#endif // BZ_COLLAPSE_LOOPS

    /*
     * Now we actually perform the loops.  This while loop contains
     * two parts: first, the innermost loop is performed.  Then we
     * exit the loop, and pop our way down the stack until we find
     * a loop that isn't completed.  We then restart the inner loops
     * and push them onto the stack.
     */

     while (true) {
         /*
          * This bit of code handles the innermost loop.  It would look
          * a lot simpler if it weren't for unit stride and common stride
          * optimizations; these clutter up the code with multiple versions.
          */
         if ((useUnitStride) || (useCommonStride))
         {
#ifdef BZ_USE_FAST_READ_ARRAY_EXPR

           /*
            * The check for BZ_USE_FAST_READ_ARRAY_EXPR can probably
            * be taken out.  This was put in place while the unit stride/
            * common stride optimizations were being implemented and
            * tested.
            */

            // Calculate the end of the innermost loop
            int ubound = lastLength * commonStride;

            /*
             * This is a real kludge.  I didn't want to have to write
             * a const and non-const version of FastArrayIterator, so I use a
             * const iterator and cast away const.  This could
             * probably be avoided with some trick, but the whole routine
             * is ugly, so why bother.
             */

			 /* iter represents the iterator of left-hand side expression */
            T_numtype* restrict data = const_cast<T_numtype*>(iter.data());

            /*
             * BZ_NEEDS_WORK-- need to implement optional unrolling.
             */
            if (commonStride == 1)
            {
                for (int i=0; i < ubound; ++i)
                    T_update::update(*data++, expr.fastRead(i));
            }
#ifdef BZ_ARRAY_EXPR_USE_COMMON_STRIDE
            else {
                for (int i=0; i != ubound; i += commonStride)
                    T_update::update(data[i], expr.fastRead(i));
            }
#endif
            /*
             * Tidy up for the fact that we haven't actually been
             * incrementing the iterators in the innermost loop, by
             * faking it afterward.
             */
            iter.advance(lastLength * commonStride);
            expr.advance(lastLength * commonStride);
#endif              
        }
        else {
            /*
             * We don't have a unit stride or common stride in the innermost
             * loop.  This is going to hurt performance.  Luckily 95% of
             * the time, we hit the cases above.
             */
            T_numtype * restrict end = const_cast<T_numtype*>(iter.data())
                + lastLength * stride(maxRank);

            while (iter.data() != end)
            {
                T_update::update(*const_cast<T_numtype*>(iter.data()), *expr);
                iter.advance();
                expr.advance();
            }
        }

        /*
         * We just finished the innermost loop.  Now we pop our way down
         * the stack, until we hit a loop that hasn't completed yet.
         */
        int j = firstNoncollapsedLoop;
        for (; j < N_rank; ++j)
        {
            // Get the next loop
            int r = ordering(j);

            // Pop-- this restores the data pointers to the first element
            // encountered in the loop.
            iter.pop(j);
            expr.pop(j);

            // Load the stride associated with this loop, and increment
            // once.
            iter.loadStride(r);
            expr.loadStride(r);
            iter.advance();
            expr.advance();

            // If we aren't at the end of this loop, then stop popping.
            if (iter.data() != last[j])
                break;
        }
       // Are we completely done?
        if (j == N_rank)
            break;

        // No, so push all the inner loops back onto the stack.
        for (; j >= firstNoncollapsedLoop; --j)
        {
            int r2 = ordering(j-1);
            iter.push(j);
            expr.push(j);
            last[j-1] = iter.data() + length(r2) * stride(r2);
        }

        // Load the stride for the innermost loop again.
        iter.loadStride(maxRank);
        expr.loadStride(maxRank);
	} /* end while (true) */

    return *this;
}

