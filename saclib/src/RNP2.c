/*======================================================================
                      r <- RNP2(k)

Rational number power of 2.  

Inputs
  k : a BETA-digit.  

Outputs
  r : 2^k, a rational number.
======================================================================*/
#include "saclib.h"

Word RNP2(k)
       Word k;
{
       Word a,h,r;

Step1: /* Compute. */
       h = ABS(k);
       a = IMP2(1,h);
       if (k >= 0)
	  r = LIST2(a,1);
       else
	  r = LIST2(1,a);

Return: /* Prepare for return. */
       return(r);
}
