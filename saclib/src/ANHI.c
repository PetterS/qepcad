/*======================================================================
                           ANHI(I,a; J,t)

Algebraic number to hardware interval.

Inputs
   I : a hardware interval containing an algebraic number \alpha.
   a : a nonzero element of Q[\alpha].  a is represented by a list 
       (r,A), where r is a rational number and A is a nonzero
       univariate integral polynomial A(x) of degree less than n 
       such that  r * A(\alpha) = a.

Outputs
   J : If t = 1, J is a hardware interval containing a; otherwise 
       t = 0, failure is due to exponent limitation, and the value 
       of J is undefined.
   t : 0 or 1.
======================================================================*/
#include "saclib.h"

void ANHI(I,a,J_,t_)
	interval I;
	Word a;
	interval *J_;
	BDigit *t_;
{
	interval *B,J,K;
	BDigit i,m;
	Word A,Ap,b,c,d,e,r,t;

Step1: /* Get an array B for a hardware interval polynomial. */
	FIRST2(a,&r,&A);
	m = PDEG(A);
	B = GETHIPARRAY(m);

Step2: /*  Let r = c / d. */
	FIRST2(r,&c,&d);

Step3: /* Convert rational coefficients to intervals. */
	Ap = A;
	for (i = m; i >= 0; i--) {
	   if (Ap == NIL || FIRST(Ap) < i)
	      IHI(0,&B[i],&t);
	   else {
	      Ap = RED(Ap);
	      ADV(Ap,&e,&Ap);
	      if (c == 1) 
	         b = e;
	      else
	         b = IPROD(c,e);
	      RHI(b,d,&K,&t);
	      if (t == 0)
	         goto Step5;
	      B[i] = K; } }

Step4: /* Evaluate the hardware interval polynonmial at I. */
	FPCATCH();
	J = HIPIEVAL(m,B,I);
	if (FPCHECK() == 1) {
	   t = 0;
	   FPCATCH(); }

Step5: /* Free array B. */
	FREEARRAY(B);

Return: /* Return J and t. */
	*J_ = J;
	*t_ = t;
	return;
}
