/*======================================================================
                      s <- LBRNP2PROD(r,k)

Logarithmic binary rational number power of 2 product.

Inputs
      r : a logarithmic binary rational number.
      k : a BETA-digit.
Outputs
      s : a logarithmic binary rational representation of r*2^k

======================================================================*/
#include "saclib.h"

Word LBRNP2PROD(r,k)
       Word r,k;
{
       Word s,r1,r2;

Step1: /* Construct r*2^k. */
       if (r == 0)
	 s = 0;
       else {
	 FIRST2(r,&r1,&r2);
	 s = LIST2(r1, r2 - k); }

Return: /* Prepare to return. */
       return (s);
}
