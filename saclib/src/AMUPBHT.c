/*===========================================================================
			     B <- AMUPBHT(A,k)

Algebraic module univariate polynomial binary homothetic transformation.

Inputs
  A : in Z[alpha,X], A non-zero.
  k : a BETA-digit.

Outputs
  B : in Z[X], B(X) = 2^(-h) * A(2^k*X),
      where h is uniquely determined so that B is an
      integral polynomial not divisible by 2.
===========================================================================*/
#include "saclib.h"

Word AMUPBHT(A,k)
       Word A,k;
{
       Word B;

Step1: /* Compute. */
       B = IPBHTMV(2,A,k);

Return: /* Prepare for return. */
       return(B);
}
