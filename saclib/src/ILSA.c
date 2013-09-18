/*======================================================================
                           ILSA(A,n,k)

Integer left shift in array.

Inputs
   A : an array of size n containing a non-negative integer a that is
       less than BETA^n / 2^k.
   n : a positive BETA-digit.
   k : a positive BETA-digit less than ZETA.

Effect
   The integer a * 2^k replaces a in A.
======================================================================*/
#include "saclib.h"

void ILSA(A,n,k)
	BDigit *A,n,k;
{
	BDigit d,h,i;

Step1: /* Shift. */
	h = ZETA - k;
	A[n - 1] = A[n - 1] << k;
	for (i = n - 2; i >= 0; i--) {
	   d = A[i] >> h;
	   A[i + 1] = A[i + 1] | d;
	   d = A[i] << k;
	   A[i] = d & BETA1; }

Return: /* Return. */
	return;
}
