/*======================================================================
                      CONWR(V,C)

Conjunction Write.

\Input
   \parm{V} is a non-null list of distinct variables.
   \parm{C} is a conjunction of atomic formulas
            with variables in $V$,
            written out to the output strem.
======================================================================*/
#include "qepcad.h"

void CONWR(Word V, Word C)
{
       Word A,Cp;

Step1: /* Write. */
       Cp = RED(C);
       ADV(Cp,&A,&Cp); ATOMFWR(V,A);
       while (Cp != NIL)
         { ADV(Cp,&A,&Cp); SWRITE(" /\\ "); ATOMFWR(V,A); }

Return: /* Prepare for return. */
       return;
}
