/*=======================================================================
                           B <-  MPFFEXP(p,F,A,e)

Medium prime finite field exponentiation.

Inputs
   p : a medium prime.
   F : an irreducible monic polynomial over Z_p in array representation
       of degree n defining a finite field GF(p^n).
   A : a nonzero element of GF(p^n) in array representation.
   e : a positive beta-integer.

Output
   B : B = A^e, an element of GF(p^n) in array representation.
=======================================================================*/
#include "saclib.h"

BDigit *MPFFEXP(p,F,A,e)
	BDigit p,*F,*A,e;
{
	BDigit f,*B,*C;

Step1: /* e = 1. */
	if (e == 1) {
	   B = MAPCOPY(A);
	   goto Return; }

Step2: /* Recursion. */
	f = e >> 1;
	B = MPFFEXP(p,F,A,f);
	C = MPFFPROD(p,F,B,B);
	MAPFREE(B);
	B = C;
	if (ODD(e)) {
	   C = MPFFPROD(p,F,B,A);
	   MAPFREE(B);
	   B = C; }

Return: /* Return B. */
	return(B);
}
