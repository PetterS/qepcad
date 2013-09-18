/*======================================================================
                      SISUM(I,J,K)

Software interval sum.

Inputs
   I, J : software intervals of the same precision, p.
   K : an array of size (at least) p + 3.

Effect
   The smallest p-precision software interval containing I + J
   is computed and stored in K.
======================================================================*/
#include "saclib.h"

void SISUM(I,J,K)
	BDigit *I,*J,*K;
{
	BDigit p,q;

Step1: /* Add corresponding endpoints. */
	p = I[2];
	q = p + 3;
        FSUM(I,J,-1,K);
        FSUM(I + q,J + q,+1,K + q);

Return: /* Return. */
	return;
}
