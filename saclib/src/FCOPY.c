/*======================================================================
                      FCOPY(A,B)

Floating point copy.

Inputs
   A : a floating-point number.
   B : an array as large as A.

Effect
   The floating-point number A is copied into B.
======================================================================*/
#include "saclib.h"

void FCOPY(A,B)
	Word *A,*B;
{

	BDigit i,p;

Step1: /* Copy A. */
	p = A[2];
	for (i = 0; i <= p + 2; i++)
	   B[i] = A[i];

Return: /* Return. */
	return;
}
