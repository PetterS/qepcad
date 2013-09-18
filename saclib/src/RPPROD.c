/*======================================================================
                      C <- RPPROD(r,A,B)

Rational polynomial product.

Inputs
  A, B : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 0.

Outputs
  C : in Q[X1,...,Xr], C = A * B.
======================================================================*/
#include "saclib.h"

Word RPPROD(r,A,B)
       Word r,A,B;
{
       Word Ap,As,Bs,C,C1,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0 || B == 0) {
         C = 0;
         goto Return; }

Step2: /* r=0. */
       if (r == 0) {
         C = RNPROD(A,B);
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
           if (rp == 0) c = RNPROD(a,b);
           else         c = RPPROD(rp,a,b);
           C1 = COMP2(e + f,c,C1); }
         while (Ap != NIL);
         C = RPSUM(r,C,C1); }
       while (Bs != NIL);

Return: /* Prepare for return. */
       return(C);
}
