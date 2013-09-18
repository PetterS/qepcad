/*======================================================================
                     B <- IPNT(r,A,i)

Integral polynomial negative transformation.

Inputs
  r : a positive BETA digit.
  A : an element of Z[X1,...,Xr].
  i : 1 <= i <= r.

Outputs
  B : an element of Z[X1,...,Xr].  B(X1,...,Xr) = A(X1,...,-Xi,...,Xr).
======================================================================*/
#include "saclib.h"

Word IPNT(r,A,i)
       Word r,A,i;
{
       Word B;
       Word Ap,a,b,e,n,rp;

Step1: /* Degree zero. */
       n = PDEG(A);
       if (n == 0)
         {
         B = A;
         goto Return;
         }

Step2: /* r=1. */
       if (r == 1)
         {
         B = IUPNT(A);
         goto Return;
         }

Step3: /* r > 1. */
       B = NIL;
       Ap = A;
       rp = r - 1;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         if (r == i)
           {
           if (ODD(e))
             b = IPNEG(rp,a);
           else
             b = a;
           }
         else
           b = IPNT(rp,a,i);
         B = COMP2(b,e,B);
         }
       B = INV(B);

Return:
       return(B);
}
