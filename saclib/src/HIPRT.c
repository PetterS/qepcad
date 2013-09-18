/*======================================================================
                          B <- HIPRT(n,A)

Hardware interval polynomial reciprocal transformation.

Inputs
   n : a positive BETA-digit.
   A : in HI[x], deg(A) = n.

Output
   B : in HI[x], B(x) = X^n A(1/x).
======================================================================*/
#include "saclib.h"

interval *HIPRT(n,A)
	BDigit n;
	interval *A;
{
	BDigit i;
	interval *B;

Step1: /* Get array for B. */
	B = GETHIPARRAY(n);

Step2: /* Copy elements in reverse order. */
	for (i=0; i <= n; i++)
	   B[i] = A[n-i];

Return: /* Return B. */
	return(B);
}
