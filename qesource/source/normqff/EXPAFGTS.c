/*======================================================================
                      A <- EXPAFGTS(L)

Expand Atomic Formula with GreaterThan relational operator, Subalgorithm.

\Input
  \parm{L} is a 3-tuples~$(e,r,P)$,
           where $e$ is a positive $\beta$--integer,
           $r$ is a positive $\beta$--integer,
           and $P$ is a positive irreducible
           elemenet of $Z[x_1,\ldots,x_r]$
           of positive degree in $x_r$.

\Output
  \parm{A} is an atomic formula equivalent to 
           the formula~$P^e > 0$ such that
           the polynomial in  \v{A} is  \v{P}.
======================================================================*/
#include "qepcad.h"

Word EXPAFGTS(Word L)
{
       Word A,P,e,r;

Step1: /* Do it. */
       FIRST3(L,&e,&r,&P);
       if (EVEN(e))
         A = LIST4(NEOP,P,r,NIL);
       else
         A = LIST4(GTOP,P,r,NIL);
       goto Return;

Return: /* Prepare for return. */
       return(A);
}
