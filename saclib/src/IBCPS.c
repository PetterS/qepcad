/*======================================================================
                      A <- IBCPS(n,k)

Integer binomial coefficient partial sum.

Inputs
  n,k : BETA-digits, 0 <= k <= n.

Outputs
  A : the sum (n choose 0) + . . . + (n choose k).
======================================================================*/
#include "saclib.h"

Word IBCPS(n,k)
       Word n,k;
{
       Word A,B,j;
       /* hide j; */

Step1: /* Compute. */
       A = 1;
       B = 1;
       for (j = 0; j <= k - 1; j++)
         {
         B = IBCIND(B,n,j);
         A = ISUM(A,B);
         }

Return: /* Prepare for return. */
       return(A);
}
