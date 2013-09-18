/*======================================================================
                      t <- IEVEN(A)

Integer even.

Inputs
  A  : in Z.

Outputs
  t  : a BETA-digit, t = 1 if A is even, t = 0 otherwise.
======================================================================*/
#include "saclib.h"

Word IEVEN(A)
       Word A;
{
       Word t;
       /* hide algorithm */

Step1: /* Determine. */
       if (A < BETA)
         t = EVEN(A);
       else
         t = EVEN(FIRST(A));

Return: /* Prepare for return. */
       return(t);
}
