/*===========================================================================
			   IDQRA(A,m,b,Q; k,r)

Integer-digit quotient and remainder, array version.

Inputs
  A : an array containing a positive integer A.
  m : the length of A in BETA-digits.
  b : a positive BETA-digit.
  Q : an array at least m elements long.

Outputs
  k : the length of Q' in BETA-digits.
  r : a BETA-digit, r = A - b * Q' and r >= 0.

Side effects
  Q' is put in Q.
===========================================================================*/
#include "saclib.h"

void IDQRA(A,m,b,Q, k_,r_)
       Word *A,m,b,*Q, *k_,*r_;
{
       Word Qp,a,a0,a1,h,hp,i,k,q,r;

Step1: /* A single-precision. */
       if (m == 1) {
	  a = A[0];
	  Qp = a / b;
	  Q[0] = Qp;
	  if (Qp == 0)
	     k = 0;
	  else
	     k = 1;
	  r = a - b * Qp;
	  goto Return; }

Step2: /* Copy A to Q. */
       for (i = 0; i < m; i++)
	  Q[i] = A[i];

Step3: /* b = 1. */
       r = 0;
       if (b == 1) {
	  k = m;
	  goto Return; }

Step4: /* b < 2^15. */
       if (b < (01 << 15)) {
	  for (i = m - 1; i >= 0; i--) {
	     PHDQR(r,Q[i],b,&q,&r);
	     Q[i] = q; }
	  goto Step6; }
       
Step5: /* b >= 2^15. */
       h = PDLOG2(b);
       hp = ZETA - h;
       b <<= hp;
       a1 = Q[m - 1];
       r = a1 >> h;
       for (i = m - 1; i > 0; i--) {
	  a0 = ((Q[i] << hp) & BETA1) | (Q[i - 1] >> h);
	  PNDQR(r,a0,b,&q,&r);
	  Q[i] = q; }
       a0 = (Q[0] << hp) & BETA1;
       PNDQR(r,a0,b,&q,&r);
       Q[0] = q;
       r >>= hp;

Step6: /* Determine length of quotient. */
       k = m;
       while (Q[k - 1] == 0)
	  k--;

Return: /* Prepare for return. */
       *k_ = k;
       *r_ = r;
       return;
}
