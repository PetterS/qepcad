/*======================================================================
			HIDWRITE(I,k)

Hardware interval decimal write.

Inputs
   I : a hardware interval.
   k : a positive beta-digit.

Effect
   The endpoints of I are written as decimal fractions
   with k digits following the decimal point.
======================================================================*/
#include "saclib.h"

void HIDWRITE(I,k)
	interval I;
	BDigit k;
{
	Word J;

Step1: /* Convert  and write. */
	   J = HILBRI(I);
	   LBRIDWRITE(J,k);

Return: /* Return. */
	return;
}
