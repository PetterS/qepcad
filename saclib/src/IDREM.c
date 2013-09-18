/*==========================================================================
                      r <- IDREM(A,b)

Integer-digit remainder.

Inputs
  A  : in Z.
  b  : non-zero BETA-digit.

Outputs
  r  : in Z.  r = A - b * Q, where Q is the integral part of A / b.
==========================================================================*/
#include "saclib.h"

Word IDREM(A,b)
       Word A,b;
{
       Word Q,r;
       /* hide algorithm */

Step1: /* Compute. */
       IDQR(A,b,&Q,&r);

Return: /* Prepare for return. */
       return(r);
}
