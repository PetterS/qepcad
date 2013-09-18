/*======================================================================
                      B <- AFPDMV(r,M,A)

Algebraic number field polynomial derivative, main variable.

Inputs
  r : a BETA-digit, r >= 1.
  M : in Z[x], the minimal polynomial of an algebraic number alpha.
  A : in Q(alpha)[X1,...,Xr].

Outputs
  B : in Q(alpha)[X1,...,Xr]. B is the derivative of A with respect
      to its main variable.
======================================================================*/
#include "saclib.h"

Word AFPDMV(r,M,A)
       Word r,M,A;
{
       Word Ap,B,a,b,e,ep,rp;
       /* hide a,ep,rp; */

Step1: /* A = 0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* General case. */
       Ap = A;
       rp = r - 1;
       B = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         if (rp == 0)
           b = AFPROD(M,AFFINT(e),a);
         else
           b = AFPAFP(rp,M,AFFINT(e),a);
         ep = e - 1;
         if (e != 0)
           B = COMP2(b,ep,B);
         }
       while (Ap != NIL);
       B = INV(B);
       if (B == NIL)
         B = 0;

Return: /* Prepare for return. */
       return(B);
}
