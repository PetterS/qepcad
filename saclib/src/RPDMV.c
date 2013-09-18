/*======================================================================
                      B <- RPDMV(r,A)

Rational polynomial derivative, main variable.

Inputs
  A : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 1.

Outputs
  B : in Q[X1,...,Xr], the derivative of A with respect to    
      its main variable.
======================================================================*/
#include "saclib.h"

Word RPDMV(r,A)
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
           b = RNPROD(RNINT(e),a);
         else
           b = RPRNP(rp,RNINT(e),a);
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
