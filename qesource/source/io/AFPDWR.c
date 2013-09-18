/*======================================================================
                      AFPDWR(r,A,V,N)

Algebraic number field polynomial distributive write. 

\Input
  \parm{r} is a non-negative $\beta$--integer.
  \parm{A} is an element of~$Q(\alpha)[x_1,\ldots,x_r]$, 
           written out to the output stream.
  \parm{V} is a list of at least $r$ distinct variables.
           First $r$ variables in $V$ are used. 
  \parm{N} is the variable name for $\alpha$.
======================================================================*/
#include "qepcad.h"

void AFPDWR(Word r, Word A, Word V, Word N)
{
       Word Ap,Vp,rp;
       /* hide rp; */

Step1: /* Convert the representation. */
       rp = r + 1;
       Ap = AFPICR(r,A);
       Vp = CONC(LIST1(N),V);

Step2: /* Write it out. */
       RPDWRITE(rp,Ap,Vp);

Return: /* Prepare for return. */
       return;
}
