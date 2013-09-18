/*======================================================================
			HIPLWRITE(n,A)

Hardware interval polynomial logarithmic write.

Inputs
   n : a positive BETA-digit.
   A : in HI[x], deg(A) = n.

Effect
   The coefficients of A are written as logarithmic binary
   rational intervals, one per line, beginning with the leading
   coefficient.
======================================================================*/
#include "saclib.h"

void HIPLWRITE(n,A)
	BDigit n;
	interval *A;
{
	BDigit i;
	Word I;

Step1: /* Convert and write coefficients. */
	for (i = n; i >= 0; i--) {
	   I = HILBRI(A[i]);
	   LBRIWRITE(I);
	   SWRITE("\n"); }

Return: /* Return. */
	return;
}
