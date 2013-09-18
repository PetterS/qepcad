/*======================================================================
                      B <- SMFMIP(r,M,A)

Symmetric modular from modular integral polynomial.

Inputs
  M : in Z, M > 0.
  A : in Z/(M)[X1,...,Xr].
  r : a BETA-digit, r >= 0.

Outputs
  B : in Z'/(M)[X1,...,Xr] with B=A (modulo M).
======================================================================*/
#include "saclib.h"

Word SMFMIP(r,M,A)
       Word r,M,A;
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
         B = SMFMI(M,A);
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
           b = SMFMI(M,a);
         else
           b = SMFMIP(rp,M,a);
         B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
