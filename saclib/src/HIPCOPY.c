/*======================================================================
                          B <- HIPCOPY(n,A)

Hardware interval polynomial copy.

Inputs
   n : a BETA-digit.
   A : in HI[X], deg(A) = n.

Output
   B : in HI[X], B(X) = A(X).
======================================================================*/
#include "saclib.h"

interval *HIPCOPY(n,A)
	BDigit n;
	interval A[];
{
	BDigit i;
	interval *B;

Step1: /* Get array. */
	B = GETHIPARRAY(n);

Step2: /* Copy. */
	for (i = 0;i <= n;i++)
	   B[i] = A[i];

Return: /* Return B. */
	return(B);
}
