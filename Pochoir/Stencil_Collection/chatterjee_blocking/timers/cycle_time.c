/*------------------------------------------------------------------
 * PowerPC "cycle" counter using the time base register.
 *-----------------------------------------------------------------*/
#if (defined(__powerpc) || defined(__powerpc__) || defined(__PPC__) || defined(__PPC) || defined(__bg__) || defined(__bgp__))
inline uint64_t cycle_time() {
#if defined(__GNUC__)
  volatile uint32_t tbl, tbu0, tbu1;
  do {
    __asm__ __volatile__ ("mftbu   %0 \n\
                           mftb    %1 \n\
                           mftbu   %2"    : "=r" (tbu0), "=r" (tbl), "=r" (tbu1));
  } while (tbu0 != tbu1);
#elif (defined(__xlc__) || defined(__xlC__))
  volatile uint64_t tbl, tbu0, tbu1;
  do {
    tbu0 = __mftbu();
    tbl  = __mftb();
    tbu1 = __mftbu();
  } while (tbu0 != tbu1);
#endif
  return (((volatile uint64_t)tbu0) << 32) | (volatile uint64_t)tbl;
}
#endif
/*------------------------------------------------------------------
 * X86-64 cycle counter
 *-----------------------------------------------------------------*/
#if defined(__x86_64__)
inline uint64_t cycle_time() {
    uint64_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return( (((uint64_t)hi) << 32) | ((uint64_t)lo) );
}
#endif
/*------------------------------------------------------------------
 * IA64 cycle counter
 *-----------------------------------------------------------------*/
#if defined(__ia64__)
#if defined(__ICC)
#include <ia64intrin.h>
inline uint64_t cycle_time() {
  return __getReg(_IA64_REG_AR_ITC);
}
#elif defined(__GNUC__)
inline uint64_t cycle_time() {
  uint64_t ret;
  __asm__ __volatile__ ("mov %0=ar.itc" : "=r"(ret));
  return ret;
}
#endif
#endif
/*------------------------------------------------------------------
 * Sparc cycle counter
 *-----------------------------------------------------------------*/
#if defined(__sparc) && defined(__GNUC__)
inline volatile uint64_t cycle_time() {
  volatile uint64_t ret;
  __asm__ volatile("rd %%tick, %0" : "=r" (ret));
  return ret;
}
#elif defined (__sparcv9) && defined(__SUNPRO_C)
extern uint64_t cycle_time();
#endif
