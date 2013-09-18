/*======================================================================
                      J <- BRILBRI(I)

Binary rational interval to logarithmic binary rational interval.

Input
   I : an interval with binary rational endpoints.

Output
   J : the same interval represented with logarithmic binary
       rational endpoints.
======================================================================*/
#include "saclib.h"

Word BRILBRI(I)
	Word I;
{
	Word a,b,J;

Step1: /* Convert the endpoints. */
	FIRST2(I,&a,&b);
	a = RNLBRN(a);
	b = RNLBRN(b);
	J = LIST2(a,b);

Return: /* Return J. */
	return(J);
}
