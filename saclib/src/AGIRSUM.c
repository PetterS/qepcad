/*========================================================================
                           AGIRSUM(A,B,k,C)

Array Gaussian integer rotated sum.

Inputs
   A, B: array Gaussian integers.
   k : a BETA digit, k = 0. 1. 2 or 3.
   C : a Gaussian integer array.  The sizes of C[0] and C[1]
         must be at least as long as the maximum of the
         lengths of A and B plus 3.

Effect
   The sum of A and i^k * B is placed in C.
========================================================================*/
#include "saclib.h"

void AGIRSUM(A,B,k,C)
        BDigit **A,**B,k,**C;
{
	BDigit *T;

Step1: /* Replace B with i^k B. */
	if (k == 1 || k == 3) {
	   T = B[0];
	   B[0] = B[1];
	   B[1] = T; }
	if (k == 1 || k == 2)
	   B[0][0] = - B[0][0];
	if (k == 2 || k == 3)
	   B[1][0] = - B[1][0];

Step2: /* Add. */
	AGISUM(A,B,C);

Step3: /* Restore B. */
	if (k == 1 || k == 2) 
           B[0][0] = - B[0][0];
        if (k == 2 || k == 3)
           B[1][0] = - B[1][0];
	if (k == 1 || k == 3) {
           T = B[0];
           B[0] = B[1];
           B[1] = T; }

Return: /* Return. */
	return;
}
