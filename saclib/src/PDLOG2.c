/*======================================================================
                      n <- PDLOG2(a)

Positive digit logarithm, base 2.

Inputs
  a  : a positive BETA-digit.

Outputs
  n  : a BETA-digit. n = floor(log2(a)) + 1, the bit-length of a.

Restriction
  This program requires that ZETA = 29.
======================================================================*/
#include "saclib.h"

Word PDLOG2(a)
       Word a;
{
       Word c,n;

Step1: /* Begin with binary search. */
       if (a >= TABP2[15])
          if (a >= TABP2[22]) {
	     if (a >= TABP2[26])
	        n = 29;
	     else
	        n = 25; }
	  else
	     if (a >= TABP2[18])
	        n = 21;
	     else
	        n = 17;
       else
          if (a >= TABP2[8])
	     if (a >= TABP2[11])
                n = 14;
             else
                n = 10;
          else
             if (a >= TABP2[4])
                n = 7;
             else
                n = 3;

Step2: /* Finish by shifting. */
       c = TABP2[n];
       while (a < c) {
	  n = n - 1;
	  c = c >> 1; }

Return: /* Prepare for return. */
       return(n);
}
