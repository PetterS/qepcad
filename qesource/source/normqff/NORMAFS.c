/*======================================================================
                      F <- NORMAFS(Fh)

Normalize Atomic Formulas.

\Input
  \parm{F^} is a quantifier--free formula.

\Output
  \parm{F} is a quantifier--free formula equivalent to \v{F^}
           such that all the atomic formulas in \v{F} are normalized.
======================================================================*/
#include "qepcad.h"

Word NORMAFS(Word Fh)
{
       Word F,F_i,Fh_i,Fhp,T;

Step1: /* Atomic formula. */
       if (ISATOMF(Fh)) { F = NORMAF(Fh); goto Return; }

Step3: /* Non-atomic formula. */
       Fhp = Fh; ADV(Fhp,&T,&Fhp); F = LIST1(T);
       while (Fhp != NIL)
         { ADV(Fhp,&Fh_i,&Fhp); F_i = NORMAFS(Fh_i); F = COMP(F_i,F); }
       F = INV(F); goto Return;

Return: /* Prepare for return. */
       return(F);
}
