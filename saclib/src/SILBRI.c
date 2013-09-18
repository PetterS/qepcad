/*======================================================================
                      J <- SILBRI(I)

Software interval to logarithmic binary rational interval.

Input
   I : a software interval.

Output
   J : a logarithmic binary rational interval equal to I.
======================================================================*/
#include "saclib.h"

Word SILBRI(I)
	BDigit *I;
{

	BDigit p;
	Word a,b,J;

Step1:/* Convert the endpoints. */
	p = I[2];
	a = FLBRN(I);
	b = FLBRN(I + p + 3);
	J = LIST2(a,b);

Return: /* Return J. */
	return(J);
}
