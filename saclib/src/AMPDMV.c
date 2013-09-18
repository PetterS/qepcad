/*======================================================================
                      B <- AMPDMV(r,A)

Algebraic module polynomial derivative, main variable.

Inputs
  r : a BETA-digit, r >= 1.
  A : in Z[alpha,X1,...,Xr].

Outputs
  B : in Z[alpha,X1,...,Xr]. B is the derivative of A with respect
      to its main variable.
======================================================================*/
#include "saclib.h"

Word AMPDMV(r,A)
       Word r,A;
{
       Word B;

Step1: /* Compute derivative. */
       B = IPDMV(r+1,A);

Return: /* Prepare for return. */
       return(B);
}
