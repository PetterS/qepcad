/*======================================================================
                      C <- RPDIF(r,A,B)

Rational polynomial difference.

Inputs
  A, B : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 0.

Outputs
  C : in Q[X1,...,Xr], C = A - B.
======================================================================*/
#include "saclib.h"

Word RPDIF(r,A,B)
       Word r,A,B;
{
       Word Ap,Bp,C,Cp,Cpp,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0) {
         C = RPNEG(r,B);
         goto Return; }
       if (B == 0) {
         C = A;
         goto Return; }

Step2: /* r=0. */
       if (r == 0) {
         C = RNDIF(A,B);
         goto Return; }

Step3: /* General case. */
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
             if (rp == 0) c = RNNEG(b);
             else         c = RPNEG(rp,b);
             Cp = COMP2(c,f,Cp); }
           else {
             ADV2(Ap,&e,&a,&Ap);
             ADV2(Bp,&f,&b,&Bp);
             if (rp == 0) c = RNDIF(a,b);
             else         c = RPDIF(rp,a,b);
             if (c != 0)
               Cp = COMP2(c,e,Cp); } }
       while (Ap != NIL && Bp != NIL);

Step4: /* Finish. */
       if (Ap == NIL && Bp == NIL)
         Cpp = NIL;
       else
         if (Ap == NIL)
           Cpp = RPNEG(r,Bp);
         else
           Cpp = Ap;
       C = INV(Cp);
       if (C == NIL)
         C = Cpp;
       else
         SRED(Cp,Cpp);
       if (C == NIL)
         C = 0;

Return: /* Prepare for return. */
       return(C);
}
