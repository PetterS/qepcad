/*======================================================================
                      J <- RINEG(I)

Rational interval negation.

Inputs
  I : a rational interval.
Outputs
  J : a rational interval.  J = -I.
======================================================================*/
#include "saclib.h"

Word RINEG(I)
       Word I;
{
       Word J;
       Word a1,a2;

Step1: /* Get endpoints of I and J. */
       FIRST2(I,&a1,&a2);

Step2: /* Negate endpoints. */
       J = LIST2(RNNEG(a2),RNNEG(a1));

Return:
       return(J);
}
