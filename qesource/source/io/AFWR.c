/*======================================================================
                      AFWR(A,a)

Algebraic number field element write. 

\Input
  \parm{A} is an element of~$Q(\alpha)$
           written out to the output stream.
  \parm{a} is the variable name for $\alpha$.
======================================================================*/
#include "qepcad.h"

void AFWR(Word A, Word a)
{
       Word Ap;

Step1: /* Convert the representation. */
       Ap = AFICR(A);

Step2: /* Write it out. */
       RPDWRITE(1,Ap,LIST1(a));

Return: /* Prepare for return. */
       return;
}
