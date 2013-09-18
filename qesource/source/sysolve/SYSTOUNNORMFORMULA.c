/*======================================================================
                      F <- SYSTOUNNORMFORMULA(r,L)

System to unnormalized formula

Inputs:
   r : a BDigit
   L : a list of r-variate SACLIB polynomials

Ouputs:
   F : an unnormalized QEPCAD formula for the system
======================================================================*/
#include "qepcad.h"

Word SYSTOUNNORMFORMULA(BDigit r, Word L)
{
  Word F, Lp;
  F = NIL;
  for(Lp = L; Lp != NIL; Lp = RED(Lp))
    F = COMP(LIST4(EQOP,FIRST(Lp),r,NIL),F);
  F = COMP(ANDOP,F);
  return F;
}

