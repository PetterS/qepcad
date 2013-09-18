/*===========================================================================
			      c <- BDGCD(a,b)

Binary digit greatest common divisor.

Inputs
  a, b : BETA-digits, a >= b >= 0.

Outputs
  c : a BETA-digit, c = gcd(a,b).

Method
  The binary gcd algorithm is used.
===========================================================================*/
#include "saclib.h"

Word BDGCD(a,b)
       Word a,b;
{
       Word a1,a2,a3,c,e;

Step1: /* b = 0. */
       if (b == 0) {
	  c = a;
	  goto Return; }

Step2: /* Compute highest power e of 2 dividing the gcd. */
       a1 = a;
       a2 = b;
       e = 0;
       while (((a1 & 1) == 0) && ((a2 & 1) == 0)) {
	  a1 >>= 1;
	  a2 >>= 1;
	  e++; }

Step3: /* Compute gcd of a/2^e and b/2^e. */
       while ((a1 & 1) == 0)
	  a1 >>= 1;
       while ((a2 & 1) == 0)
	  a2 >>= 1;
       if (a1 < a2) {
	  a3 = a1;
	  a1 = a2;
	  a2 = a3; }
       while (a2 != 0) {
	  a3 = a1 - a2;
	  if (a3 == 0)
	     goto Step4;
	  while ((a3 & 1) == 0)
	     a3 >>= 1;
	  if (a3 < a2) {
	     a1 = a2;
	     a2 = a3; }
	  else
	     a1 = a3; }

Step4: /* Multiply by 2^e. */
       c = a1 << e;

Return: /* Prepare for return. */
       return(c);
}
