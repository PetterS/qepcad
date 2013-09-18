/*======================================================================
                           AFPHIP(I,A; B,t)

Algebraic field polynomial to hardware interval polynomial.

Inputs
   I : a hardware interval containing an algebraic number \alpha.
   A : a univariate polynomial of positive degree over the
       algebraic number field Q(\alpha).  Each nonzero coefficient
       of A is represented by a pair (r,a) where r is a
       rational number and a is an integral polynomial of
       degree less than the degree of \alpha.

Outputs
   B : if t = 1, B is a hardware interval polynomial containing A(x).
       Otherwise t = 0 and the value of B is undefined due to
       exponent limitation.
   t : 0 or 1.
======================================================================*/
#include "saclib.h"

void AFPHIP(I,A,B_,t_)
	interval I;
	Word A;
	interval **B_;
	BDigit *t_;
	
{
	interval *B;
	BDigit i,m,t;
	Word a,Ap;
	Word V,v;

Step1: /* Get an array for B. */
	m = PDEG(A);
	B = GETHIPARRAY(m);

Step2: /* Convert and evaluate coefficients. */
	Ap = A;
	for (i = m; i >= 0; i--) {
	   if (Ap == NIL || PDEG(Ap) < i)
	      IHI(0,&B[i],&t);
	   else {
	      Ap = RED(Ap);
	      ADV(Ap,&a,&Ap);
	      ANHI(I,a,&B[i],&t);
	      if (t == 0)
	         goto Return; } }
	   
Return: /* Return B and t. */
	*B_ = B;
	*t_ = t;
	return;
}
