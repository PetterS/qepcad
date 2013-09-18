/*======================================================================
                      B <- DIPFP(r,A)

Distributive polynomial from polynomial.

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  A : in R[X1,...Xr], where R is any ring.

Outputs
  B : in R[X1,...Xr], the result of converting A
      from recursive to distributive representation.
======================================================================*/
#include "saclib.h"

Word DIPFP(r,A)
       Word r,A;
{
       Word A1,Ap,B,B1,E1,a1,b1,e1,rp;
       /* hide rp; */

Step1: /* r=0 or A=0. */
       if (r == 0 || A == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* r=1. */
       B = NIL;
       Ap = A;
       rp = r - 1;
       if (rp > 0)
         goto Step3;
       do
         {
         ADV2(Ap,&e1,&a1,&Ap);
         E1 = LIST1(e1);
         B = COMP2(E1,a1,B);
         }
       while (!(Ap == NIL));
       B = INV(B);
       goto Return;

Step3: /* Recursion. */
       do
         {
         ADV2(Ap,&e1,&A1,&Ap);
         B1 = DIPFP(rp,A1);
         do
           {
           ADV2(B1,&b1,&E1,&B1);
           E1 = COMP(e1,E1);
           B = COMP2(E1,b1,B);
           }
         while (!(B1 == NIL));
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
