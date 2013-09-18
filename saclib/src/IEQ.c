/*===========================================================================
                               C <- IEQ(A,B)

Integer exact quotient.

Inputs
  A,B : in Z, B /= 0, B a divisor of A.

Output
  C   : the quotient A/B.
===========================================================================*/
#include "saclib.h"
#define IEQ_SIZE 100

Word IEQ(A,B)
       Word A,B;
{
       Word C;
       Word Ab[IEQ_SIZE],Bb[IEQ_SIZE],Cb[IEQ_SIZE];
       Word *Ah,*Bh,*Ch;
       Word Ap,App,Bp,Bpp;
       Word J,K,L,M,N,u,v,w;
       Word a,a1,a2,ah,ap1,ap2,b,b1,b2,bh,bp,bp1,bp2,c,cp,d,e,f,g;
       Word i,j,k,m,n;

Step1: /* A single-precision. */
       if (A < BETA) { 
          C = A / B;
          goto Return; }

Step2: /* B single-precision. */
       if (B < BETA) {
          C = IDEQ(A,B);
          goto Return; }

Step3: /* Skip common trailing zero BETA-digits. */
       Ap = A;
       Bp = B;
       while (Bp != NIL && FIRST(Bp) == 0) {
          Ap = RED(Ap);
          Bp = RED(Bp); }

Step4: /* Bp single-precision. */
       if (RED(Bp) == NIL) {
          b = FIRST(Bp);
          C = IDEQ(Ap,b);
          goto Return; }

Step5: /*  Compute lengths and signs. */
       J = 0;
       App = Ap;
       Bpp = Bp;
       while (Bpp != NIL) {
	  ah = FIRST(App);
	  App = RED(App);
	  bh = FIRST(Bpp);
	  Bpp = RED(Bpp);
	  J = J + 1; }
       K = 1;
       while (App != NIL) {
	  ah = FIRST(App);
	  App = RED(App);
	  K = K + 1; }
       ah = absm(ah);
       bh = absm(bh);
       if (ah + 1 < bh)
	  K = K - 1;
       b = FIRST(Bp);
       v = signm(b);
       a = 0;
       App = Ap;
       while (a == 0) {
	  a = FIRST(App);
	  App = RED(App); }
       u = SIGN(a);
       if (v > 0)
	  w = u;
       else
	  w = - u;

Step6: /* Get arrays for A, B and C. */
       L = minm(J,K);
       if (K < IEQ_SIZE) {
	  Ah = Ab;
	  Ch = Cb; }
       else {
	  Ah = GETARRAY(K + 1);
	  Ch = GETARRAY(K + 1); }
       if (L < IEQ_SIZE)
	  Bh = Bb;
       else
	  Bh = GETARRAY(L + 1);

Step7: /* Copy digits of A and B, made positive, into arrays. */
       if (u > 0)
	  for (i = 0; i <= K; i++) {
	     Ah[i] = FIRST(Ap);
	     Ap = RED(Ap); }
       else
	  for (i = 0; i <= K; i++) {
	     Ah[i] = - FIRST(Ap);
	     Ap = RED(Ap); }
       if (v > 0) {
	  for (i = 0; i < L; i++) {
	     Bh[i] = FIRST(Bp);
	     Bp = RED(Bp); }
	  if (Bp != NIL)
	     Bh[L] = FIRST(Bp);
	  else
	     Bh[L] = 0; }
       else {
	  for (i = 0; i < L; i++) {
	     Bh[i] = - FIRST(Bp);
	     Bp = RED(Bp); }
	  if (Bp != NIL)
	     Bh[L] = - FIRST(Bp);
	  else
	     Bh[L] = 0; }

Step8: /* Count trailing zero bits. */
       b = Bh[0];
       n = 0;
       while ((b & 01) == 0) {
	  b = b >> 1;
	  n = n + 1; }

Step9: /* If n > 0 divide both numbers by 2^n (by shifting). */
       if (n == 0) goto Step10;
       m = ZETA - n;
       N = (01 << n) - 1;
       for (i = 0; i < K; i++) {
	  a1 = Ah[i];
	  ap1 = a1 >> n;
	  a2 = Ah[i + 1];
	  ap2 = (a2 & N) << m;
	  ap1 = ap1 | ap2;
	  Ah[i] = ap1; }
       for (i = 0; i < L; i++) {
	  b1 = Bh[i];
	  bp1 = b1 >> n;
	  b2 = Bh[i + 1];
	  bp2 = (b2 & N) << m;
	  bp1 = bp1 | bp2;
	  Bh[i] = bp1; }

Step10: /* Compute inverse of b modulo BETA.*/
       b = Bh[0];
       bp = MDINVB(b);

Step11: /* K = 1? */
       if (K == 1) {
	  DPR(Ah[0],bp,&cp,&C);
	  if (w < 0)
	     C = -C;
          goto Return; }

Step12: /* Divide by Jebelean's method. */
       d = 0;
       for (k = 0; k < K; k++) {
	  DPR(Ah[k],bp,&cp,&c);
	  Ch[k] = c;
	  if (k == K - 1)
	     goto Step13;
	  g = 0;
	  M = minm(L,K - k);
	  for (i = 0; i < M; i++) {
	     j = i + k;
	     DPR(c,Bh[i],&e,&f);
	     a = Ah[j];
	     a = a - g;
	     if (a < 0) {
		a = a + BETA;
		e = e + 1; }
	     a = a - f;
	     if (a < 0) {
		a = a + BETA;
		e = e + 1; }
	     Ah[j] = a;
	     g = e; }
	  j = i + k;
	  if (j < K) {
	     a = Ah[j];
	     a = a - g - d;
	     if (a < 0) {
		a = a + BETA;
		d = 1; }
	     else
                d = 0;
	     Ah[j] = a; } }

Step13: /* Copy result to a list. */
       C = IFATL(Ch,K,w);

Step14: /* Free dynamic arrays. */
       if (K >= IEQ_SIZE) {
	  FREEARRAY(Ah);
	  FREEARRAY(Ch); }
       if (L >= IEQ_SIZE)
	  FREEARRAY(Bh);

Return: /* Prepare for return. */
        return(C);
}
