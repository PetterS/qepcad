/*===========================================================================
			   DRPCC(m,a,b; u1,u2,v1,v2)

Digit restricted partial cosequence calculation.

Inputs
  a, b : BETA-digits, a >= b > 0.

Outputs
   u1, u2, v1, v2: BETA-digits.  Let A and B be positive integers such
   that, for some k >= 0, we have a = [A / 2^k] and b = [B / 2^k].
   Then, for some i, nearly as large as possible, A_i = u1 A + v1 B and
   A_{i+1} = u2 A + v2 B, where A_j is the j-th term of the remainder
   sequence of A and B.  Furthermore, |v2| < m or v1 <= 1.
===========================================================================*/
#include "saclib.h"

void DRPCC(m,a,b, u1_,u2_,v1_,v2_)
       Word m,a,b, *u1_,*u2_,*v1_,*v2_;
{
       Word a1,a2,a3,b2,d1,d2,d3,i,k,p,q,t1,t2,u1,u2,u3,v1,v2,v3;

Step1: /* Initialize. */
       a1 = a;
       a2 = b;
       u1 = 1;
       u2 = 0;
       v1 = 0;
       v2 = 1;

Step2: /* Is the quotient 1 or 2 ? */
       d1 = a1 - a2;
       d2 = d1 - a2;
       if (d2 < 0) {
	  a3 = d1;
	  u3 = u1 - u2;
	  v3 = v1 - v2;
	  goto Step4; }
       d3 = d2 - a2;
       if (d2 < 0) {
	  a3 = d2;
	  u3 = u1 - u2 - u2;
	  v3 = v1 - v2 - v2;
	  goto Step4; }

Step3: /* Quotient is at least 3, divide by shifting and subtraction. */
       k = 1;
       b2 = a2 << 2;
       while (b2 <= a1) {
	  b2 <<= 1;
	  k++; }
       b2 >>= 1;
       p = 1 << k;
       a3 = a1;
       q = 0;
       for (i = 0; i <= k; i++) {
	  if (b2 < a3) {
	     a3 -= b2;
	     q += p; }
	  p >>= 1;
	  b2 >>= 1; }
       u3 = u1 - q * u2;
       v3 = v1 - q * v2;

Step4: /* Check for completion. */
       if (v3 > 0) {
	  t1 = v3;
	  t2 = v3 - v2; }
       else {
	  t1 = -v3;
	  t2 = v2 - v3; }
       if (a3 < t1 || a2 - a3 < t2)
	  goto Return;
       if (t1 >= m) {
	  if (v1 == 0) {
	     u1 = u2;
	     u2 = u3;
	     v1 = v2;
	     v2 = v3; }
	  goto Return; }

Step5: /* Update sequence values, and loop. */
       a1 = a2;
       a2 = a3;
       u1 = u2;
       u2 = u3;
       v1 = v2;
       v2 = v3;
       goto Step2;

Return: /* Prepare for return. */
       *u1_ = u1;
       *u2_ = u2;
       *v1_ = v1;
       *v2_ = v2;
       return;
}
