/*=======================================================================
                         B <- INVPERM(n,A)

Invert permutation.

Inputs
   n : a positive beta digit.
   A : an array of n beta digits such that, for 0 <= i < n,
       there exists j, 0 <= j < n, such that A[j] = i.

Output
   B : an array of n beta digits such that B[i] = j if and only if
       A[j] = i.
=======================================================================*/
#include "saclib.h"

BDigit *INVPERM(n,A)
	BDigit n,*A;
{
	BDigit i,j,*B;

Step1: /* Get an array and assign its elements. */
	B = GETARRAY(n);
	for (i = 0; i < n; i++) {
	   j = A[i];
	   B[j] = i; }

Return: /* Return B. */
	return(B);
}
