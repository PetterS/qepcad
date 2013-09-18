/*========================================================================
                           AGISUM(A,B,C)

Array Gaussian integer sum.

Inputs
   A, B: array Gaussian integers.
   C   : an array for a Gaussian integer.  The sizes of C[0]
         and C[1] must be at least as long as the maximum of the 
         lengths of A and B plus 3.

Effect
   The sum of A and B is placed in C.
========================================================================*/
#include "saclib.h"

void AGISUM(A,B,C)
        BDigit **A,**B,**C;
{

Step1: /* Add the parts. */
	AISUM(A[0],B[0],C[0]);
	AISUM(A[1],B[1],C[1]);

Return: /* Return. */
	return;
}
