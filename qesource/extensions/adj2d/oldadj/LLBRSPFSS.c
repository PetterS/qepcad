/*

List of logarithmic binary rational sample points from sectors in stack.

*/
#include "oldadj.h"

Word LLBRSPFSS(Word c)
{
  Word L,S,C;
  L = NIL;
  S = LELTI(c,CHILD);
  while(S != NIL) {
    C = FIRST(S);
    S = RED(S);
    if (S != NIL) S = RED(S);
    L = COMP(RNLBRN(SPRLC(C)),L); }
  L = INV(L);
  return L;
}
