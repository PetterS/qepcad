/*======================================================================
                      B <- IEXP(A,n)

Integer exponentiation.

Inputs
  A  : in Z.
  n  : non-negative BETA-digit.

Outputs
  B  : A^n.
======================================================================*/
#include "saclib.h"

Word IEXP(A,n)
       Word A,n;
{
       Word B,k;
       /* hide k; */

Step1: /* n less than or equal to 1. */
       if (n == 0)
         {
         B = 1;
         goto Return;
         }
       if (n == 1)
         {
         B = A;
         goto Return;
         }

Step2: /* Recursion. */
       k = n / 2;
       B = IEXP(A,k);
       B = IPROD(B,B);
       if (n > 2 * k)
         B = IPROD(B,A);

Return: /* Prepare for return. */
       return(B);
}
