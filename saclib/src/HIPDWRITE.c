/*======================================================================
			HIPDWRITE(n,A,k)

Hardware interval polynomial decimal write.

Inputs
   n : a positive BETA-digit.
   A : in HI[x], deg(A) = n.
   k : a positive beta-digit.

Effect
   A is written as a polynomial in x with the coefficients
   written as intervals, whose endpoints have k decimal digits
   after the decomal point.  An end-of-line character follows
   the polynomial.
======================================================================*/
#include "saclib.h"

void HIPDWRITE(n,A,k)
	BDigit n;
	interval *A;
	BDigit k;
{
	BDigit i;
	Word I;

Step1: /* Convert and write coefficients. */
	for (i = n; i >= 0; i--) {
           HIDWRITE(A[i],k);
           SWRITE(" x^");
           IWRITE(i);
           if (i != 0)
              SWRITE(" + "); }
        SWRITE("\n");

Return: /* Return. */
	return;
}
