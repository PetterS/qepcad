/*======================================================================
                      B <- AMUPNT(A)

Algebraic module univariate polynomial negative transformation.

Inputs
  A : in Z[alpha,X].

Outputs
  B : in Z[alpha,X], B(X)=A(-X).
======================================================================*/
#include "saclib.h"

Word AMUPNT(A)
       Word A;
{
       Word B;

Step1: /* Compute. */
       B = IPNT(2,A,2);

Return: /* Prepare for return. */
       return(B);
}
