/*
                     t <- FMADMQ(F,C,k,P)

ForMulA defines marks query.

F : a formula
C : a list of cells
k : a level --- any cell k-levels above C is taken to be a leaf,
    even if it actually has children.
P : the projection factor set defining C's signiture

t : 1 if F does define the marks for the CAD of C x R^k, 0 otherwise.

*/

#include "extlang.h"

Word FMADMQ(Word F,Word C,Word k,Word P)
{
  Word t,L;
  t = 1;
  for(L = C; t && L != NIL; L = RED(L))
    t = singleFMADMQ(F,FIRST(L),k,P);
  return t;
}

Word singleFMADMQ(Word F,Word C,Word k,Word P)
{
  Word t,L;

  if (k == 0 || !ISLIST(LELTI(C,SC_CDTV)))
    t = (FMACELLEVAL(F,C,P) == LELTI(C,SC_TMPM));
  else {
    L = LELTI(C,SC_CDTV);
    for(t = 1; t && L != NIL; L = RED(L))
      t = singleFMADMQ(F,FIRST(L),k-1,P); }
  return t;

}
