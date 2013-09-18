/*=====================================================================
			L <- IBPPOL(A,a,k)

Integral bivariate polynomial points on line.

Inputs
   A:  an integral bivariate polynomial A(x,y) of positive
       degree in y.
   a:  a binary rational number.
   k:  an integer.

Output
   L:  a list of logarithmic binary rational numbers (a_1, ...,a_r)
       such that r is the number of real roots of A(a,y) and the i-th
       real root is either equal to a_i or is in the open interval
       (a_i,a_i + 2^{-k}.
======================================================================*/
#include "saclib.h"

Word IBPPOL(A,a,k)
	Word A,a,k;
{
	Word B,d,I,L,Lp;

Step1: /* Compute B(y) = A(a,y). */
	B = IPBREI(2,A,1,a);

Step2: /* Isolate and refine the real roots of B. */
	if (PDEG(B) == 0)
	   L = NIL;
	else
	   L = IPRRIRDB(B,-k);

Step3: /* Replace each isolating interval with its left endpoint. */
	Lp = NIL;
	while (L != NIL) {
	   ADV(L,&I,&L);
	   d = FIRST(I);
	   Lp = COMP(d,Lp); }
	L = INV(Lp);

Return: /* Return L. */
	return(L);
}
