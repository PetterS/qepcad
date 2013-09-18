/*======================================================================
                      C <- RPSUM(r,A,B)

Rational polynomial sum.

Inputs
  A, B : in Q[X1,...,Xr].
  r    : a BETA-digit, r >= 0.

Outputs
  C    : in Q[X1,...,Xr], C = A + B.
======================================================================*/
#include "saclib.h"

Word RPSUM(r,A,B)
       Word r,A,B;
{
       Word Ap,Bp,C,Cp,a,b,c,e,f,rp;
       /* hide C,a,b,f,rp; */

Step1: /* A=0 or B=0. */
       if (A == 0) {
         C = B;
         goto Return; }
       if (B == 0) {
         C = A;
         goto Return; }

Step2: /* r=0. */
       if (r == 0) {
         C = RNSUM(A,B);
         goto Return; }

Step3: /* Match coefficients. */
       Ap = A;
       Bp = B;
       Cp = NIL;
       rp = r - 1;
       do {
         e = FIRST(Ap);
         f = FIRST(Bp);
         if (e > f) {
           ADV2(Ap,&e,&a,&Ap);
           Cp = COMP2(a,e,Cp); }
         else
           if (e < f) {
             ADV2(Bp,&f,&b,&Bp);
             Cp = COMP2(b,f,Cp); }
           else {
             ADV2(Ap,&e,&a,&Ap);
             ADV2(Bp,&f,&b,&Bp);
             if (rp == 0) c = RNSUM(a,b);
             else         c = RPSUM(rp,a,b);
             if (c != 0)
               Cp = COMP2(c,e,Cp); } }
       while (Ap != NIL && Bp != NIL);

Step4: /* Finish. */
       if (Ap == NIL)
         Ap = Bp;
       if (Cp == NIL)
         C = Ap;
       else {
         C = INV(Cp);
         SRED(Cp,Ap); }
       if (C == NIL)
         C = 0;

Return: /* Prepare for return. */
       return(C);
}
