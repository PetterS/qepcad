/*======================================================================
                      J <- LBRINSUM(I,c)

Logarithmic binary rational interval number sum.

Inputs
   I : a logarithmic binary rational interval.
   c : a logarithmic binary rational number.

Output
   J : a logarithmic binary rational interval.  J = I + c.
======================================================================*/
#include "saclib.h"

Word LBRINSUM(I,c)
	Word I,c;
{
	Word a,b,J;

Step1: /* Add r to each endpoint. */
	FIRST2(I,&a,&b);
	a = LBRNSUM(a,c);
	b = LBRNSUM(b,c);
	J = LIST2(a,b);

Return: /* Return J. */
	return(J);
}
