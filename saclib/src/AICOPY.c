/*========================================================================
                           AICOPY(A,B)

Array integer copy.

Inputs
   A : an integer in array representation.
   B : an array large enough to hold the integer A.

Effect
   A is copied into array B.
========================================================================*/
#include "saclib.h"

void AICOPY(A,B)

	BDigit *A,*B;
{
	BDigit i,n;

Step1: /* Get the length of A. */
	n = A[1];

Step2: /* Copy. */
	for (i = 0; i < n + 2; i++)
	   B[i] = A[i];
	if (n == 0)
	   B[2] = A[2];

Return: /* Return. */
	return;
}
