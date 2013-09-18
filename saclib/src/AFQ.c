/*======================================================================
                      c <- AFQ(M,a,b)

Algebraic number field quotient.

Inputs
    M : in Z[x], the minimal polynomial for an algebraic number alpha.  
  a,b : in Q(alpha), b not zero.

Outputs
    c : in Q(alpha), c = a/b.
======================================================================*/
#include "saclib.h"

Word AFQ(M,a,b)
       Word M,a,b;
{
       Word c;
       /* hide c; */

Step1: /* Compute the quotient. */
       if (a == 0)
         c = 0;
       else
         c = AFPROD(M,a,AFINV(M,b));

Return: /* Prepare for return. */
       return(c);
}
