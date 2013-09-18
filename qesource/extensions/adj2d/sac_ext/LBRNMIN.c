/*======================================================================
                      c <- LBRNMIN(a,b)

Logarithmic binary rational number min.

Inputs
  a, b : logarithmic binary rational numbers.

Outputs
  c : a logarithmic binary rational number.  c = min(a,b).
======================================================================*/
#include "sac_ext.h"

Word LBRNMIN(Word a, Word b)
{
       Word c;

Step1:
       if (LBRNCOMP(a,b) <= 0)
         c = a;
       else
         c = b;

Return:
       return(c);
}
