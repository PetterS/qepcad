/*=======================================================================
                             h <- GIHQ(a)

Gaussian integer half quadrant.

Input
   a : a nonzero first quadrant Gaussian integer.

Output
   h : the half quadrant in which a lies.  That is, h = 1 if
       arg(a) < pi / 4, and otherwise h = 2.
=======================================================================*/
#include "saclib.h"

BDigit GIHQ(a)
	Word a;
{
	BDigit h;
	Word a1,a2;

Step1: /* Compare components. */
	FIRST2(a, &a1,&a2);
	if (ICOMP(a1,a2) < 0)
	   h = 1;
	else
	   h = 2;

Return: /* Return h. */
	return(h);
}
