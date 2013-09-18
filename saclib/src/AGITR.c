/*=======================================================================
                            AGITR(A,n,k,B)

Array Gaussian integer truncate and round.

Inputs
   A    : a nonzero array Gaussian integer.
   n, k : nonnegative BETA digits, with 0 <= k < ZETA.
   B    : an array for a Gaussian integer.  Let m = L(A).  The
          sizes of B[0] and B[1] must be at least min(3,m - n + 3).

Effect
   Let N = n * ZETA + k.  {A / 2^N}, the nearest Gaussian integer
   to A / 2^N is placed in B.
========================================================================*/
#include "saclib.h"

void AGITR(A,n,k,B)
	BDigit **A,n,k,**B;
{

Step1: /* Apply AITR. */
	AITR(A[0],n,k,B[0]);
	AITR(A[1],n,k,B[1]);

Return: /* Return. */
	return;
}
