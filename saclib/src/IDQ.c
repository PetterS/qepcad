/*==========================================================================
                      C <- IDQ(A,b)

Integer-digit quotient.

Inputs
  A  : in Z.
  b  : non-zero BETA-digit.

Outputs
  C :  in Z, the integral part of A / b.
==========================================================================*/
#include "saclib.h"

Word IDQ(A,b)
       Word A,b;
{
       Word C,r;
       /* hide algorithm */

Step1: /* Compute. */
       IDQR(A,b,&C,&r);

Return: /* Prepare for return. */
       return(C);
}
