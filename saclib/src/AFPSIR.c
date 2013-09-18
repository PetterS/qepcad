/*======================================================================
                      K = AFPSIR(p,I,B,J)

Algebraic field polynomial software interval refinement.

Inputs
   p : a nonnegative BETA digit (the precision).
   I : a standard logarithmic binary rational that is a refined 
       isolating interval for an algebraic number alpha.
       I must be exactly convertible to a precision p
       software interval.
   B : a univariate polynomial of positive degree over Q(alpha).
       Each coefficient of B is represented as a rational
       number and a univariate polynomial over Z[alpha].
   J : a standard logarithmic binary rational isolating interval
       for a root beta of B(x).

Output
   K : a standard logarithmic binary rational isolating interval
       for beta, as small as could be achieved using precision p
       software interval arithmetic, where p is the precision of I.
======================================================================*/
#include "saclib.h"

Word AFPSIR(p,I,B,J)
	BDigit p;
	Word I,B,J;
{
	BDigit *Bp,n,q,S,t,*T1,*T2;
	Word b2,J2,K;

Step1: /* Convert B to a software interval polynomial. */
	q = p + p + 6;
	n = PDEG(B);
	S = (n + 1) * q + 1;
	Bp = GETARRAY(S);
	AFPSIP(I,B,p,Bp);
	
Step2: /* Compute the trend of beta. */
	b2 = SECOND(J);
	J2 = LIST2(b2,b2);
	T1 = GETARRAY(q);
	LBRISI(J2,p,T1);
	T2 = GETARRAY(q);
	SIPEVAL(Bp,T1,T2);
	FREEARRAY(T1);
	t = SISIGN(T2);
	FREEARRAY(T2);
	if (t == NIL) {
	   K = J;
	   goto Step4; }

Step3: /* Refine J. */
	K = SIPIR(Bp,J,t,-p * ZETA);

Step4: /* Free array Bp. */
	FREEARRAY(Bp);

Return: /* Return K. */
	return(K);
}
