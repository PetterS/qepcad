/*======================================================================
                      B <- MPEVAL(r,m,A,i,a)

Modular polynomial evaluation.

Inputs
  A : in Z/(m)[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.
  m : a BETA-digit.
  a : in Z/(m).
  i : a BETA-digit, 1 <= i <= r.

Outputs
  B : in Z/(m)[X1,...,X_{i-1},X_{i+1},...,Xr],
      B(X1,...,X_{i-1},X_{i+1},...,Xr) =
      A(X1,...,X_{i-1},a,X_{i+1},...,Xr)
======================================================================*/
#include "saclib.h"

Word MPEVAL(r,m,A,i,a)
       Word r,m,A,i,a;
{
       Word A1,Ap,B,B1,e1,rp;
       /* hide A1,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* i=r. */
       if (i == r)
         {
         B = MPEMV(r,m,A,a);
         goto Return;
         }

Step3: /* i < r. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do
         {
         ADV2(Ap,&e1,&A1,&Ap);
         B1 = MPEVAL(rp,m,A1,i,a);
         if (B1 != 0)
           B = COMP2(B1,e1,B);
         }
       while (!(Ap == NIL));
       if (B == NIL)
         B = 0;
       else
         B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
