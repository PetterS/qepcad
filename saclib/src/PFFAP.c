/*=======================================================================
                         A <- PFFAP(p,a)

Prime finite field array of powers.

Inputs
   p : a prime beta digit.
   a : a generator for Z_p.

Output
   A : An array of p beta digits.  A[0] = 0 and, for 0 < i < p,
       A[i] = a^i, an element of Z_p.
=======================================================================*/
#include "saclib.h"

BDigit *PFFAP(p,a)
	BDigit p,a;
{
	BDigit *A,i;

Step1: /* Get array for A. */
	A = GETARRAY(p);

Step2: /* Compute array elements. */
	A[0] = 0;
	A[1] = a;
	for (i = 2; i < p; i++)
	   A[i] = MDPROD(p,A[i-1],a);

Return: /* Return A. */
	return(A);
}
