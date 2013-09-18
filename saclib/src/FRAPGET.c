/*===========================================================================
			A <- FRAPGET(d,n)

Finite ring array polynomial get memory.

Inputs
  d, n: positive BETA-digits.

Outputs
  A : a pointer to an array large enough to hold an element of
      (Z/(m)[x])/(M)[y] having degree d, where M has degree n.
===========================================================================*/
#include <stdio.h>
#include "saclib.h"

Word **FRAPGET(d,n)
       Word d,n;
{
       Word **A,i;

Step1: /* Allocate memory for polynomial. */
       A = (Word **)malloc((d+2)*sizeof(Word *));
       if (A == NULL)
          FAIL("FRAPGET","Out of memory.");
       A = A + 1;
       A[-1] = GETARRAY(2);
       FRAPSIZE(A) = d;
       for (i = 0; i <= d; i++)
	  FRAPCF(A,i) = MAPGET(n);

Return: /* Prepare for return. */
       return(A);
}
