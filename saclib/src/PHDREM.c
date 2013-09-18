/*===========================================================================
			   r <- PHDREM(a1,a0,b)

Positive half-digit remainder.

Inputs
   a1, a0, b : BETA-integers with a1 and a0 non-negative, 0 < b < 2^15
               and a = a1 * BETA + a0 < b * BETA.

Outputs
   r : a BETA-integer, the remainder of (a1 * BETA + a0) modulo b,
       0 <= r < b.

Restriction: This program is valid only if the word length is 32
   bits and ZETA = 29.
===========================================================================*/
#include "saclib.h"

Word PHDREM(a1,a0,b)
       Word a1,a0,b;
{
       Word a,ap,c,c1,c0,q1,q0,r;

Step1: /* Compute q1 = [[a / 2^15] / b]. */
       ap = (a1<<14) | (a0 >> 15);
       q1 = ap / b;

Step2: /* Subtract 2^15 * b * q1 from a. */
       c = b * q1;
       c1 = c >> 14;
       c0 = (c << 15) & BETA1;
       a0 = a0 - c0;
       if (a0 < 0) {
	  a0 = a0 + BETA;
	  a1 = a1 - 1; }
       a1 = a1 - c1;

Step3: /* Compute q0 = [a / b]. */
       a = a0;
       if (a1 > 0)
	  a = a + BETA;
       q0 = a / b;

Step4: /* Compute r = a - b * q0. */
       c = b * q0;
       r = a0 - c;
       if (r < 0)
	  r = r + BETA;

Return: /* Prepare for return. */
       return(r);
}
