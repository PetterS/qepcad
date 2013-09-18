/*===========================================================================
			LSHIFT1(A,n)

Left shift one bit.

Inputs
   A : an array containing the n BETA digits of an integer a, with
       0 <= a < BETA^n / 2.
   n : a positive BETA digit.

Effect
   a is replaced by 2 a, i. e. a is shifted left one bit.
===========================================================================*/
#include "saclib.h"

void LSHIFT1(A,n)
	Word *A;
	BDigit n;
{

	BDigit a,ap,i;

Step1: /* */
	ap = 0;
	for (i = 0; i < n - 1; i++) {
	   a = A[i];
	   A[i] = ((a << 1) & BETA1) | ap;
	   ap = a >> (ZETA - 1); }

Step2: /* Shift last digit. */
	A[n-1] = (A[n-1] << 1) | ap;

Return: /* Return. */
	return;
}
