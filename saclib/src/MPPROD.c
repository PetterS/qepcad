/*======================================================================
                      C <- MPPROD(r,m,A,B)

Modular polynomial product.

Inputs
  A,B : in Z/(m)[X1,...,Xr].
  r : a BETA-digit, r >= 0, the number of variables.
  m : a BETA-digit.

Outputs
  C :  in Z/(m)[X1,...,Xr], C = A * B.
======================================================================*/
#include "saclib.h"

Word MPPROD(r,m,A,B)
       Word r,m,A,B;
{
       Word Ap,As,Bs,C,C1,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0 || B == 0) {
         C = 0;
         goto Return; }

Step2: /* r=0. */
       if (r == 0) {
         C = MDPROD(m,A,B);
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
           if (rp == 0) c = MDPROD(m,a,b);
           else         c = MPPROD(rp,m,a,b);
           if (c != 0)
             C1 = COMP2(e + f,c,C1); }
         while (Ap != NIL);
         if (C1 != NIL)
           C = MPSUM(r,m,C,C1); }
       while (Bs != NIL);

Return: /* Prepare for return. */
       return(C);
}
