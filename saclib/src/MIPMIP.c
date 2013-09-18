/*===========================================================================
                            C <- MIPMIP(r,M,a,B)

Modular integral polynomial modular integer product.

Inputs
  r : a BETA-digit, r >= 1, the number of variables;
  M : in Z, M > 1.
  a : in Z/(M).
  B : in Z/(M)[X1,...,Xr].

Outputs
  C : in Z/(M)[X1,...,Xr], C = a * B.
===========================================================================*/
#include "saclib.h"

Word MIPMIP(r,M,a,B)
       Word r,M,a,B;
{
       Word Bp,C,b,c,e,rp;

Step1: /* C = 0. */
       if (a == 0 || B == 0) {
          C = 0;
          goto Return; }

Step2: /* General case. */
       Bp = B;
       C = NIL;
       rp = r - 1;
       do {
          ADV2(Bp,&e,&b,&Bp);
          if (rp == 0)
             c = MIPROD(M,a,b);
          else
             c = MIPMIP(rp,M,a,b);
          C = COMP2(c,e,C); }
       while (Bp != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
