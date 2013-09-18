/*===========================================================================
			      C <- IPIQ(r,A,b)

Integral polynomial integer quotient.

Inputs
  A : in Z[x_1,...,x_r].
  r : a BETA-digit, r >= 1, the number of variables.
  b : a non-zero integer which divides A.
 
Outputs
  C : in Z[x_1,...,x_r], C = A / b.
===========================================================================*/
#include "saclib.h"

Word IPIQ(r,A,b)
       Word r,A,b;
{
       Word Ap,C,a,c,e,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  C = 0;
	  goto Return; }

Step2: /* A /= 0. */
       Ap = A;
       rp = r - 1;
       C = NIL;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  if (rp == 0)
	     c = IEQ(a,b);
	  else
	     c = IPIQ(rp,a,b);
	  C = COMP2(c,e,C); }
       while (Ap != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
