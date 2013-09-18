/*======================================================================
                      B <- IPBEILV(r,A,c,k,m)

Integral polynomial binary rational evaluation, integral polynomial
result, leading variable.

Inputs
  r : A BETA-digit.  r > 0.
  A : an element of Z[X1,...,Xr].
  c : an element of Z.
  k : A BETA-digit.  k >= 0
  m : A non-negative BETA-digit.  m >= deg_1(A(X1,...,Xr)).

Outputs
  B : an element of Z[X2,...,Xr].  
      B(X2,...,Xr) = 2^{km}A(c/2^k,X2,...,Xr).
======================================================================*/
#include "saclib.h"

Word IPBEILV(r,A,c,k,m)

       Word r,A,c,k,m;
{
       Word B;
       Word Ap,a,b,e,m1;

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* r=1. */
       if (r == 1)
         {
         m1 = PDEG(A);
         B = ITRUNC(IUPBEI(A,c,k),k * (m1 - m));
         goto Return;
         }

Step3: /* r>1. */
       B = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         b = IPBEILV(r - 1,a,c,k,m);
         if (b != 0)
           B = COMP2(b,e,B);
         }
       if (B == NIL)
         B = 0;
       else
         B = INV(B);

Return:
       return(B);
}
