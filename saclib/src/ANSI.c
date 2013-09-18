/*======================================================================
                           ANSI(I,a,J)

Algebraic number to software interval.

Inputs
   I : a software interval containing an algebraic number \alpha.
       Let p be the precision of I.
   a : a nonzero element of Q[\alpha].  a is represented by a list 
       (r,A), where r is a rational number and A is a nonzero
       univariate integral polynomial A(x) of degree less than 
       deg(\alpha) such that  r * A(\alpha) = a.
   J : an array of (at least) 2(p + 3) words.

Effect
   A software interval of precision p containing a is placed in J.
======================================================================*/
#include "saclib.h"

void ANSI(I,a,J)
	BDigit *I;
	Word a;
	BDigit *J;
{
	BDigit *B,*Bp,i,m,p,q1,q2,s;
	Word b,c,d,e,A,Ap,r;

Step1: /* Get an array B for a software interval polynomial. */
	p = I[2];
	q1 = p + 3;
	q2 = q1 + q1;
	FIRST2(a,&r,&A);
	m = PDEG(A);
	s = (m + 1) * q2 + 1;
	B = GETARRAY(s);
	B[0] = m;

Step2: /*  Let r = c / d. */
	FIRST2(r,&c,&d);

Step3: /* Convert rational coefficients to software intervals. */
	Ap = A;
	Bp = B + s - q2;
	for (i = m; i >= 0; i--) {
	   if (Ap == NIL || FIRST(Ap) < i)
	      ISI(0,p,Bp);
	   else {
	      Ap = RED(Ap);
	      ADV(Ap,&e,&Ap);
	      b = IPROD(c,e);
	      RSI(p,b,d,Bp); }
	   Bp = Bp - q2; }

Step4: /* Evaluate the software interval polynonmial at I. */
	SIPEVAL(B,I,J);

Step5: /* Free array B. */
	FREEARRAY(B);

Return: /* Return. */
	return;
}
