/*=======================================================================
                         AIQR(A,B,Q,R,T)

Array integer quotient and remainder.

Inputs
   A, B    : integers in array representation, B /= 0.
   Q, R, T : arrays.  Let m = L(A), n = L(B).  The size of Q must
             be at least m - n + 3 and at least 3.  The size of
             R must be at least m + 3.  The size of T must be at 
	     least n + 2.

Effect
   The quotient [A / B], the integral part of A / B, is placed
   in the array Q.  The remainder, A - B * [A / B], is placed
   in the array R.
========================================================================*/
#include "saclib.h"

void AIQR(A,B,Q,R,T)
	BDigit *A,*B,*Q,*R,*T;
{
	BDigit a,a0,a1,a2,b,b0,b1,c,c0,c1,c2,h,hp,i,j,k,m,n,q,r;

Step1: /* A = 0 or L(A) < L(B). */
	m = A[1];
	n = B[1];
	if (A[0] == 0 || m < n) {
	   Q[0] = 0;
	   Q[1] = 0;
	   Q[2] = 0;
	   AICOPY(A,R);
	   goto Return; }

Step2: /* L(B) = 1. */
	if (n == 1) {
	   a1 = 0;
	   b = B[2];
	   for (j = m + 1; j >= 2; j--) {
	      a0 = A[j];
	      DQR(a1,a0,b, &q,&r);
	      Q[j] = q;
	      a1 = r; }
           R[2] = r;
	   goto Step12; }

Step3: /* Normalize. */
	b = B[n +1];
	h = PDLOG2(b);
	hp = ZETA - h;
	AIMP2(A,hp,R);
	AIMP2(B,hp,T);

Step4: /* Obtain the two leading digits of the divisor. */
	b1 = T[n + 1];
	b0 = T[n];

Step5: /* Initialize the division loop. */
	m = R[1];
	R[1] = m + 1;
	R[m + 2] = 0;
	j = m;

Step6: /* Get the three leading digits of the dividend. */
	a2 = R[j + 2];
	a1 = R[j + 1];
	a0 = R[j];

Step7: /* Compute a quotient digit approximation, q. */
	if (a2 == b1) {
           q = BETA - 1;
           a1 = a1 + a2;
           a2 = 0;
           if (a1 >= BETA) {
              a1 = a1 - BETA;
              a2 = 1; } }
        else {
           PNDQR(a2,a1,b1,&q,&a1);
           a2 = 0; }
	DPR(b0,q,&c1,&c0);
	a0 = a0 - c0;
	if (a0 < 0) {
	   a0 = a0 + BETA;
	   a1 = a1 - 1; }
	a1 = a1 - c1;
        if ( a1 < 0) {
           a1 = a1 + BETA;
           a2 = a2 - 1; }
        if (a2 < 0) {
           q = q - 1;
           a0 = a0 + b0;
           if (a0 >= BETA) {
              a0 = a0 - BETA;
              a1 = a1 + 1; }
           a1 = a1 + b1;
	   if (a1 >= BETA) {
              a1 = a1 - BETA;
              a2 = a2 + 1; } }

Step8: /* If q /= 0, subtract q times the remaining digits of the 
          divisor. */
	if (q == 0)
	   goto Step9;
	c = 0;
        for (i = 2; i <= n - 1; i++) {
           DPR(T[i],q,&c2,&c1);
	a = R[j - n + i];
           a = a - c;
           if (a < 0) {
              a = a + BETA;
              c2 = c2 + 1; }
           a = a - c1;
           if (a < 0) {
              a = a + BETA;
              c2 = c2 + 1; }
           c = c2;
           R[j - n + i] = a; }
	a0 = a0 - c;
        if (a0 < 0) {
           a0 = a0 + BETA;
           a1 = a1 - 1;
           if (a1 < 0) {
              a1 = a1 + BETA;
              a2 = a2 - 1; } }
        R[j] = a0;
        R[j + 1] = a1;
        R[j + 2] = a2;

Step9: /* If the remainder is negative, decrease q by 1 and
          add the divisor to the remainder. */
	if (a2 < 0) {
           q = q - 1;
           c = 0;
           for (i = 2; i <= n + 1; i++) {
              a = R[j - n + i] + T[i] + c;
              if (a >= BETA) {
                 a = a - BETA;
                 c = 1; }
              else
                 c = 0;
              R[j - n + i] = a; }
           R[j + 2] = 0; }

Step10: /* Store q and return for the next quotient digit, if any. */
	Q[j - n + 2] = q;
	if (j > n) {
           j = j - 1;
           goto Step6; }

Step11: /* De-normalize the remainder. */
	if (hp > 0)
	   AIDP2(R,hp,R);

Step12: /* Store the lengths of Q and R, */
	j = m - n + 1;
	if (Q[j + 1] == 0)
	   j = j - 1;
	Q[1] = j;
	k = n;
	while (k >= 1 && R[k + 1] == 0)
	   k = k - 1;
	R[1] = k;

Step13: /* Store the signs of Q and R. */
	Q[0] = A[0];
	if (B[0] < 0)
	   Q[0] = - Q[0];
	if (j == 0 && Q[2] == 0)
	   Q[0] = 0;
	if (k == 0 && R[2] == 0)
	   R[0] = 0;
	else
	   R[0] = A[0];

Return: /* Return. */
	return;
}
