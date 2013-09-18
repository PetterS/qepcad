/*======================================================================
                      PTRADV(L; a,Lp)

Advance. (assuming the "first" element of L is a pointer)

Inputs
  L  : a non-empty list.

Outputs
  a  : PTRFIRST(L).
  Lp : reductum of L (assuming the "first" element of L is a pointer).
======================================================================*/
#include "saclib.h"

void PTRADV(L,a_,Lp_)
     Word L, **a_, *Lp_;
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
  *Lp_ = Lp;
  *a_ = (Word*)res;
#else /* Assumes 32-bit pointers. */
  Word Lp, t;
  unsigned int res = 0;
  ADV(L,&t,&Lp);
  res = t;
  ADV(Lp,&t,&Lp);
  res = (res << BETALENGTH) | t;
  *Lp_ = Lp;
  *a_ = (Word*)res;
#endif
}
