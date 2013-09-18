/*=======================================================================
                         c <- DLPROD(a,b)

Discrete logarithm product.

Inputs
   a, b : elements of a finite field represented as discrete logarithms.

Output
   c : a * b, the finite field product.
=======================================================================*/
#include "saclib.h"

BDigit DLPROD(a,b)
	BDigit a,b;
{
	BDigit c;

Step1: /* Add logarithms modulo FFSIZE. */
	if (a == 0 || b == 0)
	   c = 0;
	else {
	   c = a + b;
	   if (c > FFSIZE)
	      c = c - FFSIZE; }

Return: /* Return c. */
	return(c);
}
