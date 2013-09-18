/*=======================================================================
                         b <- MAPSEV(A,a)

Modular array polynomial special evaluation.

Inputs
   A : a modular array polynomial over Z_p for some medium prime p.
   a : a nonnegative beta digit such that A(a) (evaluation in
       Z. not in Z_p) is a beta digit.

Output
   b : A(a), a beta digit.
=======================================================================*/
#include "saclib.h"

BDigit MAPSEV(A,a)
	BDigit *A,a;
{
	BDigit b,i,n;

Step1: /*  Apply Horner's method. */
	n = MAPDEG(A);
	b = MAPCF(A,n);
	for (i = n - 1; i >= 0; i--)
	   b = b * a + MAPCF(A,i);

Return: /* Return b. */
	return(b);
}
