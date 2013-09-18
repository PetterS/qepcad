/*========================================================================
			J <- HILBRI(I)

Hardware interval to logarithmic binary rational interval.

Input
   I : a hardware interval.

Output
   J : the interval I in logarithmic binary rational representation.
=========================================================================*/
#include "saclib.h"

Word HILBRI(I)
	interval I;
{
	Word a,b,J;

Step1: /* Convert endpoints and make list. */
	a = IEEELBRN(I.left);
	b = IEEELBRN(I.right);
	J = LIST2(a,b);

Return: /* Return J. */
	return(J);
}
