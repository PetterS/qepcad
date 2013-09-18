/*======================================================================
                      B <- PUFP(r,A)

Polynomial, univariate, from polynomial.

Inputs
  A : in R[X1,...,Xr], r ring.
  r : a BETA-digit, r >= 0.

Outputs
  B : in R[X], B(X) =  A(0,...,0,X).
======================================================================*/
#include "saclib.h"

Word PUFP(r,A)
       Word r,A;
{
       Word Ap,B,a,b,e,rp;
       /* hide a,e,rp; */

Step1: /* r=0 or A=0. */
       if (r == 0 || A == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* General case. */
       rp = r - 1;
       B = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         b = PTBCF(rp,a);
         if (b != 0)
           B = COMP2(b,e,B);
         }
       if (B == NIL)
         B = 0;
       else
         B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
