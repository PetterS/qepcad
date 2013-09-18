/*=======================================================================
                        AGIDP2(A,k,B)

Array Gaussian integer division by a power of 2.

Inputs
   A : an array Gaussian integer.
   k : a BETA integer, 0 <= k < ZETA.
   B : a Gaussian integer array.

Effect
   The integral part of A / 2^k os placed in B.  Note that B may
   be the same array as A.
========================================================================*/
#include "saclib.h"

void AGIDP2(A,k,B)
        BDigit **A,k,**B;
{

Step1: /* Apply AIDP2. */
	AIDP2(A[0],k,B[0]);
	AIDP2(A[1],k,B[1]);

Return: /* Return. */
	return;
}
