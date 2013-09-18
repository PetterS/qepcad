/*======================================================================
                      F <- EXPAFEQ(L)

Expand Atomic Formula with Equal relational operator.

\Input
  \parm{L} is a non-null list of 3-tuples~$(e_i,r_i,P_i)$,
           where $e_i$ is a positive $\beta$--integer,
           $r_i$ is a positive $\beta$--integer,
           and $P_i$ is a positive irreducible
           element of $Z[x_1,\ldots,x_{r_i}]$
           of positive degree in $x_{r_i}$.

\Output
  \parm{F} is a quantifier--free formula equivalent to 
           the formula~$\prod_i P_i^{e_i} = 0$ such that
           all the atomic formulas in \v{F} are normalized.
======================================================================*/
#include "qepcad.h"

Word EXPAFEQ(Word L)
{
       Word F,F_i,L_i,Lp,P_i,e_i,r_i;

Step1: /* Expand. */
       F = LIST1(OROP);
       Lp = L;
       while (Lp != NIL)
         {
         ADV(Lp,&L_i,&Lp);
         FIRST3(L_i,&e_i,&r_i,&P_i);
         F_i = LIST4(EQOP,P_i,r_i,NIL);
         F = COMP(F_i,F);
         }
       F = INV(F); goto Return;

Return: /* Prepare for return. */
       return(F);
}
