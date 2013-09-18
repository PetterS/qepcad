/*===========================================================================
				INEGA(A,n)

Integer negation, array version.

Inputs
  A : in Z, in array representation.
  n : a BETA digit, the length of A.

Side effect
  A is replaced by -A.
===========================================================================*/
#include "saclib.h"

void INEGA(A,n)
       Word *A,n;
{
       Word i;

Step1: /* Negate each digit. */
       for (i = 0; i < n; i++)
	  A[i] = -A[i];

Return: /* Prepare for return. */
       return;
}
