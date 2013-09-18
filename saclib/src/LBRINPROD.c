/*======================================================================
                      J <- LBRINPROD(I,c)

Logarithmic binary rational interval number product.

Inputs
   I : a logarithmic binary rational interval.
   c : a nonzero logarithmic binary rational number.

Output
   J : a logarithmic binary rational interval.  J = I * c.
======================================================================*/
#include "saclib.h"

Word LBRINPROD(I,c)
	Word I,c;
{
	Word a,b,J;

Step1: /* Multiply each endpoint by c. */
	FIRST2(I,&a,&b);
	a = LBRNPROD(a,c);
	b = LBRNPROD(b,c);
	if (LBRNSIGN(c) > 0)
	   J = LIST2(a,b);
	else
	   J = LIST2(b,a);

Return: /* Return J. */
	return(J);
}
