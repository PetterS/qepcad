/*======================================================================
                      c <- LBRIMID(I)

Logarithmic binary rational interval midpoint.

Input
   I : a logarithmic binary rational interval.

Output
   c : the midpoint of I, a logarithmic binaary rational number.
======================================================================*/
#include "saclib.h"

Word LBRIMID(I)
	Word I;
{
	Word a,b,c;


Step1: /* Add endpoints and divide by 2. */
	FIRST2(I,&a,&b);
	c = LBRNSUM(a,b);
	if (c != 0)
	   c = LIST2(FIRST(c),SECOND(c) + 1);

Return: /* Return c. */
	return(c);
}
