/*======================================================================
                      B <- AMUPTR1(A)

Algebraic module univariate polynomial translation by 1. 

Inputs
  A : in Z[alpha,X].

Outputs
  B : in Z[alpha,X], B(X) = A(X+1).
======================================================================*/
#include "saclib.h"

Word AMUPTR1(A)
       Word A;
{
       Word B;

Step1: /* Translate by one. */
       B = IPTR1(2,A,2);

Return: /* Prepare for return. */
       return(B);
}
