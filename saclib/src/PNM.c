/*=======================================================================
                         n = PNM(r,A)

Polynomial number of monomials.

Inputs
   r : a positive beta digit.
   A : a polynomial in r variables over an arbitrary domain, in
       recursive representation.

Output
   n : the number of monomials in A.
=======================================================================*/
#include "saclib.h"

BDigit PNM(r,A)
	BDigit r;
	Word A;
{
	BDigit n,rp;
	Word a,Ap;

Step1: /* A = 0. */
	if (A == 0) {
	   n = 0;
	   goto Return; }

Step2: /* r = 1. */
	if (r == 1) {
	   n = LENGTH(A) >> 1;
	   goto Return; }

Step3: /* r > 1. */
	n = 0;
	Ap = A;
	rp = r - 1;
	while (Ap != NIL) {
	   Ap = RED(Ap);
	   ADV(Ap,&a,&Ap);
	   n = n + PNM(rp,a); }

Return: /* Return n. */
	return(n);
}
