/*======================================================================
                      B <- IPHDMV(r,A,k)

Integral polynomial higher derivative, main variable.

Inputs 
  r : a BETA-digit, r >= 1, the number of variables.
  A : in Z[X1,...,Xr].
  k : BETA-digit, k >= 0.

Outputs
  B : in Z[X1,...,Xr], the k-th derivative of A
       with respect to its main variable.
======================================================================*/
#include "saclib.h"

Word IPHDMV(r,A,k)
       Word r,A,k;
{
       Word B,i;
       /* hide i; */

Step1: /* Compute. */
       B = A;
       i = k;
       while (i > 0 && B != 0)
         {
         B = IPDMV(r,B);
         i = i - 1;
         }

Return: /* Prepare for return. */
       return(B);
}
