/*======================================================================
                      PSIMREP(r,P; rs,Ps)

Polynomial Simplification of Representation.

\Input
  \parm{r} is a non-negative $\beta$--integer.
  \parm{P} is an element of $Z[x_1,\ldots,x_r]$.
  
\Output
  \parm{r*} is the level of the polynomial~\v{P}.
  \parm{P*} is an element of $Z[x_1,\ldots,x_{\v{r*}}]$ such that
            $\v{P*} = \v{P}$.
======================================================================*/
#include "qepcad.h"

void PSIMREP(Word r, Word P, Word *rs_, Word *Ps_)
{
       Word Ps,rs;
       /* hide rs; */

Step1: /* $\v{P} = 0$. */
       if (P == 0) { rs = 0; Ps = 0; goto Return; }

Step2: /* Simplify. */
       Ps = P; rs = r;
       do
         {
         if (rs == 0) goto Return;
         if (PDEG(Ps) > 0) goto Return;
         Ps = PLDCF(Ps);
         rs = rs - 1;
         } while (1);

Return: /* Prepare for return. */
       *rs_ = rs;
       *Ps_ = Ps;
       return;
}
