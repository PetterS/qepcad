/*======================================================================
                      c <- AFDIF(a,b)

Algebraic number field element difference.

Inputs
 a, b : in Q(alpha) for some algebraic number alpha.

Outputs
    c : in Q(alpha). C = a - b.
======================================================================*/
#include "saclib.h"

Word AFDIF(a,b)
       Word a,b;
{
       Word bp,c;

Step1: /* Compute the difference. */
       bp = AFNEG(b);
       c = AFSUM(a,bp);

Return: /* Prepare for return. */
       return(c);
}
