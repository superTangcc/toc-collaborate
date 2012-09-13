#if defined(__x86_64__)
  #include <xmmintrin.h>
  #include <emmintrin.h>
  #include <pmmintrin.h>
#elif defined(__ia64__)
  #include <ia64intrin.h>
#endif
