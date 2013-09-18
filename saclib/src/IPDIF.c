/*======================================================================
                      C <- IPDIF(r,A,B)

Integral polynomial difference.

Inputs
  r    : a BETA-digit, r >= 0, the number of variables.
  A,B  : in Z[X1,...Xr].

Outputs
  C    : in Z[X1,...Xr], C = A - B.
======================================================================*/
#include "saclib.h"

Word IPDIF(r,A,B)
       Word r,A,B;
{
       Word Ap,Bp,C,Cp,Cpp,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0) {
         C = IPNEG(r,B);
         goto Return; }
       if (B == 0) {
         C = A;
         goto Return; }

Step2: /* r=0. */
       if (r == 0) {
         C = IDIF(A,B);
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
             if (rp == 0) c = INEG(b);
             else         c = IPNEG(rp,b);
             Cp = COMP2(c,f,Cp); }
           else {
             ADV2(Ap,&e,&a,&Ap);
             ADV2(Bp,&f,&b,&Bp);
             if (rp == 0) c = IDIF(a,b);
             else         c = IPDIF(rp,a,b);
             if (c != 0)
               Cp = COMP2(c,e,Cp); } }
       while (Ap != NIL && Bp != NIL);

Step4: /* Finish. */
       if (Ap == NIL && Bp == NIL)
         Cpp = NIL;
       else
         if (Ap == NIL)
           Cpp = IPNEG(r,Bp);
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

