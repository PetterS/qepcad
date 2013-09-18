/*======================================================================
                      B <- IUPCHT(A)

Integral univariate polynomial circle to half-plane transformation.

Inputs
  A : in Z[X], non-zero.

Outputs
  B : in Z[X], B(x) = (x+1)^n * A(1/(x+1)),
      where n = deg(A).
======================================================================*/
#include "saclib.h"

Word IUPCHT(A)
       Word A;
{
       Word Ap,B;
       /* hide B; */

Step1: /* Compute. */
       Ap = PRT(A);
       B = IUPTR1(Ap);

Return: /* Prepare for return. */
       return(B);
}
