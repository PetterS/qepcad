/*===========================================================================
			      A <- PFBRE(r,a)

Polynomial from base ring element.

Input
  r : a non-negative BETA-digit.
  a : an element of a ring R.

Output
  A : a represented as an element of R[x_1,...,x_r].
===========================================================================*/
#include "saclib.h"

Word PFBRE(r,a)
       Word r,a;
{
       Word A,i;

Step1: /* a = 0. */
       if (a == 0) {
	  A = 0;
	  goto Return; }

Step2: /* a != 0. */
       A = a;
       for (i = 1; i <= r; i++)
	  A = PMON(A,0);

Return: /* Prepare for return. */
       return(A);
}
