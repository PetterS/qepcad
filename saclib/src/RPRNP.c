/*======================================================================
                      C <- RPRNP(r,a,B)

Rational polynomial rational number product.

Inputs
  B : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 0.
  a : in Q.

Outputs
  C : in Q[X1,...,Xr], C = a B.
======================================================================*/
#include "saclib.h"

Word RPRNP(r,a,B)
       Word r,a,B;
{
       Word Bp,C,b,c,e,rp;
       /* hide b,rp; */

Step1: /* a=0 or B=0. */
       if (a == 0 || B == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* r=0. */
       if (r == 0)
         {
         C = RNPROD(a,B);
         goto Return;
         }

Step3: /* General case. */
       C = NIL;
       Bp = B;
       rp = r - 1;
       do
         {
         ADV2(Bp,&e,&b,&Bp);
         c = RPRNP(rp,a,b);
         C = COMP2(c,e,C);
         }
       while (!(Bp == NIL));
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
