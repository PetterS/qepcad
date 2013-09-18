/*======================================================================
                          AGIWRITE(A)

Array Gaussian integer write.

Input
   A : a Gaussian integer in array representation.

Effect
   A is written in the output stream.
======================================================================*/
#include "saclib.h"

void AGIWRITE(A)
        BDigit **A;
{
        BDigit B,B1,B2;

Step1: /* Convert to list representation and write. */
	B1 = AII(A[0]);
	B2 = AII(A[1]);
	if (B1 == 0 && B2 == 0)
	   B = 0;
	else
	   B = LIST2(B1,B2);
	GIWRITE(B);

Return: /* Return. */
	return;
}
