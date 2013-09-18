/*======================================================================
                      B <- AMUPTR(A,h)

Algebraic module univariate polynomial translation.

Inputs
  A : in Z[alpha,X].
  h : in Z.

Outputs
  B : in Z[alpha,X], B(X) = A(X+h).
======================================================================*/
#include "saclib.h"

Word AMUPTR(A,h)
       Word A,h;
{
       Word B;

Step1: /* Translate. */
       B = IPTR(2,A,2,h);

Return: /* Prepare for return. */
       return(B);
}
