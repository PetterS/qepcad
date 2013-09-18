/*======================================================================
                      SICOPY(A,B)

Software interval copy.

Inputs
   A : a software interval.
   B : an array large enough for a copy of A.

Effect
   The software interval A is copied into B.
======================================================================*/
#include "saclib.h"

void SICOPY(A,B)
	BDigit *A,*B;
{

	BDigit i,p,q1,q2;

Step1: /* Copy A. */
	p = A[2];
	q1 = p + 3;
	q2 = q1 + q1;
	for (i = 0; i < q2; i++)
	   B[i] = A[i];

Return: /* Return. */
	return;
}
