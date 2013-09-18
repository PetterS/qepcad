/*======================================================================
                      B <- IPDMV(r,A)

Integral polynomial derivative, main variable.

Inputs
  r : BETA-digit, r >= 1, the number of variables.
  A : in Z[X1,...,Xr].     

Outputs
  B : in Z[X1,...,Xr], the derivative of A with
      respect to its main variable.
======================================================================*/
#include "saclib.h"

Word IPDMV(r,A)
       Word r,A;
{
       Word Ap,B,a,b,e,ep,rp;
       /* hide a,ep,rp; */

Step1: /* A=0. */
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
           b = IPROD(e,a);
         else
           b = IPIP(rp,e,a);
         ep = e - 1;
         if (e != 0)
           B = COMP2(b,ep,B);
         }
       while (!(Ap == NIL));
       B = INV(B);
       if (B == NIL)
         B = 0;

Return: /* Prepare for return. */
       return(B);
}
