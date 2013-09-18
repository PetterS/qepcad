/*======================================================================
                      Ib <- LBRNFIE(I,e)

Logarithmic binary rational number from integer and exponent.

Inputs
      I : an integer.
      e : a BETA-digit.
Outputs
      R : logarithmic binary rational representation of I*2^e.

======================================================================*/
#include "saclib.h"

Word LBRNFIE(I,e)
       Word I,e;
{
      Word R;

Step1: /* Compute I*2^e. */
      R = LBRNP2PROD( ILBRN(I) , e );

Return: /* Prepare to return. */
       return (R);
}
