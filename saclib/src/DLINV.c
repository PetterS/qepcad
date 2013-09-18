/*=======================================================================
                         b <- DLINV(a)

Discrete logarithm inverse.

Input
   a : a nonzero element of a field represented as a discrete logarithm.

Output
   b : b = 1 / a, the inverse of a in the field.
=======================================================================*/
#include "saclib.h"

BDigit DLINV(a)
	BDigit a;
{
	BDigit b;

Step1: /* Obvious. */
	if (a == FFSIZE)
	   b = a;
	else
	   b = FFSIZE - a;

Return: /* Return b. */
	return(b);
}
