/*=======================================================================
                        D = AGICDAE(A,B)

Array Gaussian integer greatest common divisor, approximative Euclidean.

Inputs
   A, B : array Gaussian integers.

Output
   C : an array Gaussian integer, a greatest common divisor of A and B.
========================================================================*/
#include "saclib.h"

BDigit **AGIGCDAE(A,B)
	BDigit **A,**B;
{
	BDigit **D,**Dt,**E,**Et,**F,**Ft,*Gt,**Q,*T1,*T2,*T3,**U;
	BDigit d,dp,h,k,kp,M,m,N,n,np,p,t;
	BDigit d1,d2,e,e1,e2,f1,f2,q1,q2,r1,r2;

BDigit g,i;
BDigit j,*W,*X;
BDigit **S;
BDigit I,P,T,V;

Step1: /* Set the precision. */
	d = 8;

Step2: /* Compute the initial bit lengths. */
	AGIBL(A, &m,&h);
        M = m * ZETA + h;
        AGIBL(B, &n,&k);
        N = n * ZETA + k;

Step3: /* Get Arrays. */
	p = m + n + 4;
	D = GETMATRIX(2,p);
	E = GETMATRIX(2,p);
	F = GETMATRIX(2,p);
	Dt = GETMATRIX(2,p);
	Et = GETMATRIX(2,p);
	Ft = GETMATRIX(2,p);
	Q = GETMATRIX(2,p);
	U = GETMATRIX(2,p);
	Gt = GETARRAY(p);
	T1 = GETARRAY(p);
	T2 = GETARRAY(p);
	T3 = GETARRAY(p);

Step4: /* Let D be the longer of A and B, E the shorter. */
	if (M >= N) {
	   AGICOPY(A,D);
	   AGICOPY(B,E); }
	else {
	   AGICOPY(B,D);
	   AGICOPY(A,E);
	   t = m;
	   m = n;
	   n = t;
	   t = h;
	   h = k;
	   k = t;
	   t = M;
	   M = N;
	   N = t; }

Step5: /* E = 0? */
	if (N == 0)
	   goto Step10;

Step6: /* Truncate D and E. */
	dp = M - N + d;
	if (M - N + dp + dp <= ZETA) {
	   np = n;
	   kp = k - dp;
	   if (kp < 0) {
	      np = np - 1;
	      kp = kp + ZETA; }
	   if (np < 0) {
	      np = 0;
	      kp = 0; }
	   d1 = AITRS(D[0],np,kp);
	   d2 = AITRS(D[1],np,kp);
	   e1 = AITRS(E[0],np,kp);
	   e2 = AITRS(E[1],np,kp); }
	else {
	   np = dp / ZETA;
	   kp = dp - np * ZETA;
	   np = n - np;
	   kp = k - kp;
	   if (kp < 0) {
	      kp = kp + ZETA;
	      np = np - 1; }
	   if (np < 0) {
	      np = 0;
	      kp = 0; }
	   AGITR(D,np,kp,Dt);
	   AGITR(E,np,kp,Et); }

Step7: /* Compute the approximate nearest quotient, Q. */
	if (M - N + dp + dp <= ZETA) {
	   e = e1 * e1 + e2 * e2;
	   f1 = d1 * e1 + d2 * e2;
	   f2 = d2 * e1 - d1 * e2;
	   q1 = f1 / e;
	   r1 = f1 - e * q1;
	   if (f1 >= 0 && r1 + r1 > e)
	      q1 = q1 + 1;
	   else if (f1 <= 0 && r1 + r1 < - e)
	      q1 = q1 - 1;
	   q2 = f2 / e;
           r2 = f2 - e * q2;
           if (f2 >= 0 && r2 + r2 > e)
              q2 = q2 + 1;
           else if (f2 <= 0 && r2 + r2 < - e)
              q2 = q2 - 1;
           Q[0][1] = 1;
           Q[0][0] = SIGN(q1);
           Q[0][2] = ABS(q1);
           Q[1][1] = 1;
           Q[1][0] = SIGN(q2);
           Q[1][2] = ABS(q2); }
	else {
	   Et[1][0] = - Et[1][0];
	   AGIPROD(Dt,Et,Ft,T1,T2);
	   AGINORM(Et,Gt,T1,T2);
	   AINQ(Ft[0],Gt,Q[0],T1,T2,T3);
	   AINQ(Ft[1],Gt,Q[1],T1,T2,T3); }

Step8: /* Compute F = D - E * Q. */
	Q[0][0] = - Q[0][0];
	Q[1][0] = - Q[1][0];
	AGIPROD(E,Q,U,T1,T2);
	AGISUM(D,U,F);

Step9: /*Update variables for next loop pass. */
        D = E;
        E = F;
	F = D;
	M = N;
        m = n;
        h = k;
        AGIBL(E, &n,&k);
        N = n * ZETA + k;
        goto Step5;

Step10: /* Free arrays. */
	FREEMATRIX(E,2);
	FREEMATRIX(F,2);
	FREEMATRIX(Dt,2);
	FREEMATRIX(Et,2);
	FREEMATRIX(Ft,2);
	FREEMATRIX(Q,2);
	FREEMATRIX(U,2);
	FREEARRAY(Gt);
	FREEARRAY(T1);
	FREEARRAY(T2);
	FREEARRAY(T3);

Return: /* Return(D). */
	return(D);
}
