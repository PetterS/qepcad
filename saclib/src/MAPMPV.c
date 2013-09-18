/*===========================================================================
			MAPMPV(p,A,n,k)

Modular array polynomial multiplication by a power of variable.

Inputs
  A : a univariate polynomial in array representation.
  k : a positive integer such that m + k + 2 <= n where m = deg(A) and
      n is the size of the array representing A.

Side effect
  The array is modified so that it represents x^k A(x).
===========================================================================*/
#include "saclib.h"

void MAPMPV(A,k)
       Word *A,k;
{
       Word m,i;

Step1: /* Shift the coefficients. */
       m = MAPDEG(A);
       for (i = m; i >= 0; i--)
	  MAPCF(A,i+k) = MAPCF(A,i);

Step2: /* Append zeros. */
       for (i = 0; i < k; i++)
	  MAPCF(A,i) = 0;

Step3: /* Change the degree. */
       MAPDEG(A) = m+k;

Return: /* Prepare for return. */
       return;
}
