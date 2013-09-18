/*======================================================================
                           t <- LBRNFEC(B,p,A)

Logarithmic binary rational to floating, exact conversion.

Inputs
   B : a logarithmic binary rational number.
   p : a beta digit, the desired precision.
   A :  an array of size at least p + 3.

Output
   t : 0 or 1.

Effect
   If t = 0, B could not be exactly converted to a p-precision software
   float and the content of A is undefined.  If t = 1, the p-precision
   software float equal to B is placed in A.
========================================================================*/
#include "saclib.h"

BDigit LBRNFEC(B,p,A)
	Word B;
	BDigit p,*A;
{
	Word b;
	BDigit e,t;

Step1: /* Apply IFEC. */
	if (B == 0)
	   t = IFEC(0,p,A);
	else {
	   FIRST2(B,&b,&e);
	   t = IFEC(b,p,A);
	   A[0] = A[0] - e; }

Return: /* Return t. */
	return(t);
}
