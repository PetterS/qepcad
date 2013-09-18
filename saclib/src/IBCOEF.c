/*======================================================================
                      A <- IBCOEF(n,k)

Integer binomial coefficient.

Inputs
  n,k : BETA-digits with 0 <= k <= n.

Outputs
  A : the binomial coefficient (n choose k).
======================================================================*/
#include "saclib.h"

Word IBCOEF(n,k)
       Word n,k;
{
       Word A,j,kp;
       /* hide j,kp; */

Step1: /* Compute. */
       kp = MIN(k,n - k);
       A = 1;
       for (j = 0; j <= kp - 1; j++)
         A = IBCIND(A,n,j);

Return: /* Prepare for return. */
       return(A);
}
