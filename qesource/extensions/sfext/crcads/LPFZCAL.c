/*======================================================================
                     L <- LPFZCAL(D,C,P)

List of projection factors which are zero on cell - All Levels!

Inputs
  D : A qepcad CAD data structure.
  C : A qepcad cell data structure, of level > 0
  P : The qepcad data structure for the projection factors.

Outputs
  L : A list of projection factors whose level is the same as C or 
      lower, and
      which are identically zero in C.  These projection factors are
      ordered in the list by decreasing index.
======================================================================*/
#include "qepcad.h"

Word LPFZCAL(Word D, Word C, Word P)
{
  Word I,cp,L,Lp,i;

  I = LELTI(C,INDX);
  cp = D;
  L = NIL;
  do {
    ADV(I,&i,&I);
    cp = LELTI(LELTI(cp,CHILD),i);
    for(Lp = LPFZC(cp,P); Lp != NIL; Lp = RED(Lp))
      L = COMP(FIRST(Lp),L);
  } while(I != NIL);
  L = CINV(L);

Return: /* Prepare to return. */
      return (L);

}
