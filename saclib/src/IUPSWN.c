/*===========================================================================
			 b <- IUPSWN(A)

Integral univariate polynomial, square of the weighted norm.

Input
  A : in Z[x].

Output
  b : in Z, the square of the weighted norm of A.
      If A = sum_{i=0}^n a_i,
      then b = sum_{i=0}^n ceiling(a_i^2/(n choose i)).
===========================================================================*/
#include "saclib.h"

Word IUPSWN(A)
       Word A;
{
       Word b,n,C,Ap,i,a,e,a2,c,r,s;

Step1: /* A = 0. */
       if (A == 0) {
          b = 0;
          goto Return; }

Step2: /* Compute the binomial coefficients. */
       n = PDEG(A);
       C = IBCOEFS(n);

Step3: /* Compute weighted sum. */
       Ap = A;
       b = 0;
       i = n;
       do {
          a = PLDCF(Ap);
          e = PDEG(Ap);
          a2 = IPROD(a,a);
	  while (e < i) {
	     C = RED(C);
	     i--; }
	  ADV(C,&c,&C);
	  i--;
          r = RNRED(a2,c);
	  s = RNCEIL(r);
          b = ISUM(b,s);
          Ap = PRED(Ap); }
       while (Ap != 0);

Return: /* Prepare for return. */
       return(b);
}
