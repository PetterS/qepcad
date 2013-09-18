/*=========================================================================
                            c <- DGCD(a,b)

Digit greatest common divisor.

Inputs
   a, b : BETA-digits, a >= b >= 0.

Outputs
   c : a BETA-digit, c = gcd(a,b).

Method
   The Euclidean algorithm with divisions performed by shifting and
   subtraction.
===========================================================================*/
#include "saclib.h"

Word DGCD(a,b)
       Word a,b;
{
       Word a1,a2,a3,b2,c,d;

Step1: /* b = 0. */
       if (b == 0) {
	  c = a;
	  goto Return; }

Step2: /* Initialize. */
       a1 = a;
       a2 = b;

Step3: /* Quotient is less than 8. */
       a3 = a1 - a2;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;
       a3 = d;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;
       a3 = d;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;
       a3 = d;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;
       a3 = d;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;
       a3 = d;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;
       a3 = d;
       d = a3 - a2;
       if (d < 0)
	  goto Step5;

Step4: /* Quotient is 8 or more; divide by shifting and subtraction. */
       b2 = a2 << 1;
       while (b2 <= a3)
	  b2 = b2 << 1;
       b2 = b2 >> 1;
       while (b2 >= a2) {
	  if (b2 < a3)
	     a3 = a3 - b2;
	  b2 = b2 >> 1; }

Step5: /* Check for completion. */
       if (a3 == 0) {
	  c = a2;
	  goto Return; }

Step6: /* Update and go back to Step3. */
       a1 = a2;
       a2 = a3;
       goto Step3;

Return: /* Prepare for return. */
       return(c);
}
