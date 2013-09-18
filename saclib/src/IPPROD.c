/*======================================================================
                      C <- IPPROD(r,A,B)

Integral polynomial product.

Inputs
  A,B : in Z[X1,...,Xr].
  r   : a BETA-digit, r >= 0, the number of variables.

Outputs
  C   : in Z[X1,...,Xr], C = A * B.
======================================================================*/
#include "saclib.h"

Word IPPROD(r,A,B)
       Word r,A,B;
{
       Word Ap,As,Bs,C,C1,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0 || B == 0) {
         C = 0;
         goto Return; }

Step2: /* r=0. */
       if (r == 0) {
         C = IPROD(A,B);
         goto Return; }

Step3: /* General case. */
       As = CINV(A);
       Bs = CINV(B);
       C = 0;
       rp = r - 1;
       do {
         ADV2(Bs,&b,&f,&Bs);
         Ap = As;
         C1 = NIL;
         do {
           ADV2(Ap,&a,&e,&Ap);
           if (rp == 0) c = IPROD(a,b);
           else         c = IPPROD(rp,a,b);
           C1 = COMP2(e + f,c,C1); }
         while (Ap != NIL);
         C = IPSUM(r,C,C1); }
       while (Bs != NIL);

Return: /* Prepare for return. */
       return(C);
}
