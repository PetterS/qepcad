/*=====================================================================
                      T <- LBRNDIF(R,S)

Logarithmic binary rational number difference.

Inputs
   R, S : logarithmic binary rational numbers.

Outputs
   T    : R - S, a logarithmic binary rational integer.
======================================================================*/
#include "saclib.h"

Word LBRNDIF(R,S)
       Word R,S;
{
       Word T;

Step1: /* Do it. */
       T = LBRNSUM(R,LBRNNEG(S));

Return: /* Return T. */
       return(T);
}
