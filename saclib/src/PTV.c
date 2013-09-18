/*======================================================================
         B <- PTV(r,A,i)

Polynomial transpose variables.

Inputs
  r : an element of Z.  r >= 2.
  A : an element of R[X1,...,Xr]
  i : 1 <= i <= r.

Outputs
  B : an element of R[X1,...,Xr].  
      B(X1,...,X{i-1},Xi,...,Xr) = A(X1,...,Xi,X{i-1},...,Xr).
======================================================================*/
#include "saclib.h"

Word PTV(r,A,i)

       Word r,A,i;
{
       Word B;
       Word Ap,a,b,e;

Step1: /*[i=r.]*/
       if (i == r)
         {
         B = PTMV(r,A);
         goto Return;
         }

Step2: /* i<r. */
       Ap = A;
       B = NIL;
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         b = PTV(r - 1,a,i);
         B = COMP2(b,e,B);
         }
       B = INV(B);

Return:
       return(B);
}
