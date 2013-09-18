/*======================================================================
                      t <- LBRNPROD(r,s)

Logarithmic binary rational number product.

Inputs
      r,s : logarithmic binary rational numbers.
Outputs
      t: logarithmic binary rational representation of r*s;

======================================================================*/
#include "saclib.h"

Word LBRNPROD(r,s)
       Word r,s;
{
  Word t,r1,r2,s1,s2;

Step1: /* Multiply numerators & add denominator exponents. */
  if (r == 0 || s == 0)
    t = 0;
  else {
    FIRST2(r,&r1,&r2);
    FIRST2(s,&s1,&s2);
    t = LIST2(IPROD(r1,s1),r2 + s2); }

Return: /* Prepare to return. */
  return t;
}
