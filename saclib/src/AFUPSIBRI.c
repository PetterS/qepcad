/*======================================================================
                      AFUPSIBRI(A,I,B,p; J,L)

Algebraic number field univariate polynomial software interval basis 
real root isolation.

Inputs
   A : the minimal integral polynomial of an algebraic number
       \alpha.
   I : a logarithmic open standard isolating interval for \alpha.
   B : a non-empty list of univariate polynomials over Q(\alpha).
       B is a squarefree basis. Each element of B has its
       nonzero coefficients represented by a pair (r,a) where
       r is a rational number and a is a univariate integral 
       polynomial of degree less than n.
   p : a positive beta integer, the precision of the software
       arithmetic to be employed.

Outputs
   J : a logarithmic open standard isolating interval for \alpha that
       is a subinterval of I, the smallest that could be obtained
       with precision p arithmetic.
   L : either 0 or a list (I_1,B_1,...,I_m,B_m).  (I_1,...,I_m)
       is a list of disjoint intervals, each of which is either
       open and standard or one-point.  Each I_j is an isolating
       interval for a root of B_j and each B_j is an element of B.
       Each root of each element of B is isolated by some I_j.
       The intervals have binary rational endpoints in rational
       representation and I_1 < I_2 < ... , I_m.  Furthermore,
       two intervals share an endpoint only if both are open.
       If L = 0, the program failed to produce such a list for the
       given inputs using p-precision arithmetic.
======================================================================*/
#include "saclib.h"

void AFUPSIBRI(A,I,B,p, J_,L_)
        Word A,I,B;
        BDigit p;
	Word *J_,*L_;
{
	BDigit *Ap,*bp,**C,*c,i,k,m,n,q1,q2,S,s,t;
	Word b,Bp,I1,I2,J,K,L,L1,Lp,M,T;

Step1: /* Convert the minimal polynomial to a software interval
          polynomial. */
        n = PDEG(A);
        q1 = p + 3;
        q2 = q1 + q1;
        S = (n + 1) * q2 + 1;
        Ap = GETARRAY(S);
        IPSIP(A,p,Ap);

Step2: /* Compute the trend of \alpha. */
	b = SECOND(I);
	bp = GETARRAY(q1);
	t = LBRNFEC(b,p,bp);
	J = I;
        L = 0;
	if (t == 0) {
	   FREEARRAY(bp);
	   goto Return; }
	t = SIPES(Ap,bp);
	FREEARRAY(bp);
	if (t == NIL)
	   goto Return;

Step3: /* Refine the isolating interval for \alpha. */
        J = SIPIR(Ap,I,t,- (p * ZETA));
        FREEARRAY(Ap);

Step4: /*  Isolate the real roots of each basis polynomial. */
	k = LENGTH(B);
	C = GETMATRIX(k,1);
	L = NIL;
	Bp = B;
	for (i = 0; i < k; i++) {
	   ADV(Bp, &b,&Bp);
	   m = PDEG(b);
	   s = (m + 1) * q2 + 1;
	   c = GETARRAY(s);
	   AFPSIP(J,b,p,c);
	   FREEARRAY(C[i]);
	   C[i] = c;
	   L1 = SIPRRID(c);
	   if (L1 == 0) {
	      L = 0;
	      goto Step8; }
	   t = c[s - q2 + 1];
	   if (EVEN(m))
	      t = -t;
	   while (L1 != NIL) {
	      ADV(L1, &K,&L1);
	      T = LIST3(i,K,t);
	      t = - t;
	      L = COMP(T,L); } }
	L = INV(L);

Step5: /* Refine and merge sort the intervals. */
	M = SIPIIRMS(L,C);
	if (M == 0) {
	   L = 0;
	   goto Step8; }

Step6: /* Extract the polynomials and intervals. */
	L = NIL;
	while (M != NIL) {
	   ADV(M, &T,&M);
	   i = FIRST(T);
	   b = LELTI(B,i + 1);
	   K = SECOND(T);
	   L = COMP2(b,K,L); }
	L = INV(L);

Step7: /* Convert the interval endpoints to rational number representation. */
	Lp = L;
	while (Lp != NIL) {
	   I1 = FIRST(Lp);
	   I2 = LIST2(LBRNRN(FIRST(I1)),LBRNRN(SECOND(I1)));
	   SFIRST(Lp,I2);
	   Lp = RED2(Lp); }

Step8: /* Free arrays. */
	for (i = 0; i < k; i++)
	   FREEARRAY(C[i]);
	FREEARRAY(C);
	
Return: /* Return J and L. */
	*J_ = J;
	*L_ = L;
	return;
}
