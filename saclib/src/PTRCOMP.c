/*======================================================================
                      M <- PTRCOMP(a,L)

Composition.

Inputs
  a : a pointer (i.e. Word*).
  L : list.

Outputs  
  M : the composition of a and L.
======================================================================*/
#include "saclib.h"

Word PTRCOMP(p,L)
     Word *p, L;
{
#if __WORDSIZE == 64
  unsigned long long t = (unsigned long long)p;
  Word a,b,c,d;
  a = (Word)(t & BETA1);
  t = t >> BETALENGTH;
  b = (Word)(t & BETA1);
  t = t >> BETALENGTH;
  c = (Word)(t & BETA1);
  t = t >> BETALENGTH;
  d = (Word)(t & BETA1);
  return COMP4(d,c,b,a,L);

#else /* Assumes 32-bit pointers. */
  unsigned int t = (unsigned int)p;
  Word a,b,c,d;
  a = (Word)(t & BETA1);
  t = t >> BETALENGTH;
  b = (Word)(t & BETA1);
  return COMP2(b,a,L);

#endif
}
