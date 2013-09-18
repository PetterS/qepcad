/*======================================================================
                      c <- RNMIN(a,b)

Rational number min.

Inputs
  a, b : rational numbers.

Outputs
  c : a rational number.  c = min(a,b).
======================================================================*/
#include "saclib.h"

Word RNMIN(a,b)
       Word a,b;
{
       Word c;

Step1:
       if (RNCOMP(a,b) <= 0)
         c = a;
       else
         c = b;

Return:
       return(c);
}
