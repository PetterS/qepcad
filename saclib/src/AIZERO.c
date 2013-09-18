/*========================================================================
                           t = AIZERO(A)

Array integer zero.

Input
   A : an integer in array representation.

Output
   t : a BETA digit.  t = 1 if A = 0; t = 0 otherwise.
========================================================================*/
#include "saclib.h"

BDigit AIZERO(A)
	BDigit *A;
{
	BDigit t;

Step1: /* Check the sign. */
	if (A[0] == 0)
	   t = 1;
	else
	   t = 0;

Return: /* Return t. */
        return(t);
}
