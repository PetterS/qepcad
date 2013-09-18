/*======================================================================
                      a <- RNNUM(R)

Rational number numerator.  

Inputs
  R : a rational number.  

Outputs
  a : the numerator of R, an integer.
======================================================================*/
#include "saclib.h"

Word RNNUM(R)
       Word R;
{
       Word a;
       /* hide algorithm */

Step1: /* Compute. */
       if (R == 0)
         a = 0;
       else
         a = FIRST(R);

Return: /* Prepare for return. */
       return(a);
}
