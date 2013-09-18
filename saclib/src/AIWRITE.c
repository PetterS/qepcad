/*======================================================================
                          AIWRITE(A)

Array integer write.

Input
   A : an integer in array representation.

Effect
   A is written in the output stream.
======================================================================*/
#include "saclib.h"

void AIWRITE(A)
	BDigit *A;
{
	Word B;

Step1: /* Convert to list representation and write. */
	B = AII(A);
	IWRITE(B);

Return: /* Return. */
	return;
}
