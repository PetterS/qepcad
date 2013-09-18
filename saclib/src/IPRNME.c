/*===========================================================================
			    B <- IPRNME(r,A,b)

Integral polynomial, rational number multiple evaluation.

Inputs
  r : is a positive BETA-digit.
  A : is an element of Z[x_1,...,x_r].
  b : is a list (b_1,...,b_k) of elements of Q, 1 <= k <= r.
  
Output
  B : an element of Q[x_{k+1},...,x_r] such that 
      B(x_{k+1},...,x_r) = A(b_1,...,b_k,x_{k+1},...,x_r).
===========================================================================*/
#include "saclib.h"

Word IPRNME(r,A,b)
       Word r,A,b;
{
       Word Ap,B;

Step1: /* Convert A to a polynomial over Q. */
       Ap = RPFIP(r,A);

Step2: /* Evaluate at b. */
       B = RPME(r,Ap,b);

Return: /* Prepare for return. */
       return(B);
}
