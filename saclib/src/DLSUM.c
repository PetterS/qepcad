/*=======================================================================
                         c <- DLSUM(a,b)

Discrete logarithm sum.

Inputs
   a, b : elements of a finite field represented as discrete logarithms.

Output
   c : a + b, the finite field sum.
=======================================================================*/
#include "saclib.h"

BDigit DLSUM(a,b)
	BDigit a,b;
{
	BDigit c,d;

Step1: /* c = b * ( a / b + 1). */
	if (a == 0)
	   c = b;
	else if (b == 0)
	   c = a;
	else {
	   d = a - b;
	   if (d <= 0)
	      d = d + FFSIZE;
	   c = b + FFPLUS1[d];
	   if ( c > FFSIZE)
	      c = c - FFSIZE; }

Return: /* Return c. */
	return(c);
}
