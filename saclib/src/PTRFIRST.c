/*======================================================================
                      a <- PTRFIRST(L)

First. (assuming the "first" element of L is a pointer)

Inputs
  L  : list of length 2 or more.

Outputs
  a  : the first element of L (assuming "first" element is a pointer).
======================================================================*/
#include "saclib.h"

Word* PTRFIRST(L)
        Word L;
{
#if __WORDSIZE == 64

  Word Lp, t;
  unsigned long long res = 0;
  ADV(L,&t,&Lp);
  res = t;
  ADV(Lp,&t,&Lp);
  res = (res << BETALENGTH) | t;
  ADV(Lp,&t,&Lp);
  res = (res << BETALENGTH) | t;
  ADV(Lp,&t,&Lp);
  res = (res << BETALENGTH) | t;
  return (Word*)res;

#else /* Assumes 32-bit pointers. */

  Word Lp, t;
  unsigned int res = 0;
  ADV(L,&t,&Lp);
  res = t;
  ADV(Lp,&t,&Lp);
  res = (res << BETALENGTH) | t;
  return (Word*)res;

#endif
}  
