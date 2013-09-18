/*======================================================================
                      b <- IPSUMN(r,A)

Integral polynomial sum norm.

Inputs
  A  : in Z[X1,...,Xr].
  r  : a BETA-digit, r >= 0, the number of variables.

Outputs
  b  : in Z, the sum norm of A.
======================================================================*/
#include "saclib.h"

Word IPSUMN(r,A)
       Word r,A;
{
       Word Ap,a1,b,b1,e1,rp;
       /* hide a1,e1,rp; */

Step1: /* r=0. */
       if (r == 0)
         {
         b = IABSF(A);
         goto Return;
         }

Step2: /* r > 0. */
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
           b1 = IPSUMN(rp,a1);
         b = ISUM(b,b1);
         }
       while (Ap != NIL);

Return: /* Prepare for return. */
       return(b);
}
