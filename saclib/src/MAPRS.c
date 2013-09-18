/*===========================================================================
                      MAPRS(p,A,B)

Modular array polynomial remainder step.

Inputs
   p : a prime BETA-digit.
   A,B : nonzero univariate polynomials over Z_p in array
	 representation, with deg(A) >= deg(B).

Effect:
   Let m = deg(A), n = deg(B), a = ldcf(A), b = ldcf(B).
   A is replaced by A - (a/b) x^{m-n} B.
===========================================================================*/
#include "saclib.h"

void MAPRS(p,A,B)
	BDigit p;
	Word *A,*B;
{
	BDigit a,b,c,i,k,m,n;

Step1: /* If deg(B) = 0, set A to zero. */
	if (MAPDEG(B) == 0) {
	   A[-1] = 0;
           A[0] = 0; }

Step2: /* Get degrees and leading coefficients. */
	m = MAPDEG(A);
	n = MAPDEG(B);
	a = MAPLDCF(A);
	b = MAPLDCF(B);

Step3: /* Compute c = a/b. */
	c = MDQ(p,a,b);

Step4: /* Subtract c x^{m-n} B from A. */
	k = m - n;
	for (i = 0; i < n; i++)
	   A[i+k] = MDDIF(p,A[i+k],MDPROD(p,c,B[i]));

Step5: /* Update degree of A. */
	m = m - 1;
	while (m >= 0 && A[m] == 0)
	   m = m - 1;
	if (m < 0)
	   m = 0;
	A[-1] = m;

Return: /* Return. */
	return;
}
