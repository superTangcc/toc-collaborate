#include "AssertLib.h"
#include <cassert>

#if ASSERTIONS
#if !USE_HOST_ASSERT
extern void AssertionFailure(const char* filename, int line, const char* expression) {
	{
		assert(0);
	}
}
#endif /*!USE_HOST_ASSERT*/
#endif /*NO_ASSERTIONS*/
