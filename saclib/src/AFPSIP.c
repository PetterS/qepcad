/*======================================================================
                           AFPSIP(I,A,p,B)

Algebraic field polynomial to software interval polynomial.

Inputs
   I : a standard logarithmic binary rational interval containing 
       an algebraic number \alpha.
   A : a univariate polynomial of positive degree over the
       algebraic number field Q(\alpha).  Each nonzero coefficient
       of A is represented by a pair (r,a) where r is a
       rational number and a is an integral polynomial of
       degree less than the degree of \alpha.  Let n be the
       degree of A.
   p : a positive BETA-digit.
   B : an array of size at least 2(n + 1)(p + 3) + 1.

Effect
   A software interval polynomial of precision p containing A(x)
   is placed in B.
======================================================================*/
#include "saclib.h"

void AFPSIP(I,A,p,B)
	Word I,A;
	BDigit p,*B;
{
	BDigit *Ip,i,m,q1,q2,s;
	Word a,Ap;

Step1: /* Compute parameters. */
	m = PDEG(A);
	q1 = p + 3;
	q2 = q1 + q1;
	s = (m + 1) * q2 + 1;
	B[0] = m;

Step2: /* Convert isolating interval to floating point. */
	Ip = GETARRAY(q2);
	LBRISI(I,p,Ip);

Step3: /* Convert and evaluate coefficients. */
	Ap = A;
	for (i = m; i >= 0; i--) {
	   s = s - q2;
	   if (Ap == NIL || PDEG(Ap) < i)
	      ISI(0,p,B + s);
	   else {
	      Ap = RED(Ap);
	      ADV(Ap,&a,&Ap);
	      ANSI(Ip,a,B + s); } }
	   
Return: /* Return. */
	FREEARRAY(Ip);
	return;
}
