/*======================================================================
                          t <- PPPRDQ(P)

Projection polynomial parentage includes resultant or discrimnant query?

Input:
P : a QEPCAD projection polynomial

Output:

t : TRUE if P has a derivation as a resultant or discriminant, and
    FALSE otherwise.

======================================================================*/
#include "qepcad.h"

Word PPPRDQ(Word P)
{
  Word L, T;

  for(L = LELTI(P,PO_PARENT); L != NIL; L = RED(L)) {
    T = FIRST(FIRST(L));
    if (T == PO_RES || T == PO_DIS)
      return TRUE; }
  return FALSE;
}
