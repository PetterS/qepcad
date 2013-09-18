/*===========================================================================
				 CLEAR(A,n)

Clear array.

Inputs
  A    : array of length >= n.
  n    : positive BETA-digit.

Effect : A[0],...,A[n-1] are set to 0.
===========================================================================*/
#include "saclib.h"

void CLEAR(A,n)
	Word *A,n;
{
        Word i;

Step1: /* Do it. */
       for (i = 0; i < n; i++)
         A[i] = 0;

Return: /* Prepare for return. */
        return;
}
