/*===========================================================================
			    B <- PCPV(r,A,i,j)

Polynomial cyclic permutation of variables.

Inputs
  r : an element of Z.  r >= 2.
  A : an element of R[x_1,...,x_r]
  i : 1 <= i <= r.
  j : i < j <= r.

Outputs
  B : an element of R[x_1,...,x_r].  
      B(x_1,...,x_r) = A(x_1,...,x_{i-1},x_j,x_i,...,x_{j-1},x_{j+1},...,x_r)
                   = A(x_p(1),...,x_p(r)), where p = (i,i+1,...,j)^{-1}
===========================================================================*/
#include "saclib.h"

Word PCPV(r,A,i,j)

       Word r,A,i,j;
{
       Word B;
       Word B1;

Step1: /* (i,...,j)^{-1} = (i,...,j-1)^{-1}(j,j-1). */
       B1 = PTV(r,A,j);
       if (j == i + 1) {
	  B = B1;
	  goto Return; }
       else
	  B = PCPV(r,B1,i,j - 1);

Return: /* Prepare for return. */
       return(B);
}
