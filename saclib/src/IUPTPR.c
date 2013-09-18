/*======================================================================
                      C <- IUPTPR(n,A,B)

Integral univariate polynomial truncated product.

Inputs
  n   : in Z, n >= 0.
  A,B : in Z[X].

Outputs
  C   : in Z[X], C(x) = A(x)*B(x) (modulo x^n)
        and C = 0 or deg(C) < n.
======================================================================*/
#include "saclib.h"

Word IUPTPR(n,A,B)
       Word n,A,B;
{
       Word Ap,As,Bs,C,Cp,a,b,c,e,f;

Step1: /* n=0 or A=0 or B=0. */
       C = 0;
       if (n == 0 || A == 0 || B == 0)
         goto Return;

Step2: /* General case. */
       As = CINV(A);
       Bs = CINV(B);
       while (Bs != NIL && SECOND(Bs) < n)
         {
         ADV2(Bs,&b,&f,&Bs);
         Ap = As;
         Cp = NIL;
         while (Ap != NIL && SECOND(Ap) < n - f)
           {
           ADV2(Ap,&a,&e,&Ap);
           c = IPROD(a,b);
           Cp = COMP2(e + f,c,Cp);
           }
         if (Cp != NIL)
           C = IPSUM(1,C,Cp);
         }

Return: /* Prepare for return. */
       return(C);
}
