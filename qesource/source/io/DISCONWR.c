/*======================================================================
                      DISCONWR(V,F)

Disjunction of Conjunctions Write.

\Input
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a disjunction of conjunctions of atomic formulas
            with variables in $V$,
            written out to the output strem.
======================================================================*/
#include "qepcad.h"

void DISCONWR(Word V, Word F)
{
       Word C,Fp;

Step1: /* Write. */
       Fp = RED(F);
       ADV(Fp,&C,&Fp); SWRITE("   "); CONWR(V,C); SWRITE("\n");
       while (Fp != NIL)
         { ADV(Fp,&C,&Fp); SWRITE("\\/ "); CONWR(V,C); SWRITE("\n"); }

Return: /* Prepare for return. */
       return;
}
