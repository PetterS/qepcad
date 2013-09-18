/*======================================================================
                      B <- IPFRP(r,A)

Integral polynomial from rational polynomial. 

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Q[X1,...,Xr], The base coefficients of A
      are integers.

Outputs
  B : in Z[X1,...,Xr], B is A converted to integral
      polynomial representation.
======================================================================*/
#include "saclib.h"

Word IPFRP(r,A)
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
         B = FIRST(A);
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
           b = FIRST(a);
         else
           b = IPFRP(rp,a);
         B = COMP2(b,e,B);
         }
       while (As != NIL);
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
