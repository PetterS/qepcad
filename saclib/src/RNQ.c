/*======================================================================
                      T <- RNQ(R,S)

Rational number quotient.  

Inputs
  R,S : rational numbers, S non-zero.

Outputs  
  T   : R/S.
======================================================================*/
#include "saclib.h"

Word RNQ(R,S)
       Word R,S;
{
       Word T;
       /* hide T; */

Step1: /* Compute. */
       if (R == 0)
         T = 0;
       else
         T = RNPROD(R,RNINV(S));

Return: /* Prepare for return. */
       return(T);
}
