/*======================================================================
                      B <- AMPSAFP(r,A)

Algebraic module polynomial similar to algebraic field polynomial.

Inputs
  r : in Z.  r > 0.
  A : in Q(alpha)[X1,...,Xr].

Outputs
  B : in Z[alpha,X1,...,Xr].
======================================================================*/
#include "saclib.h"

Word AMPSAFP(r,A)
       Word r,A;
{
       Word B,b;

Step1: /* Convert to Q[alpha,X1,...,Xr]. */
       B = AFPICR(r,A);
       IPSRP(r+1,B,&b,&B);

Return: /* Prepare for return. */
       return(B);
}
