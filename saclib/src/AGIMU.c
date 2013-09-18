/*=======================================================================
                            AGIMU(A,k,B)

Array Gaussian integer multiplication by a unit.

Inputs
   A : a non-zero array Gaussian integer.
   k : a BETA digit, 0 <= k <= 3.
   B : an array large enough for i^k * A.

Effect
   i^k * A is placed in B.
========================================================================*/
#include "saclib.h"

void AGIMU(A,k,B)
	BDigit **A,k,**B;
{
	BDigit *B1,*B2,*B3;

Step1: /* Copy, then fix signs and pointers. */
	AGICOPY(A,B);
	B1 = B[0];
	B2 = B[1];
	if (k == 2) {
           B1[0] = - B1[0];
           B2[0] = - B2[0]; }
	else if (k != 0) {
	   B3 = B1;
	   B1 = B2;
	   B2 = B3;
	   if (k == 1)
	      B1[0] = - B1[0];
	   else
	      B2[0] = - B2[0]; }
	B[0] = B1;
	B[1] = B2;

Return: /* Return. */
	return;
}
