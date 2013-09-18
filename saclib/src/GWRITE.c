/*======================================================================
                      GWRITE(a)

C integer write.  

Inputs
  a : a C integer.

Side effects
  a is written to the output stream.
======================================================================*/
#include "saclib.h"

void GWRITE(a)
       Word a;
{
       Word D[21],N,ap,q;

Step1: /* Write minus sign. */
       if (a < 0) {
	  ap = -a;
	  CWRITE('-'); }
       else
	  ap = a;

Step2: /* Convert to decimal. */
       N = 0;
       do {
	  q = ap / 10;
	  N = N + 1;
	  D[N] = ap - 10 * q;
	  ap = q; }
       while (ap != 0);

Step3: /* Write digits. */
       do {
	  CWRITE(D[N] + '0');
	  N = N - 1; }
       while (N != 0);

Return: /* Prepare for return. */
       return;
}
