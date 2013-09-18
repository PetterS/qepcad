/*======================================================================
                      R <- RNRAND(n)

Rational number, random.  

Inputs
  n : a positive BETA-integer.  

Outputs
  R : Random integers a and b are generated using IRAND(n).  
      Then R=a/(abs(b)+1), reduced to lowest terms.
======================================================================*/
#include "saclib.h"

Word RNRAND(n)
       Word n;
{
       Word A,B,R;

Step1: /* Compute. */
       A = IRAND(n);
       B = IRAND(n);
       B = IABSF(B);
       B = ISUM(B,1);
       R = RNRED(A,B);

Return: /* Prepare for return. */
       return(R);
}
