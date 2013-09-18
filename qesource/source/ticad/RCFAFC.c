/*======================================================================
                      bp <- RCFAFC(b)

Rational Coordintes From Algebraic number Field Coordinates.

\Input
  \parm{b}  is the list of elements of $Q(\alpha)$, 
            where $\alpha$ is a rational number.

\Output
  \parm{b'} is the list of elements of $Q$ such that $b = b'$.
======================================================================*/
#include "qepcad.h"

Word RCFAFC(Word b)
{
       Word b1,bh,bp,bp1;

Step1: /* Convert. */
       bp = NIL; bh = b;
       while (bh != NIL)
         { ADV(bh,&b1,&bh); bp1 = RNFAF(b1); bp = COMP(bp1,bp); }
       bp = INV(bp);
       goto Return;

Return: /* Prepare for return. */
       return(bp);
}
