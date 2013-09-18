/*

Set mark to reflect formula.

D : an EPCAD
F : a formula
P : projection factor set for D

Note: assumptions are carried over into this process!
 */
#include "extlang.h"

void SETMARK2FMA(Word D, Word F, Word P)
{
  Word L,c;
  L = LELTI(D,SC_CDTV);
  if (ISLIST(L)) {
    SLELTI(D,SC_TMPM,UNDET);
    while(L != NIL) {
      ADV(L,&c,&L);
      SETMARK2FMA(c,F,P); } }
  else {
    if (L == NA)
      SLELTI(D,SC_TMPM,NA);
    else
      SLELTI(D,SC_TMPM,FMACELLEVAL(F,D,P));
  }
  return;
}
