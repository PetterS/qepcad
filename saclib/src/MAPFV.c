/*===========================================================================
			B <- MAPFV(n,A)

Modular array  polynomial from vector.

Inputs
  n : a BETA digit.
  A : an array of size at least n containing the coefficients of a 
      modular univariate polynomial, A', with the coefficient of x^i
      in A[i], deg(A') < n.

Output
  B : an array containing the polynomial A'.
===========================================================================*/
#include "saclib.h"

Word *MAPFV(n,A)
       Word n,*A;
{
       Word i,d,*B;

Step1: /* Determine the degree of A'. */
       d = n-1;
       while (A[d] == 0)
	  d--;

Step2: /* Get array B and assign A' to it. */
       B = MAPGET(d);
       MAPDEG(B) = d;
       for (i = 0; i <= d; i++)
	  MAPCF(B,i) = A[i];

Return: /* Prepare for return. */
       return(B);
}
