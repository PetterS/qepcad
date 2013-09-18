/*======================================================================
                      B <- RNLBRN(A)

Rational number to logarithmic binary rational number.

Input
   A : a binary rational number.

Output
   B : A in logarithmic representation.
======================================================================*/
#include "saclib.h"

Word RNLBRN(A)
       Word A;
{
       Word a,b,k,B;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* A /= 0. */
       FIRST2(A,&a,&b);
       if (b == 1) {
	  k = IORD2(a);
	  a = ITRUNC(a,k);
	  k = -k; }
       else
	  k = IORD2(b);
       B = LIST2(a,k);

Return: /* Prepare for return. */
	return(B);
}
