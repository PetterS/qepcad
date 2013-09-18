/*======================================================================
                     B <- IPTRLV(r,A,h)

Integral polynomial translation, leading variable.

Inputs
  r : A BETA-digit.  r >= 0.
  A : an element of Z[X1,...,Xr].

Outputs
  B : an element of Z[X1,...,Xr].  
      B(X1,...,Xr) = A(X1+h,X2,...,Xr).
======================================================================*/
#include "saclib.h"

Word IPTRLV(r,A,h)
       Word r,A,h;
{
       Word B;
       Word Ap,a,b,e;

Step1: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step2: /* r=1. */
       if (r == 1)
         {
         B = IUPTR(A,h);
         goto Return;
         }

Step3: /* r>1. */
       B = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         b = IPTRLV(r - 1,a,h);
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
