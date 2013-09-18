/*======================================================================
                      A <- IFACTL(n)

Integer factorial.

Inputs
  n : a non-negative BETA-digit.

Outputs
  A : n!.
======================================================================*/
#include "saclib.h"

Word IFACTL(n)
       Word n;
{
       Word A,D,k;
       /* hide D,k; */

Step1: /* Compute. */
       A = 1;
       D = 1;
       for (k = 2; k <= n; k++)
         {
         if (k <= BETA / D)
           D = D * k;
         else
           {
           A = IDPR(A,D);
           D = k;
           }
         }
       if (A == 1)
         A = D;
       else
         A = IDPR(A,D);

Return: /* Prepare for return. */
       return(A);
}
