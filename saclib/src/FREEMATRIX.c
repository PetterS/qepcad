/*===========================================================================
			FREEMATRIX(A,n)

Free matrix.

Input
  A : a pointer to an array of pointers to Words.  The memory for A
      was allocated by the function GETMATRIX.
  n : the dimension of A (the number of pointers).

Side effect
  The memory allocated to A is freed.
===========================================================================*/
#include "saclib.h"

void FREEMATRIX(A,n)
       Word **A,n;
{
       Word i;
Step1:  /* Free memory. */
       for (i = 0; i < n; i++)
	  FREEARRAY(A[i]);
       free(A);

Return: /* Prepare for return. */
       return;
}
