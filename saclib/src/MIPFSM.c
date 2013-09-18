/*======================================================================
                      B <- MIPFSM(r,M,A)

Modular integral polynomial from symmetric modular.

Inputs
  M : in Z, M > 0.
  A : in Z'/(M)[X1,...,Xr]
  r : a BETA-digit, r >= 0, the number of variables.

Outputs
  B : in Z/(M)[X1,...,Xr], with B = A (modulo M).
======================================================================*/
#include "saclib.h"

Word MIPFSM(r,M,A)
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
         if (ISIGNF(A) < 0)
           B = ISUM(M,A);
         else
           B = A;
         goto Return;
         }

Step3: /* General case. */
       Ap = A;
       B = NIL;
       rp = r - 1;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         b = MIPFSM(rp,M,a);
         B = COMP2(b,e,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
