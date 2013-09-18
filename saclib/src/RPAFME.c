/*===========================================================================
			    B <- RPAFME(r,M,A,b)

Rational polynomial, algebraic number field multiple evaluation.

Input:      
  r : a BETA-digit, r >= 1.
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A : in Q[x_1,...,x_r].
  b : a list (b_1,...,b_k) of elements of Q(alpha), 1 <= k <= r.

Output: 
  B : in Q(alpha)[x_{k+1},...,x_r], B = A(b_1,...,b_k,x_{k+1},...,x_r).
===========================================================================*/
#include "saclib.h"

Word RPAFME(r,M,A,b)
       Word r,M,A,b;
{
       Word Ap,B;

Step1: /* Convert A to a polynomial over Q(alpha). */
       Ap = AFPFRP(r,A);

Step2: /* Evaluate at b. */
       B = AFPME(r,M,Ap,b);

Return: /* Prepare for return. */
       return(B);
}
