/*======================================================================
                      w <- LBRIW(I)

Logarithmic binary rational interval width.

Input
   I : a logarithmic binary rational interval.

Output
   w : the width of I, a logarithmic binary rational number.
======================================================================*/
#include "saclib.h"

Word LBRIW(I)
	Word I;
{
	Word a,b,w;


Step1: /* Compute difference of endpoints. */
	FIRST2(I,&a,&b);
	w = LBRNDIF(b,a);

Return: /* Return w. */
	return(w);
}
