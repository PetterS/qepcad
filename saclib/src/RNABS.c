/*======================================================================
                      S <- RNABS(R)

Rational number absolute value.  

Inputs
  R : a rational number.  

Outputs
  S : the absolute value of R.
======================================================================*/
#include "saclib.h"

Word RNABS(R)
       Word R;
{
       Word S;
       /* hide algorithm */

Step1: /* Compute. */
       if (RNSIGN(R) >= 0)
         S = R;
       else
         S = RNNEG(R);

Return: /* Prepare for return. */
       return(S);
}
