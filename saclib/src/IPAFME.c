/*===========================================================================
			    B <- IPAFME(r,M,A,b)

Integral polynomial, algebraic number field multiple evaluation.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  r : a BETA-digit, r >= 1.
  A : in Z[x_1,...,x_r].
  b : a list (b_1,...,b_k) of elements of Q(alpha), 1 <= k <= r.

Outputs
  B : in Q(alpha)[x_{k+1},...,x_r], B = A(b_1,...,b_k,x_{k+1},...,x_r).
===========================================================================*/
#include "saclib.h"

Word IPAFME(r,M,A,b)
       Word r,M,A,b;
{
       Word Ap,B;

Step1: /* Convert A to a polynomial over Q(alpha). */
       Ap = AFPFIP(r,A);

Step2: /* Evaluate at b. */
       B = AFPME(r,M,Ap,b);

Return: /* Prepare for return. */
       return(B);
}
