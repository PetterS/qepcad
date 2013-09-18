/*======================================================================
                      Lt <- SIGNL(c,L)

Signs of algebraic Leading coefficients.

\Input
  \parm{c} is a non-root cell.
  \parm{L} is a list $(L_1,\ldots,L_m)$ of
           elements of $Q(\alpha)$.

\Output
  \parm{L~} is the list $(s1,\ldots,sm)$ where $s_i = sign(L_i)$.
======================================================================*/
#include "qepcad.h"

Word SIGNL(Word c, Word L)
{
       Word I,L1,Lp,Lt,M,s,s1;
       /* hide s1; */

Step1: /* Compute. */
       s = LELTI(c,SAMPLE); FIRST2(s,&M,&I);
       Lp = L; Lt = NIL;
       while (Lp != NIL)
         {
         ADV(Lp,&L1,&Lp);
         s1 = AFSIGN(M,I,L1);
         Lt = COMP(s1,Lt);
         }
       Lt = INV(Lt);
       goto Return;

Return: /* Prepare for return. */
       return(Lt);
}
