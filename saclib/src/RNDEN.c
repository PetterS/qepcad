/*======================================================================
                      b <- RNDEN(R)

Rational number denominator.  

Inputs
  R : a rational number.  

Outputs
  b : the denominator of R, a positive integer.
======================================================================*/
#include "saclib.h"

Word RNDEN(R)
       Word R;
{
       Word b;
       /* hide algorithm */

Step1: /* Compute. */
       if (R == 0)
         b = 1;
       else
         b = SECOND(R);

Return: /* Prepare for return. */
       return(b);
}
