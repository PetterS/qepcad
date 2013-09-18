/*===========================================================================
			      B <- PPLT(e,a,A)

Polynomial prefix leading term.

Inputs
  e : a BETA-digit, e >= 0.
  a : in R, where R is a ring.
  A : in R[x].  Either A = 0 or deg(A) < e.

Output
  B : in R[x], B = a x^e + A.
===========================================================================*/
#include "saclib.h"

Word PPLT(e,a,A)
       Word e,a,A;
{
       Word B;

Step1: /* Compute. */
       if (a == 0)
	  B = A;
       else
	  if (A == 0)
	     B = LIST2(e,a);
	  else
	     B = COMP2(e,a,A);

Return: /* Prepare for return. */
       return(B);
}
