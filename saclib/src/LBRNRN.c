/*========================================================================
                      B <- LBRNRN(A)

Logarithmic binary rational number to rational number.

Input
   A : a logarithmic binary rational number.

Output
   B : A represented as a rational number.
=========================================================================*/
#include "saclib.h"

Word LBRNRN(A)
       Word A;
{
       Word a,b,k,B;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* A /= 0. */
       FIRST2(A,&a,&k);
       if (k >= 0)
	  b = IMP2(1,k);
       else {
	  a = IMP2(a,-k);
	  b = 1; }
       B = LIST2(a,b);

Return: /* Prepare for return. */
	return(B);
}
