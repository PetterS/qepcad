/*===========================================================================
                    DDPCC(a1,a0,b1,b0; u1,u2,v1,v2)

Double-digit partial cosequence calculation.

Inputs:
   a1, a0, b1, b0: non-negative BETA-digits, with a1 >= BETA/2, b1 > 0
   and a = a1 * BETA + a0 >= b = b1 * BETA + b0.

Outputs:
   u1, u2, v1, v2: BETA-digits.  Let A and B be positive integers such
   that, for some k >= 0, we have a = [A / 2^k] and b = [B / 2^k].
   Then, for some i, nearly as large as possible, A_i = u1 A + v1 B and
   A_{i+1} = u2 A + v2 B, where A_j is the j-th term of the remainder
   sequence of A and B.
===========================================================================*/
#include "saclib.h"

void DDPCC(a1,a0,b1,b0,u1_,u2_,v1_,v2_)
       Word a1,a0,b1,b0,*u1_,*u2_,*v1_,*v2_;
{
       Word a10,a11,a20,a21,a30,a31,b20,b21,c0,c1,d,i,k,q,
            u1,u2,u3,v1,v2,v3,w;

Step1: /* Initialize. */
       a11 = a1;
       a10 = a0;
       a21 = b1;
       a20 = b0;
       u1 = 1;
       v1 = 0;
       u2 = 0;
       v2 = 1;

Step2: /* Set b2 = b21 * BETA + b20 = a2 * 2^k, where k is
          such that a1 / a2 < 2^{k+1}, and k is minimal. */
       k = 0;
       b21 = a21 << 1;
       while (b21 <= a11) {
          b21 = b21 << 1;
          k = k + 1; }
       b21 = b21 >> 1;
       if (k > 0) {
          b21 = b21 | (a20 >> (ZETA - k));
          b20 = (a20 << k) & BETA1; }
       else
          b20 = a20;

Step3: /* Divide by shifting and subtraction. */
       d = 01 << k;
       a31 = a11;
       a30 = a10;
       q = 0;
       for (i = 0; i <= k; i++) {
          if ((b21 < a31) || (b21 == a31 && b20 <= a30)) {
             a31 = a31 - b21;
             a30 = a30 - b20;
             if (a30 < 0) {
                a30 = a30 + BETA;
                a31 = a31 - 1; }
             q = q + d; }
          d = d >> 1;
          b20 = (b20 >> 1) | ((b21 & 01) << (ZETA - 1));
          b21 = b21 >> 1; }
       u3 = u1;
       v3 = v1;
       switch (q) {
          case 2:  u3 -= u2;
                   v3 -= v2;
          case 1:  u3 -= u2;
                   v3 -= v2;
                   break;
	  default: u3 -= q * u2;
                   v3 -= q * v2; }

Step4: /* Test for completion. */
       if (a31 == 0) {
          if (a30 >= absm(v3)) {
             c0 = a20 - a30;
             if (c0 < 0) {
                c1 = a21 - 1;
                c0 += BETA; }
             else
                c1 = a21;
             w = v2 - v3;
             w = absm(w);
             if (w >= BETA) {
                w -= BETA;
                c1--; }
             c0 -= w;
             if (c1 > 0 || (c1 == 0 && c0 >= 0)) {
                u1 = u2;
                v1 = v2;
                u2 = u3;
                v2 = v3; } }
          goto Return; }
       c1 = a21 - a31;
       if (c1 <= 1) {
          c0 = a20 - a30;
          if (c1 == 1)
             c0 = c0 + BETA;
          w = v3 - v2;
          if (c0 < absm(w))
             goto Return; }

Step5: /*  Update sequence values and return to Step 2. */
       a11 = a21;
       a10 = a20;
       a21 = a31;
       a20 = a30;
       u1 = u2;
       v1 = v2;
       u2 = u3;
       v2 = v3;
       goto Step2;

Return: /* Return. */
       *u1_ = u1;
       *u2_ = u2;
       *v1_ = v1;
       *v2_ = v2;
       return;
}
