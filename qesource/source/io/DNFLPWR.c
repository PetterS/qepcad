/*======================================================================
                      DNFLPWR(N,V,F)

Disjunctive Normal Form Label and Polynomials Write.

\Input
   \parm{N} is a non-null list of characters used as the name of the labels.
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a disjunctive normal form with variables in $V$,
            written out in labels to the output strem along with
            the polynomials occurring in the formula.
======================================================================*/
#include "qepcad.h"

void DNFLPWR(Word N, Word V, Word F)
{
       Word A,I,L,L1,r;

Step1: /* Write out $F$ in labels. */
       DNFLWR(N,V,F);

Step2: /* Get the polynomials occurring in $F$. */
       PQFF(F,NIL,&L);

Step3: /* Write out the polynomials. */
       SWRITE("\n\nwhere\n");
       while (L != NIL)
         {
         ADV(L,&L1,&L);
         FIRST3(L1,&A,&r,&I);
         LABELWR(LFS("P"),I); SWRITE(" = "); IPDWRITE(r,A,V); SWRITE("\n");
         }
       goto Return;

Return: /* Prepare for return. */
       return;
}
