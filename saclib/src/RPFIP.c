/*======================================================================
                      B <- RPFIP(r,A)

Rational polynomial from integral polynomial.

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[X1,...,Xr].

Outputs
  B : in Q[X1,...,Xr], B is A converted to rational
      polynomial representation.
======================================================================*/
#include "saclib.h"

Word RPFIP(r,A)
       Word r,A;
{
       Word As,B,a,b,e,rp;
       /* hide a,rp; */

Step1: /* A = 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* r = 0. */
       if (r == 0)
         {
         B = RNINT(A);
         goto Return;
         }

Step3: /* r > 0. */
       As = A;
       rp = r - 1;
       B = NIL;
       do
         {
         ADV2(As,&e,&a,&As);
         if (rp == 0)
           b = RNINT(a);
         else
           b = RPFIP(rp,a);
         B = COMP2(b,e,B);
         }
       while (As != NIL);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
