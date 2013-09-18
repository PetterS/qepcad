/*===========================================================================
			       IQR(A,B; Q,R)

Integer quotient and remainder.  

Inputs
  A, B  : in Z, B /= 0.  

Outputs
  Q     : the quotient, integral part of A/B.
  R     : the remainder A - B * Q.
===========================================================================*/
#include "saclib.h"
#include <stdlib.h>
#define IQR_SIZE 100

void IQR(A,B, Q_,R_)
       Word A,B, *Q_,*R_;
{
       Word *Ah,Ap[IQR_SIZE],*Bh,Bp[IQR_SIZE],Q,Qp[IQR_SIZE],*Qh,R;
       Word a,ap,a0,a1,a2,b,bp,b0,b1,c,c0,c1,c2,
            h,hp,i,j,k,m,N,n,s,s1,s2,o,q;

Step1: /* B single-precision. */
       if (B < BETA) {
	  IDQR(A,B,&Q,&R);
	  goto Return; }

Step2: /* A single-precision. */
       if (A < BETA) {
	  Q = 0;
	  R = A;
	  goto Return; }

Step3: /* Copy |A| and |B| into arrays; determine lengths and signs. */
       IFLTA(A,Ap,IQR_SIZE,&Ah,&m,&s1,&o);
       IFLTA(B,Bp,IQR_SIZE,&Bh,&n,&s2,&o);

Step4: /* m <= n. */
       if ( (m < n) || (m == n && Ah[m-1] < Bh[n-1]) ) {
	  Q = 0;
	  R = A;
          goto Return; }

Step5: /* Normalize. */
       b = Bh[n-1];
       hp = PDLOG2(b);
       h = ZETA - hp;
       ap = 0;
       if (h > 0) {
	  for (i = 0; i < m; i++) {
	     a = Ah[i];
	     Ah[i] = ((a << h) & BETA1) | ap;
	     ap = a >> hp; }
	  bp = 0;
	  for (i = 0; i < n; i++) {
	     b = Bh[i];
	     Bh[i] = ((b << h) & BETA1) | bp;
	     bp = b >> hp; } }
       
Step6: /* Obtain leading digits of divisor. */
       b1 = Bh[n-1];
       b0 = Bh[n-2];
       
Step7: /* Get array for quotient. */
       if (m - n + 1 <= IQR_SIZE)
	  Qh = Qp;
       else 
	  Qh = GETARRAY(m-n+1);

Step8: /* Initialize loop. */
       j = m;
       k = m - n;

Step9: /* Obtain high-order digits of dividend. */
       if (j == m)
	  a2 = ap;
       else
	  a2 = Ah[j];
       a1 = Ah[j-1];
       a0 = Ah[j-2];

Step10: /* Compute quotient digit approximation q. */
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
       
Step11: /* Subtract q  times the remaining digits of the divisor. */
       c = 0;
       for (i = 0; i <= n - 3; i++) {
	  DPR(Bh[i],q,&c2,&c1);
	  a = Ah[j - n + i];
	  a = a - c;
	  if (a < 0) {
	     a = a + BETA;
	     c2 = c2 + 1; }
	  a = a - c1;
	  if (a < 0) {
	     a = a + BETA;
	     c2 = c2 + 1; }
	  c = c2;
	  Ah[j - n + i] = a; }
       a0 = a0 - c;
       if (a0 < 0) {
	  a0 = a0 + BETA;
	  a1 = a1 - 1;
	  if (a1 < 0) {
	     a1 = a1 + BETA;
	     a2 = a2 - 1; } }
       Ah[j - 2] = a0;
       Ah[j - 1] = a1;
       if (j < m)
	  Ah[j] = a2;

Step12: /* If the remainder is negative, decrease q by 1 and 
	   add the divisor to the remainder. */
       if (a2 < 0) {
	  q = q - 1;
	  c = 0;
	  for (i = 0; i <= n - 1; i++) {
	     a = Ah[j - n + i] + Bh[i] + c;
	     if (a >= BETA) {
		a = a - BETA;
		c = 1; }
	     else
		c = 0;
	     Ah[j - n + i] = a; }
	  if (j < m)
	     Ah[j] = 0; }

Step13: /* Store q and return for next quotient digit, if any. */
       Qh[k] = q;
       if (j > n) {
	  j = j - 1;
	  k = k - 1;
	  goto Step9; }

Step14: /* De-normalize quotient and remainder. */
       if (s2 > 0)
	  s = s1;
       else
	  s = -s1;
       Q = IFATL(Qh,m-n+1,s);
       if (h > 0) {
	  ap = 0;
	  N = (01 << h) - 1;
	  for (i = n - 1; i >= 0; i--) {
	     a = Ah[i];
	     Ah[i] = (a >> h) | ap; 
	     ap = (a & N) << hp; } }
       R = IFATL(Ah,n,s1);
       
Step15: /* Free dynamic arrays. */
       if (m > IQR_SIZE) 
	  FREEARRAY(Ah);
       if (n > IQR_SIZE) 
	  FREEARRAY(Bh);
       if (m - n + 1 > IQR_SIZE)
	  FREEARRAY(Qh);

Return: /* Prepare for return. */
       *Q_ = Q;
       *R_ = R;
       return;
}
