/*======================================================================
                           LBRNF(B,p,d,A)

Logarithmic binary rational to floating.

Inputs
   B : a logarithmic binary rational number.
   p : a BETA-digit, the desired precision.
   d : -1, 0 or +1, the rounding direction.
        -1 : down
         0 : nearest (mantissa even in case of a tie)
        +1 : up
   A :  an array of size at least p + 3.

Effect
   The specified p-precision software floating point number is placed
   in A.
========================================================================*/
#include "saclib.h"

void LBRNF(B,p,d,A)
	Word B;
	BDigit p,d,*A;
{
	Word b;
	BDigit e;

Step1: /* Apply IF. */
	if (B == 0)
	   IF(0,p,d,A);
	else {
	   FIRST2(B,&b,&e);
	   IF(b,p,d,A);
	   A[0] = A[0] - e; }

Return: /* Return. */
	return;
}
