/*======================================================================
                      B <- MPUP(r,m,c,A)

Modular polynomial univariate product.

Inputs
  A : in Z/(m)[X1,...,Xr].
  c : in Z/(m)[X1].
  r : a BETA-digit, r >= 1.
  m : a BETA-digit, m > 0.

Outputs
  B :  in Z/(m)[X1,...,Xr], B(X1,...,Xr) = c(X1) *  A(X1,...,Xr).
======================================================================*/
#include "saclib.h"

Word MPUP(r,m,c,A)
       Word r,m,c,A;
{
       Word Ap,B,a,b,e,rp;
       /* hide a,rp; */

Step1: /* c=0 or A=0. */
       if (c == 0 || A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* r=1. */
       if (r == 1)
         {
         B = MPPROD(r,m,c,A);
         goto Return;
         }

Step3: /* General case. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         b = MPUP(rp,m,c,a);
         if (b != 0)
           B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       if (B == NIL)
         B = 0;
       else
         B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
