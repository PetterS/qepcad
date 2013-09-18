/*======================================================================
                      B <- IABSF(A)

Integer absolute value function.

Inputs
  A  : integer.

Outputs
  B  : the absolute value of A.
======================================================================*/
#include "saclib.h"

Word IABSF(A)
       Word A;
{
       Word B,s;
       /* hide algorithm */

Step1: /* Compute. */
       s = ISIGNF(A);
       if (s >= 0)
         B = A;
       else
         B = INEG(A);

Return: /* Prepare for return. */
       return(B);
}
