/*======================================================================
                      B <- RPIMV(r,A)

Rational polynomial integration, main variable.

Inputs
  A : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 1.

Outputs
  B : in Q[X1,...,Xr], the integral of A with respect to its main variable.
      The constant of integration is 0.
======================================================================*/
#include "saclib.h"

Word RPIMV(r,A)
       Word r,A;
{
       Word Ap,B,a,b,e,ep,es,rp;
       /* hide Ap,a,e,ep,rp; */

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* A /= 0. */
       Ap = A;
       rp = r - 1;
       B = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         ep = e + 1;
         es = LIST2(1,ep);
         b = RPRNP(rp,es,a);
         B = COMP2(b,ep,B);
         }
       while (!(Ap == NIL));
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
