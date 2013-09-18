/*======================================================================
                      SIPCOPY(A,B)

Software interval polynomial copy.

Input
   A : a software interval polynomial.
   B : an array large enough for a copy of A.

Effect
   A is copied into B.
======================================================================*/
#include "saclib.h"

void SIPCOPY(A,B)
	BDigit *A,*B;
{

	BDigit i,S;

Step1: /* Get size of A. */
	S = SIPSIZE(A);

Step2: /* Copy. */
	for (i = 0; i < S; i++)
	   B[i] = A[i];

Return: /* Return. */
	return;
}
