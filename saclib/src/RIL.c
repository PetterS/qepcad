/*======================================================================
                      d <- RIL(I)

Rational interval length.

Inputs
  I : a rational interval.  I = (a,b).

Outputs
  d : a rational number.  d = Length(I) = b-a.
======================================================================*/
#include "saclib.h"

Word RIL(I)
       Word I;
{
       Word d;  
       Word a1,a2;


Step1: /* Subract left endpoint from right endpoint. */
       FIRST2(I,&a1,&a2);
       d = RNDIF(a2,a1);

Return:
       return(d);
}
