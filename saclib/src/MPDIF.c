/*======================================================================
                      C <- MPDIF(r,m,A,B)

Modular polynomial difference.

Inputs
  A,B : in Z/(m)[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.
  m : a BETA-digit.

Outputs
  C : in Z/(m)[X1,...,Xr], C = A - B.
======================================================================*/
#include "saclib.h"

Word MPDIF(r,m,A,B)
       Word r,m,A,B;
{
       Word Ap,Bp,C,Cp,Cpp,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0) {
         C = MPNEG(r,m,B);
         goto Return; }
       if (B == 0) {
         C = A;
         goto Return; }

Step2: /* General case. */
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
             if (rp == 0) c = MDNEG(m,b);
             else         c = MPNEG(rp,m,b);
             Cp = COMP2(c,f,Cp); }
           else {
             ADV2(Ap,&e,&a,&Ap);
             ADV2(Bp,&f,&b,&Bp);
             if (rp == 0) c = MDDIF(m,a,b);
             else         c = MPDIF(rp,m,a,b);
             if (c != 0)
               Cp = COMP2(c,e,Cp); } }
       while (Ap != NIL && Bp != NIL);

Step3: /* Finish. */
       if (Ap == NIL && Bp == NIL)
         Cpp = NIL;
       else
         if (Ap == NIL)
           Cpp = MPNEG(r,m,Bp);
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
