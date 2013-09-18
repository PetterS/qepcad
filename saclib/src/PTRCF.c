/*===========================================================================
			       C <- PTRCF(A)

Polynomial trailing coefficient.

Input
  A : in R[x], where R is a ring.
  
Output
  C : in R, the trailing coefficient of A.
===========================================================================*/
#include "saclib.h"

Word PTRCF(A)
       Word A;
{
       Word Ap,C,k;

Step1: /* A = 0. */
       if (A == 0) {
	  C = 0;
	  goto Return; }

Step2: /* A != 0. */
       Ap = A;
       do
	  PADV(Ap,&k,&C,&Ap);
       while (Ap != 0);

Return: /* Prepare for return. */
       return(C);
}
