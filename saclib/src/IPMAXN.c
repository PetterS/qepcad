/*======================================================================
                      b <- IPMAXN(r,A)

Integral polynomial maximum norm.

Inputs
  A : in Z[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.

Outputs
  b : in Z, the maximum norm of A.
======================================================================*/
#include "saclib.h"

Word IPMAXN(r,A)
       Word r,A;
{
       Word Ap,a1,b,b1,e1,rp;
       /* hide a1,e1,rp; */

Step1: /* Compute. */
       b = 0;
       if (A == 0)
         goto Return;
       Ap = A;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e1,&a1,&Ap);
         if (rp == 0)
           b1 = IABSF(a1);
         else
           b1 = IPMAXN(rp,a1);
         b = IMAX(b,b1);
         }
       while (Ap != NIL);
       goto Return;

Return: /* Prepare for return. */
       return(b);
}
