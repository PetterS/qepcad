/*========================================================================
                           B = GIAGI(A)

Gaussian integer to array Gaussian integer.

Input
   A : a Gaussian integer.

Output
   B : The array representation of A.
========================================================================*/
#include "saclib.h"

BDigit **GIAGI(A)
	Word A;
{
	BDigit **B;
	Word A1,A2;

Step1: /* Get the parts. */
	if (A == 0) {
	   A1 = 0;
	   A2 = 0; }
	else
	   FIRST2(A, &A1,&A2);

Step2: /* Convert the parts. */
	B = GETMATRIX(2,1);
	FREEARRAY(B[0]);
	FREEARRAY(B[1]);
	B[0] = IAI(A1);
	B[1] = IAI(A2);

Return: /* Return B. */
	return(B);
}
