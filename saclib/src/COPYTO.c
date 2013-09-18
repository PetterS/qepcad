/*===========================================================================
			       COPYTO(A,B,n)

Copy array to array.

Inputs
  A, B : arrays of length >= n.
  n    : positive BETA-digit.

Effect : B[0],...,B[n-1] is copied into A[0],...,A[n-1].
===========================================================================*/
#include "saclib.h"

void COPYTO(A,B,n)
	Word *A,*B,n;
{
        Word i;

Step1: /* Do it. */
       for (i = 0; i < n; i++)
         A[i] = B[i];

Return: /* Prepare for return. */
        return;
}
