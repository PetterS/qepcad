/*======================================================================
                      c <- RNMAX(a,b)

Rational number max.

Inputs
  a, b : rational numbers.  

Outputs
  c : a rational number.  c = max(a,b).
======================================================================*/
#include "saclib.h"

Word RNMAX(a,b)
       Word a,b;
{
       Word c;

Step1:
       if (RNCOMP(a,b) >= 0)
         c = a;
       else
         c = b;

Return:
       return(c);
}
