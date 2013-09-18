/*======================================================================
			IEEEDWRITE(F,k)

IEEE decimal write.

Inputs
   F : an ieee double.
   k : a positive beta-digit.

Effect
   F is printed as a rounded k-decimal digit fraction, with a
   trailing '+' or '-' indicating whether the exact value is
   larger or smaller.
======================================================================*/
#include "saclib.h"

void IEEEDWRITE(F,k)
	ieee F;
	BDigit k;
{
	Word G;

Step1: /* Convert  and write. */
	   G = IEEELBRN(F.num);
	   LBRNDWRITE(G,k);

Return: /* Return. */
	return;
}
