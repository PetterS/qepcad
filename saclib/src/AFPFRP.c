/*======================================================================
                      B <- AFPFRP(r,A)

Algebraic number field polynomial from rational polynomial.  

Inputs
  r : a BETA-digit, r >= 1.
  A : in Q[X1,...,Xr].

Outputs
  B : in Q(alpha)[X1,...,Xr], B = A.
======================================================================*/
#include "saclib.h"

Word AFPFRP(r,A)
       Word r,A;
{
       Word Ap,B,a,b,e,rp;
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
         B = AFFRN(A);
         goto Return;
         }

Step3: /* Recursion on r. */
       B = NIL;
       Ap = A;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         b = AFPFRP(rp,a);
         B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
