/*======================================================================
                      AWCOPY(A,n,B)

Array of words copy.

Inputs
   A : an array of words of size n.
   n : a positive BETA-digit.
   B : an array of words large enough for a copy of A.

Effect
   The array A is copied into B.
======================================================================*/
#include "saclib.h"

void AWCOPY(A,n,B)
	Word *A;
	BDigit n;
	Word *B;
{

	BDigit i;

Step1: /* Copy A. */
	for (i = 0; i < n; i++)
	   B[i] = A[i];

Return: /* Return. */
	return;
}
