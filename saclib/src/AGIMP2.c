/*=======================================================================
                        AGIMP2(A,h,B)

Array Gaussian integer multiplication by a power of 2.

Inputs
   A : an array Gaussian integer.
   h : a nonnegative BETA integer.
   B : a Gaussian integer array large enough for the result.

Effect
   2*h A is placed in B.
========================================================================*/
#include "saclib.h"

void AGIMP2(A,h,B)
	BDigit **A,h,**B;
{

Step1: /* Apply AIMP2. */
	AIMP2(A[0],h,B[0]);
	AIMP2(A[1],h,B[1]);

Return: /* Return. */
	return;
}
