/*======================================================================
                      C <- IPRESBEZ(r,A,B)

Integral polynomial resultant, Bezout.

Inputs
   r    : a positive beta digit.
   A, B : integral polynomials of positive degrees.

Output
   C : the reultant of A and B with respect to the main variable.

Method
   The Bezout matrix of A and B is computed and its determinant
is computed by minors evaluation.
======================================================================*/
#include "saclib.h"

Word IPRESBEZ(r,A,B)
	BDigit r;
        Word A,B;
{
	BDigit s;
        Word Ap,Bp,M,R;

Step1: /* Interchange A and B if necessary. */
	if (PDEG(A) >= PDEG(B)) {
	   Ap = A;
	   Bp = B;
	   s = 1; }
	else {
	   Ap = B;
	   Bp = A;
	   s = -1; }

Step2: /* Comstruct the Bezout matrix. */
	M = IPBEZM(r,Ap,Bp);

Step3: /* Compute the determinant. */
	R = MAIPDME(r-1,M);

Step4: /* Adjust sign if necessary. */
	if (s < 0)
	   R = IPNEG(r-1,R);

Return: /* Return R. */
	return(R);
}
