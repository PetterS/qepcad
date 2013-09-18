/*======================================================================
         B <- PICPV(r,A,i,j)

Polynomial inverse cyclic permutation of variables.

Inputs
  r : an element of Z.  r >= 2.
  A : an element of R[X1,...,Xr]
  i : 1 <= i <= r.
  j : i < j <= r.

Outputs
  B : an element of R[X1,...,Xr].  
      B(X1,...,Xr) = A(X1,...,X_{i-1},X_{i+1},...,Xj,Xi,X_{j+1},...,Xr)
                   = A(X_p(1),...,X_p(r)), where p = (i,i+1,...,j)
======================================================================*/
#include "saclib.h"

Word PICPV(r,A,i,j)

       Word r,A,i,j;
{
       Word B;
       Word B1;

Step1: /* (i,...,j) = (j,j-1)(i,...,j-1). */
       if (j == i + 1)
         {
         B1 = A;
         }
       else
         {
         B1 = PICPV(r,A,i,j - 1);
         }
       B = PTV(r,B1,j);

Return:
       return(B);
}
