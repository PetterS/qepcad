/*======================================================================
                      c <- LBRNMAX(a,b)

Logarithmic binary rational number max.

Inputs
  a, b : logarithmic binary rational numbers.  

Outputs
  c : a logarithmic binary rational number.  c = max(a,b).
======================================================================*/
#include "sac_ext.h"

Word LBRNMAX(Word a, Word b)
{
       Word c;

Step1:
       if (LBRNCOMP(a,b) >= 0)
         c = a;
       else
         c = b;

Return:
       return(c);
}
