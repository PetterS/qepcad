/*==========================================================================
                      C <- IREM(A,B)

Integer remainder.  

Inputs
  A, B : in Z. B non-zero.

Outputs
  C    : in Z.  Z = A - B * Q, where Q is the integral part of A / B.
==========================================================================*/
#include "saclib.h"

Word IREM(A,B)
       Word A,B;
{
       Word C,Q;
       /* hide algorithm */

Step1: /* Compute. */
       IQR(A,B,&Q,&C);

Return: /* Prepare for return. */
       return(C);
}
