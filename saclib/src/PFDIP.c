/*======================================================================
                      B <- PFDIP(r,A)

Polynomial from distributive polynomial.

Inputs
  A : in R[X1,...,Xr], distributive representation.
  R a BETA-digit, r >= 0.

Outputs
  B : in R[X1,...,Xr], the result of converting A to recursive 
      representation.
======================================================================*/
#include "saclib.h"

Word PFDIP(r,A)
       Word r,A;
{
       Word A1,Ap,B,B1,E1,a1,e,e1,rp;
       /* hide E1,a1,e,e1,rp; */

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
         ADV2(Ap,&a1,&E1,&Ap);
         e1 = FIRST(E1);
         B = COMP2(a1,e1,B);
         }
       while (!(Ap == NIL));
       B = INV(B);
       goto Return;

Step3: /* Recursion. */
       do
         {
         e = DIPDEG(r,Ap);
         A1 = NIL;
         do
           {
           e1 = DIPDEG(r,Ap);
           if (e1 == e)
             {
             ADV2(Ap,&a1,&E1,&Ap);
             E1 = RED(E1);
             A1 = COMP2(E1,a1,A1);
             }
           }
         while (!(e1 != e || Ap == NIL));
         A1 = INV(A1);
         B1 = PFDIP(rp,A1);
         B = COMP2(B1,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
