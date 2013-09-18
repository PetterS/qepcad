/*======================================================================
                      F <- EXPAFLT(L)

Expand Atomic Formula with LessThan relational operator.

\Input
  \parm{L} is a non-null list of 3-tuples~$(e_i,r_i,P_i)$,
           where $e_i$ is a positive $\beta$--integer,
           $r_i$ is a positive $\beta$--integer,
           and $P_i$ is a positive irreducible
           elemenet of $Z[x_1,\ldots,x_{r_i}]$
           of positive degree in $x_{r_i}$.

\Output
  \parm{F} is a quantifier--free formula equivalent to 
           the formula~$\prod_i P_i^{e_i} < 0$ such that
           all the atomic formulas in \v{F} are normalized.
======================================================================*/
#include "qepcad.h"

Word EXPAFLT(Word L)
{
       Word F,F1,F2,F3,F4,L1,Lp;

Step1: /* \v{L} has only one element. */
       if (LENGTH(L) > 1) goto Step2;
       L1 = FIRST(L); F = EXPAFLTS(L1); goto Return;

Step2: /* \v{L} has more than one element. */
       Lp = L; ADV(Lp,&L1,&Lp);
       F1 = EXPAFGTS(L1); F2 = EXPAFLT(Lp);
       F3 = EXPAFLTS(L1); F4 = EXPAFGT(Lp);
       F = LIST3(OROP,LIST3(ANDOP,F1,F2),LIST3(ANDOP,F3,F4));
       goto Return;

Return: /* Prepare for return. */
       return(F);
}
