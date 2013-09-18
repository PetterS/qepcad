/*======================================================================
                      C <- AFPAFP(r,M,a,B)

Algebraic number field polynomial algebraic number field element
product.  

Inputs
  r : a BETA-digit, r >= 1, the number of variables.
  M : in Z[X], M is the minimal polynomial for alpha.
  a : in Q(alpha).
  B : in Q(alpha)[X1,...,Xr].

Outputs
  C : in Q(alpha)[X1,...,Xr], C = a * B.
======================================================================*/
#include "saclib.h"

Word AFPAFP(r,M,a,B)
       Word r,M,a,B;
{
       Word Bp,C,b,c,e,rp;
       /* hide b,rp; */

Step1: /* C = 0. */
       if (a == 0 || B == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* General case. */
       Bp = B;
       C = NIL;
       rp = r - 1;
       do
         {
         ADV2(Bp,&e,&b,&Bp);
         if (rp == 0)
           c = AFPROD(M,a,b);
         else
           c = AFPAFP(rp,M,a,b);
         C = COMP2(c,e,C);
         }
       while (Bp != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
