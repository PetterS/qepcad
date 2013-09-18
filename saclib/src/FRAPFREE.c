/*===========================================================================
			  FRAPFREE(A)

Finite ring array polynomial free memory.

Inputs
  A : a pointer to an array, memory for which was allocated using FRAPGET.

Side effects
  The memory allocated to A is freed.
===========================================================================*/
#include "saclib.h"

void FRAPFREE(A)
       Word **A;
{
       Word d,i;

Step1: /* Determine how many coefficients. */
       d = FRAPSIZE(A);
       FREEARRAY(A[-1]);
       
Step2: /* Free memory of each coefficient. */
       for (i = 0; i <= d; i++)
	  MAPFREE(FRAPCF(A,i));

Step3: /* Free main array. */
       A = A - 1;
       FREEARRAY(A);

Return: /* Prepare for return. */
       return;
}
