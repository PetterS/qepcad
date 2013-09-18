/*===========================================================================
			       n <- DLOG2(a)

Digit logarithm, base 2.

Inputs
  a  : a BETA-digit.

Outputs
  n  : a BETA-digit. If a = 0 then n = 0.  Otherwise
       n = floor(log2(|a|)) + 1, the bit-length of a.
===========================================================================*/
#include "saclib.h"

Word DLOG2(a)
       Word a;
{
       Word ab,n;

Step1: /* a = 0. */
       if (a == 0) {
	  n = 0;
	  goto Return; }

Step2: /* Use PDLOG2. */
       ab = absm(a);
       n = PDLOG2(ab);

Return: /* Prepare for return. */
       return(n);
}
