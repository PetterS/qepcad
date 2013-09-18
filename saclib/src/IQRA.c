/*===========================================================================
			   IQRA(A,m,B,n,Q; m,k)

Integer quotient and remainder, array version.

Inputs
   A, B : Arrays containing positive integers A' and B', with A' >= B' > 0.
   m, n : The lengths in BETA-digits of A and B.
   Q    : an array of length 1 + length(floor(A/B)).

Outputs
   mp : the length in BETA-digits of the remainder A - floor(A/B).
   k  : the length in BETA-digits of the quotient floor(A/B).

Side effects:
  The remainder replaces A' in A, and the quotient is put in Q.
===========================================================================*/
#include "saclib.h"

void IQRA(A,m,B,n,Q, mp_,k_)
       Word *A,m,*B,n,*Q, *mp_,*k_;
{
       Word *Bt,N,a,a0,a1,a2,ap,b,b0,b1,bp,c,c0,c1,c2,h,hp,i,j,k,mp,q,r;

Step1: /* B single-precision. */
       if (n == 1) {
	  IDQRA(A,m,B[0],Q, &k,&r);
	  A[0] = r;
	  if (r == 0)
	     mp = 0;
	  else
	     mp = 1;
	  goto Return; }

Step2: /* m <= n. */
       if ( (m < n) || (m == n && A[m-1] < B[n-1]) ) {
	  Q[0] = 0;
	  mp = m;
	  k = 0;
          goto Return; }

Step3: /* Normalize. */
       Bt = GETARRAY(n);
       b = B[n-1];
       hp = PDLOG2(b);
       h = ZETA - hp;
       ap = 0;
       if (h > 0) {
	  for (i = 0; i < m; i++) {
	     a = A[i];
	     A[i] = ((a << h) & BETA1) | ap;
	     ap = a >> hp; }
	  bp = 0;
	  for (i = 0; i < n; i++) {
	     b = B[i];
	     Bt[i] = ((b << h) & BETA1) | bp;
	     bp = b >> hp; } }
       else
	  for (i = 0; i < n; i++)
	     Bt[i] = B[i];
       
Step4: /* Obtain leading digits of divisor. */
       b1 = Bt[n-1];
       b0 = Bt[n-2];
       
Step5: /* Initialize loop. */
       j = m;
       k = m - n;

Step6: /* Obtain high-order digits of dividend. */
       if (j == m)
	  a2 = ap;
       else
	  a2 = A[j];
       a1 = A[j-1];
       a0 = A[j-2];

Step7: /* Compute quotient digit approximation q. */
       if (a2 == b1) {
	  q = BETA - 1;
	  a1 += a2;
	  if (a1 >= BETA) {
	     a1 -= BETA;
	     a2--; } }
       else {
	  PNDQR(a2,a1,b1,&q,&a1);
	  a2 = 0; }
       DPR(b0,q,&c1,&c0);
       a0 -= c0;
       if (a0 < 0) {
	  a0 += BETA;
	  a1--; }
       a1 -= c1;
       if (a1 < 0) {
	  a1 += BETA;
	  a2--; }
       if (a2 < 0) {
	  q--;
	  a0 += b0;
	  if (a0 >= BETA) {
	     a0 -= BETA;
	     a1++; }
	  a1 += b1;
	  if (a1 >= BETA) {
	     a1 -= BETA;
	     a2++; } }
       
Step8: /* Subtract q  times the remaining digits of the divisor. */
       if (q != 0) {
	  c = 0;
	  for (i = 0; i <= n - 3; i++) {
	     DPR(Bt[i],q,&c2,&c1);
	     a = A[j - n + i];
	     a -= c;
	     if (a < 0) {
		a += BETA;
		c2++; }
	     a -= c1;
	     if (a < 0) {
		a += BETA;
		c2++; }
	     c = c2;
	     A[j - n + i] = a; }
	  a0 -= c;
	  if (a0 < 0) {
	     a0 += BETA;
	     a1--;
	     if (a1 < 0) {
		a1 += BETA;
		a2--; } }
	  A[j - 2] = a0;
	  A[j - 1] = a1;
	  if (j < m)
	     A[j] = a2; }

Step9: /* If the remainder is negative, decrease q by 1 and 
	   add the divisor to the remainder. */
       if (a2 < 0) {
	  q--;
	  c = 0;
	  for (i = 0; i <= n - 1; i++) {
	     a = A[j - n + i] + Bt[i] + c;
	     if (a >= BETA) {
		a -= BETA;
		c = 1; }
	     else
		c = 0;
	     A[j - n + i] = a; }
	  if (j < m)
	     A[j] = 0; }

Step10: /* Store q and return for next quotient digit, if any. */
       Q[k] = q;
       if (j > n) {
	  j--;
	  k--;
	  goto Step6; }

Step11: /* De-normalize quotient and remainder. */
       if (h > 0) {
	  ap = 0;
	  N = (01 << h) - 1;
	  for (i = n - 1; i >= 0; i--) {
	     a = A[i];
	     A[i] = (a >> h) | ap; 
	     ap = (a & N) << hp; } }
       mp = n;
       while (mp >= 1 && A[mp - 1] == 0)
	  mp--;
       k = m - n + 1;
       while (Q[k - 1] == 0)
	  k--;
       FREEARRAY(Bt);

Return: /* Prepare for return. */
       *mp_ = mp;
       *k_ = k;
       return;
}
