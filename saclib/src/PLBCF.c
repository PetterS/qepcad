/*======================================================================
                      a <- PLBCF(r,A)

Polynomial leading base coefficient.

Inputs
  A : in R[X1,...,Xr], R a ring.
  r : a BETA-digit, r >= 0.

Outputs
  a : in R, the leading base coefficient of A.
======================================================================*/
#include "saclib.h"

Word PLBCF(r,A)
       Word r,A;
{
       Word a,i;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         a = 0;
       else
         {
         a = A;
         for (i = 1; i <= r; i++)
           {
           a = PLDCF(a);
           }
         }

Return: /* Prepare for return. */
       return(a);
}
