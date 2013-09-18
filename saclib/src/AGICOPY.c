/*========================================================================
                           AGICOPY(A,B)

Array Gaussian integer copy.

Inputs
   A : an array Gaussian integer.
   B : a Gaussian integer array large enough to hold A.

Effect
   A copy of A is placed in B.
========================================================================*/
#include "saclib.h"

void AGICOPY(A,B)
        BDigit **A,**B;
{

Step1: /* Copy the parts. */
	AICOPY(A[0],B[0]);
	AICOPY(A[1],B[1]);

Return: /* Return. */
	return;
}
