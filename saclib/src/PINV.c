/*======================================================================
                      B <- PINV(r,A,k)

Polynomial introduction of new variables.

Inputs
  A : in R[X1,...,Xr], R ring.
  r : a BETA-digit, r >= 0.
  k : a BETA-digit, k >= 0.

Outputs
  B : in R[Y1,...,Yk,X1,...,Xr], B(Y1,...,Yk,X1,...,Xr) =
      = A(X1,...,Xr).
======================================================================*/
#include "saclib.h"

Word PINV(r,A,k)
       Word r,A,k;
{
       Word A1,Ap,B,B1,e1,i,rp;
       /* hide i,rp; */

Step1: /* A=0 or k=0. */
       if (A == 0 || k == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* r=0. */
       if (r == 0)
         {
         B = A;
         for (i = 1; i <= k; i++)
           B = LIST2(0,B);
         goto Return;
         }

Step3: /* r > 0. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do
         {
         ADV2(Ap,&e1,&A1,&Ap);
         B1 = PINV(rp,A1,k);
         B = COMP2(B1,e1,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
