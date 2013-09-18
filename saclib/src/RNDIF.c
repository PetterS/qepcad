/*======================================================================
                      T <- RNDIF(R,S)

Rational number difference.  

Inputs
  R,S : rational numbers.  

Outpus
  T   : R-S.
======================================================================*/
#include "saclib.h"

Word RNDIF(R,S)
       Word R,S;
{
       Word T;
       /* hide T; */

Step1: /* Compute. */
       T = RNSUM(R,RNNEG(S));

Return: /* Prepare for return. */
       return(T);
}
