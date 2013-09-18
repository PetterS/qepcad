/*======================================================================
                      B <- RPMAIP(r,A)

Rational polynomial monic associate of integral polynomial.

Inputs
  A : in Z[X1,...,Xr].
  r : a BETA-digit, r >= 1.

Outputs
  B : in Q[X1,...,Xr].  If A = 0 then B = 0.
      If A /= 0, let the integer a be the leading base coefficient of A.
      Then B = (1/a)A, a monic rational polynomial.
======================================================================*/
#include "saclib.h"

Word RPMAIP(r,A)
       Word r,A;
{
       Word B,a;

Step1: /* A = 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* A /= 0. */
       B = RPFIP(r,A);
       a = PLBCF(r,B);
       a = RNINV(a);
       B = RPRNP(r,a,B);

Return: /* Prepare for return. */
       return(B);
}
