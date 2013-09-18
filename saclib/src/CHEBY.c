/*======================================================================
			A <- CHEBY(n)

Chebyshev polynomial.

Input
   n : a non-negative beta-digit.

Output
   A : The Chebyshev polynomial of degree n, a univariate integral
       polynomial.
======================================================================*/
#include "saclib.h"

Word CHEBY(n)
	BDigit n;
{
	Word A,A1,A2,A3,i;

Step1: /* Initialize. */
	A1 = LIST2(0,1);
	if (n == 0) {
	   A = A1;
	   goto Return; }
	A2 = LIST2(1,1);
	if (n == 1) {
           A = A2;
           goto Return; }
	i = 1;

Step2: /* Apply recurrence relation. */
	A3 = IPIP(1,2,PMPMV(A2,1));
	A3 = IPDIF(1,A3,A1);
	A1 = A2;
	A2 = A3;
	i = i + 1;
	if (i < n) 
	   goto Step2;
	A = A2;

Return: /* Return A. */
	return(A);
}
