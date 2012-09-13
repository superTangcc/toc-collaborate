#pragma once
#ifndef Assert_H
#define Assert_H

// Setting ASSERTIONS to 0 turns off internal checking.
// Setting ASSERTIONS to 1 turns on internal checking.
// (i.e. much more thorough at the cost of being slower.
#ifdef ASSERTIONS
// Use whatever value was supplied on command line.
#else
#define ASSERTIONS 1	/* Turn on assertions if debugging */
#endif /* ASSERTIONS */

#define USE_HOST_ASSERT 0

#if ASSERTIONS
#if USE_HOST_ASSERT
#include <cassert>
#define Assert assert
#else
void AssertionFailure(const char* filename_, int line, const char* expression);
#define Assert(predicate) ((predicate)||(AssertionFailure(__FILE__,__LINE__,#predicate),true))
#endif
template<typename T> inline void Poison(T*& ptr) {ptr=(T*)-1;}
#else
#define Assert(predicate) ((void)0)
template<typename T> inline void Poison(T*&) {}
#endif /*!ASSERTIONS*/

#endif /*Assert_H*/
