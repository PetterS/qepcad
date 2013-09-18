/*========================================================================
                           t = AGIZERO(A)

Array Gaussian integer zero.

Input
   A : a Gaussian integer in array representation.

Output
   t : a BETA digit.  t = 1 if A = 0; t = 0 otherwise.
========================================================================*/
#include "saclib.h"

BDigit AGIZERO(A)
	BDigit **A;
{
	BDigit t;

Step1: /* Test the parts. */
	if (AIZERO(A[0]) && AIZERO(A[1]))
	   t = 1;
	else
	   t = 0;

Return: /* Return t. */
	return(t);
}
