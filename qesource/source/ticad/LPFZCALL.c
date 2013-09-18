/*======================================================================
                 L = LPFZCALL(c,P,D)
List of projection factors which are zero on cell - All lower levels.

Inputs
  c : A qepcad cell data structure.
  P : The qepcad data structure for the projection factors.
  D : the qepcad pcad data structure containing C

Outputs
  L : A list of projection factors whose level is the same or lower
  than C, and which are identically zero in C.  
======================================================================*/
#include "qepcad.h"

Word LPFZCALL(Word c, Word P, Word D)
{
  Word I,d,L;
  
  /* I := c's index, d := c's ancestor, L := the list we're building. */
  I = LELTI(c,INDX);
  d = D;
  L = NIL;
  
  /* Loop over each ancestor of c and find zero p.f.'s at that level. */
  do {
    d = LELTI(LELTI(d,CHILD),FIRST(I));
    I = RED(I);
    L = CCONC(L,LPFZC(d,P));    
  }while (I != NIL);
  L = CINV(L);

  return L;
}


