/*=====================================================================
                          t <- MMUPIT(p,A)

Medium Modulus univariate polynomial irreducibility test.

Inputs
   p : a medium prime.
   A : a polynomial over Z_p, 2 <= deg(A) <= beta^{1/2}.

Output
   t : 0 or 1.  t = 1 if A(x) is irreducible in Z_p[x], 0 otherwise.
=======================================================================*/
#include "saclib.h"

BDigit MMUPIT(p,A)
	BDigit p;
    	Word A;
{
	BDigit a,*Ap,n,t;
	Word B,C,L;

Step1: /* If p is small, check for a linear factor. */
	n = PDEG(A);
	if (p < n * n) {
	   Ap = MAPFMUP(A);
	   for (a = 0; a< p; a++) {
	      if (MMAPEVAL(p,Ap,a) == 0) {
	         MAPFREE(Ap);
	         t = 0;
	         goto Return; } }
	   MAPFREE(Ap); }

Step2: /* Test for a repeated factor. */
	B = MUPDER(p,A);
	C = MUPGCD(p,A,B);
	if (PDEG(C) > 0) {
	   t = 0;
	   goto Return; }
	L = MMPDDF(p,A);
	if (FIRST(FIRST(L)) == n)
	   t = 1;
        else
	   t = 0;

Return: /* Return t. */
	return(t);
}
