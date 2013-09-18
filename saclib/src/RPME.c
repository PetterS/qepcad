/*===========================================================================
			     B <- RPME(r,A,b)

Rational polynomial multiple evaluation.

Inputs
  r : a positive BETA-digit.
  A : in Q[x_1,...,x_r].  
  b : a list (b_1...,b_k) of elements of Q, with 1 <= k <= r.  
           
Output
  B : in Q[x_{k+1},...,x_r] such that B = A(b_1,...,b_k,x_{k+1},...,x_r).
===========================================================================*/
#include "saclib.h"

Word RPME(r,A,b)
       Word r,A,b;
{
       Word B,b1,bp,i;

Step1: /* Evaluate. */
       i = r;
       bp = b;
       B = A;
       do {
          ADV(bp,&b1,&bp);
          B = RPEV(i,B,1,b1);
          i--; }
       while (bp != NIL);

Return: /* Prepare for return. */
       return(B);
}
