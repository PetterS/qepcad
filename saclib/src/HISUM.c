/*======================================================================
                      K <- HISUM(I,J)

Hardware interval sum.

Inputs
   I, J : Hardware intervals.  

Output
   K : the smallest hardware interval containing I + J.

Warning
   HISUM is not floating-point overflow-underflow protected.
======================================================================*/
#include "saclib.h"

interval HISUM(I,J)
	interval I,J;
{
	interval K;

Step1: /* Add corresponding endpoints. */
	rounddown();
        K.left = I.left + J.left;
        roundup();
        K.right = I.right + J.right;

Return: /* Return K. */
	return(K);
}
