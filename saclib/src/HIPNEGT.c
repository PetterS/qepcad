/*======================================================================
                        B <- HIPNEGT(n,A)

Hardware interval polynomial negative transformation.

Inputs
   n : a BETA-digit.
   A : in HI[X], deg(A) = n.
  
Output
   B : in HI[X], B(X) = A(-x).
======================================================================*/
#include "saclib.h"

interval *HIPNEGT(n,A)
	BDigit n;
	interval A[];
{
	BDigit i;
	interval *B;

Step1: /* Get array for B. */
	B = GETHIPARRAY(n);

Step2: /* Put negated coefficients in B. */
	for (i = 0; i <= n; i++) {
	   if ((i & 1) == 0) {
	      B[i].left = A[i].left;
	      B[i].right = A[i].right; }
	   else {
	      B[i].left  = - A[i].right;
	      B[i].right = - A[i].left; } }

Return: /* Return B. */
	return(B);
}
