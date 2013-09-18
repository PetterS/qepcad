/*======================================================================
                      ATOMFLWR(N,V,A)

Atomic Formula Label Write.

\Input
   \parm{N} is a non-null list of characters used as the name of the label.
   \parm{V} is a non-null list of distinct variables.
   \parm{A} is an atomic formula with variables in $V$,
            written out in a label to the output strem.
======================================================================*/
#include "qepcad.h"

void ATOMFLWR(Word N, Word V, Word A)
{
       Word I,P,T,r;

Step1: /* Write. */
       FIRST4(A,&T,&P,&r,&I);
       LABELWR(N,I);
       SWRITE(" "); RLOPWR(T); SWRITE(" 0");

Return: /* Prepare for return. */
       return;
}
