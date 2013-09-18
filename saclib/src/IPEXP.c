/*======================================================================
                      B <- IPEXP(r,A,n)

Integral polynomial exponentiation.

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[X1,...,Zr].
  n : a BETA-digit, n >= 0.

Outputs
  B : in Z[X1,...,Zr], B = A^n.
======================================================================*/
#include "saclib.h"

Word IPEXP(r,A,n)
       Word r,A,n;
{
       Word B,i;
       /* hide i; */

Step1: /* n=0. */
       if (n == 0)
         {
         B = PINV(0,1,r);
         goto Return;
         }

Step2: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step3: /* General case. */
       B = A;
       for (i = 1; i <= n - 1; i++)
         {
         B = IPPROD(r,B,A);
         }

Return: /* Prepare for return. */
       return(B);
}
