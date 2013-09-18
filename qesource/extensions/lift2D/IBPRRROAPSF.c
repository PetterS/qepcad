/* Integral bivariate polynomial real root refinement over algebraic point*/
/*======================================================================
                      IBPRRIOAPSF(M,I,B,p,k, J_,L_)

Integral bivariate polynomial real root isolation over an algebraic
point - software floating point version

Inputs
   A : the minimal integral polynomial of an algebraic number
       \alpha.
   I : a logarithmic open standard isolating interval for \alpha.
   B : an integral bivariate
       polynomial of degree less than n.
   p : a positive beta integer, the precision of the software
       arithmetic to be employed.
   k : if k is NIL, only root isolation is performed.  Otherwise, k
       is the target precision of refinement - i.e. we try to refine
       isolating intervals to a width of 1/2^k.

Outputs
   J : a logarithmic open standard isolating interval for \alpha that
       is a subinterval of I, the smallest that could be obtained
       with precision p arithmetic.
   L : If L = 0 then root isolation failed, otherwise L is a list  
       (I_1,...,I_m) of strongly disjoint intervals, each of which has
       logarithmic binary rational endpoints and is either open
       or one-point, and that are isolating intervals for the
       real roots of B(alpha,y).
======================================================================*/
#include "lift2d.h"

void IBPRRIOAPSF(Word M, Word I, Word B, BDigit p, BDigit k, Word *J_, Word *L_)
{
	BDigit *Mp,*bp,*c,i,m,n,q1,q2,S,s,t;
	Word b,Bp,I1,I2,J,K,L,Ls,Lp,T,Jp;

Step1: /* Convert the minimal polynomial to a software interval
          polynomial. */
        n = PDEG(M);
        q1 = p + 3;
        q2 = q1 + q1;
        S = (n + 1) * q2 + 1;
        Mp = GETARRAY(S);
        IPSIP(M,p,Mp);

Step2: /* Compute the trend of \alpha. */
	b = SECOND(I);
	bp = GETARRAY(q1);
	t = LBRNFEC(b,p,bp);
	J = I;
        L = 0;
	if (t == 0) {
	   FREEARRAY(bp);
	   goto Return; }
	t = SIPES(Mp,bp);
	FREEARRAY(bp);
	if (t == NIL)
	   goto Return;

Step3: /* Refine the isolating interval for \alpha. */
        J = SIPIR(Mp,I,t,- (p * ZETA));
        FREEARRAY(Mp);

Step4: /*  Isolate the real roots of B(J)[Y]. */
	L = NIL;
	m = PDEG(B);
	s = (m + 1) * q2 + 1;
	c = GETARRAY(s);
	IBPELBRISIPR(B,J,p,c);
	L = SIPRRID(c);
	if (L == 0)
	  goto Step8;
	t = c[s - q2 + 1];
	if (EVEN(m))
	  t = -t;

Step5: /* Refine the intervals. */
	if (k == NIL)
	  goto Return;
	Ls = NIL;
	for(Lp = L; Lp != NIL; Lp = RED(Lp))
	{
	  Jp = SIPIR(c,FIRST(Lp),t,-k);
	  Ls = COMP(Jp,Ls);
	  t = -t;
	}
	L = CINV(Ls);


Step8: /* Free arrays. */
	FREEARRAY(c);
	
Return: /* Return J and L. */
	*J_ = J;
	*L_ = L;
	return;
}

