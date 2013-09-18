/*======================================================================
                        SIDWRITE(I,k)

Software interval decimal write.

Inputs
   I : a software interval.
   k : a positive beta-digit.

Effect
   The endpoints of I are written as decimal fractions
   with k digits following the decimal point.
======================================================================*/
#include "saclib.h"

void SIDWRITE(I,k)
	BDigit *I,k;
{
	Word J;

Step1: /* Convert to logarithmic binary rational and write. */
	J = SILBRI(I);
	LBRIDWRITE(J,k);

Return: /* Return. */
        return;
}
