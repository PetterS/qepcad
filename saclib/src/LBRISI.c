/*======================================================================
                           LBRISI(I,p,J)

Logarithmic binary rational interval to software interval.

Inputs
   I : a logarithmic binary rational interval.
   p : a BETA-digit, the desired precision.
   J : (pointer to) an array of size at least 2 p + 6.

Effect
   The smallest p-precision software interval containing I is placed
   in J.
======================================================================*/
#include "saclib.h"

void LBRISI(I,p,J)
       Word I;
       BDigit p;
       Word *J;
{

Step1: /* Apply LBRNF to endpoints. */
        LBRNF(FIRST(I),p,-1,J);
	LBRNF(SECOND(I),p,+1,J + p + 3);

Return: /* Return. */
        return;
}
