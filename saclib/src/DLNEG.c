/*=======================================================================
                         b <- DLNEG(a)

Discrete logarithm negative.

Inputs
   a : an element of a field, represented as a discrete logarithm.

Output
   b : -a, represented as a discrete logarithm.
=======================================================================*/
#include "saclib.h"

BDigit DLNEG(a)
	BDigit a;
{
	BDigit b,q2;

Step1: /* Three cases. */
	if (a == 0)
	   b = 0;
	else if (FFSIZE & 1 == 1)
	   b = a;
	else {
	   q2 = FFSIZE >> 1;
	   b = a + q2;
	   if (b > FFSIZE)
	      b = b - FFSIZE; }

Return: /* Return b. */
	return(b);
}
