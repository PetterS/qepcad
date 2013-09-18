/*======================================================================
                      B <- AFPFIP(r,A)

Algebraic number field polynomial from integral polynomial.  

Inputs
  r : a BETA-digit, r >= 1.
  A : in Z[X1,...,Xr].  

Outputs
  B :  in Q(alpha)[X1,...,Xr], B = A.
======================================================================*/
#include "saclib.h"

Word AFPFIP(r,A)
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
         B = AFFINT(A);
         goto Return;
         }

Step3: /* Recursion on r. */
       B = NIL;
       Ap = A;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         b = AFPFIP(rp,a);
         B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);
       goto Return;

Return: /* Prepare for return. */
       return(B);
}
