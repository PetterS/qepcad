/*===========================================================================
                         A <- PMONSV(r,a,i,e)

Polynomial monomial, specified variable.

Inputs
  r : a BETA-digit, r >= 1.
  a : in R, R a ring.
  i : a BETA-digit, 1 <= i <= r.
  e : a BETA-digit, e >= 0.

Outputs
  A : in R[x_1,...,x_r], A(x_1,...,x_r) = a x_i^e.
===========================================================================*/
#include "saclib.h"

Word PMONSV(r,a,i,e)
       Word r,a,i,e;
{
       Word A,j;

Step1: /* Construct the monomial. */
       A = a;
       for (j = 1; j <= r; j++) {
	 if (j == i) A = PMON(A,e);
	 else        A = PMON(A,0); }

Return: /* Prepare for return. */
       return(A);
}
