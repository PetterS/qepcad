/*======================================================================
                      C <- MPSUM(r,m,A,B)

Modular polynomial sum.

Inputs
  A,B : in Z/(m)[X1,...,Xr].
  r : a BETA-digit, r >= 1, the number of variables.
  m : a BETA-digit.

Outputs
  C :  in Z/(m)[X1,...,Xr], C = A + B.
======================================================================*/
#include "saclib.h"

Word MPSUM(r,m,A,B)
       Word r,m,A,B;
{
       Word Ap,Bp,C,Cp,a,b,c,e,f,rp;

Step1: /* A or B zero. */
       if (A == 0) {
         C = B;
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
             Cp = COMP2(b,f,Cp); }
           else {
             ADV2(Ap,&e,&a,&Ap);
             ADV2(Bp,&f,&b,&Bp);
             if (rp == 0) c = MDSUM(m,a,b);
             else         c = MPSUM(rp,m,a,b);
             if (c != 0)
               Cp = COMP2(c,e,Cp); } }
       while (Ap != NIL && Bp != NIL);

Step3: /* Finish. */
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
