/*======================================================================
                        B <- IPTR1LV(r,A)

Integral polynomial translation by one, leading variable.

Inputs
  r : A BETA-digit.  r >= 0.
  A : an element of Z[X1,...,Xr].

Outputs
  B : an element of Z[X1,...,Xr].  
      B(X1,...,Xr) = A(X1+1,X2,...,Xr).
======================================================================*/
#include "saclib.h"

Word IPTR1LV(r,A)
       Word r,A;
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
         B = IUPTR1(A);
         goto Return;
         }

Step3: /* r>1. */
       B = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         b = IPTR1LV(r - 1,a);
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
