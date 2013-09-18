/*======================================================================
                      J <- SIAFEE(B,I,p)

Software interval algebraic field element evaluation.

Inputs
   B : a univariate rational polynomial, represented as a rational
       number and a positive primitive integral polynomial.
   I : a logarithmic binary rational interval containing an
       algebraic number alpha..
   p : a positive BETA-digit.

Output
   J : a logarithmic binary rational interval containing B(alpha).

Method
   B is converted to a p-precision software interval polynomial B',
   I is converted to a p-precision software interval I', and J'
   = B'(I'), evaluated with p-precision software interval arithmetic.
   J' is then converted to a logarithmic binary rational interval J.
======================================================================*/
#include "saclib.h"

Word SIAFEE(B,I,p)
	Word B,I;
	BDigit p;
{
	BDigit *Ip,*Jp,q;
	Word J;

Step1: /* B = 0? */
	if (B == 0) {
	   J = LIST2(0,0);
	   goto Return; }

Step2: /* ANSI converts and evaluates B. */
	q = p + p + 6;
	Ip = GETARRAY(q);
	LBRISI(I,p,Ip);
	Jp = GETARRAY(q);
	ANSI(Ip,B,Jp);
	J = SILBRI(Jp);
	FREEARRAY(Ip);
	FREEARRAY(Jp);

Return: /* Return J. */
	return(J);
}
