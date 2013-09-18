/*======================================================================
                      ap <- RNFAF(a)

Rational Number From Algebraic number Field element.

\Input
  \parm{a} is an algebraic number field element which is again
           rational.

\Output
  \parm{a'} is a rational number such that $a' = a$.
======================================================================*/
#include "qepcad.h"

Word RNFAF(Word a)
{
       Word ap;

Step1: /* Convert. */
       if (a == 0) ap = 0; else ap = FIRST(a);

Return: /* Prepare for return. */
       return(ap);
}
