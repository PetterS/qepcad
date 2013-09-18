/*======================================================================
                      B <- IPNEG(r,A)

Integral polynomial negative.

Inputs
  A : in Z[X1,...,Xr].
  r : a BETA-digit, r >= 0, the number of variables.

Outputs
  B : in Z[X1,...,Xr], B = -A.
======================================================================*/
#include "saclib.h"

Word IPNEG(r,A)
       Word r,A;
{
       Word Ap,B,a,b,e,rp;
       /* hide a,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* r=0. */
       if (r == 0)
         {
         B = INEG(A);
         goto Return;
         }

Step3: /* General case. */
       Ap = A;
       B = NIL;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 0)
           b = INEG(a);
         else
           b = IPNEG(rp,a);
         B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
