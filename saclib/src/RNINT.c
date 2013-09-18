/*======================================================================
                      R <- RNINT(A)

Rational number from integer.  

Inputs
  A : an integer.  

Outputs
  R : the rational number A/1.
======================================================================*/
#include "saclib.h"

Word RNINT(A)
       Word A;
{
       Word R;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         R = 0;
       else
         R = LIST2(A,1);

Return: /* Prepare for return. */
       return(R);
}
