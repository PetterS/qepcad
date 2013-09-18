/*===========================================================================
			L <- IBCOEFFS(n)

Integer binomial coefficients.

Input
  n : a BETA-digit, n >= 0.

Output
  L : a list (b_0,...,b_n) of the binomial coefficients b_i = (n choose i).
===========================================================================*/
#include "saclib.h"

Word IBCOEFS(n)
       Word n;
{
       Word A,i,Lp,L,np;

Step1: /* n = 0. */
       if (n == 0) {
	  L = LIST1(1);
	  goto Return; }

Step2: /* General case. */
       np = (n-1)/2;
       A = 1;
       L = LIST1(A);
       for (i = 0; i < np; i++) {
	  A = IBCIND(A,n,i);
	  L = COMP(A,L); }
       Lp = CINV(L);
       if (EVEN(n)) {
	  A = IBCIND(A,n,np);
	  L = COMP(A,L); }
       L = CONC(Lp,L);

Return: /* Prepare for return. */
       return(L);
}
