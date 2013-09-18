/*======================================================================
                      t <- IPONE(r,A)

Integral polynomial one.

Inputs
  A : in Z[X1,...,Xr].
  r : a BETA-digit, r >= 0, the number of variables.

Outputs
  t : in Z,if A=1 then t=1, otherwise t=0.
======================================================================*/
#include "saclib.h"

Word IPONE(r,A)
       Word r,A;
{
       Word a,i,t;
       /* hide algorithm */

Step1: /* Dtermine. */
       t = 0;
       if (A == 0)
         goto Return;
       a = A;
       for (i = 1; i <= r; i++)
         {
         if (PDEG(a) != 0)
           goto Return;
         a = PLDCF(a);
         }
       if (a == 1)
         t = 1;

Return: /* Prepare for return. */
       return(t);
}
