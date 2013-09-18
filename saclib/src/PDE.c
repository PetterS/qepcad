/*===========================================================================
                              B <- PDE(r,A,i,k)

Polynomial division of exponents.

Inputs
   r : a positive beta digit.
   A : a nonzero polynomial in r variables over any domain
       such that every exponent of x^i in A is divisible by k.
   i : a beta digit, 1 <= i <= r.
   k : a positive beta digit.

Output
   B : the polynomial obtained from A by dividing every 
       exponent of x^i in A by k.
======================================================================*/
#include "saclib.h"

Word PDE(r,A,i,k)
	BDigit i,k,r;
	Word A;
{
	BDigit e;
	Word a,Ap,B;

Step1: /* i = r. */
	if (i == r) {
	   Ap = A;
	   B = NIL;
	   while (Ap != NIL) {
	      ADV2(Ap,&e,&a,&Ap);
	      B = COMP2(a,e/k,B); }
	   B = INV(B);
	   goto Return; }

Step2: /* i < r. */
	Ap = A;
	B = NIL;
	while (Ap!= NIL) {
	   ADV2(Ap,&e,&a,&Ap);
	   B = COMP2(PDE(r-1,a,i,k),e,B); }
	B = INV(B);
	   
Return: /* Return B. */
	return(B);
}
