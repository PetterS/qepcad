/*======================================================================
                          t <- PFPRDQ(P)

Projection factor parentage includes resultant or discrimnant query?

Input:
P : a QEPCAD projection factor

Output:

t : TRUE if P has a derivation as a factor of a resultant or 
    discriminant, and FALSE otherwise.

======================================================================*/
#include "qepcad.h"

Word PFPRDQ(Word P)
{
  Word L;  

  for(L = LELTI(P,PO_PARENT); L != NIL; L = RED(L)) {
    if (PPPRDQ(THIRD(FIRST(L))))
      return TRUE; }
  return FALSE;
}
