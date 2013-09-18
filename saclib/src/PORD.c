/*======================================================================
                      k <- PORD(A)

Polynomial order.

Inputs
  A : a non-zero polynomial.

Outputs
  k : integer, the order of A.  
      That is, if A(x)=an x^n +...+ a0, then k is the smallest integer
      such that ak /= 0.
======================================================================*/
#include "saclib.h"

Word PORD(A)
       Word A;
{
       Word Ap,k;
       /* hide algorithm */

Step1: /* Compute. */
       Ap = A;
       do
         {
         ADV(Ap,&k,&Ap);
         Ap = RED(Ap);
         }
       while (Ap != NIL);

Return: /* Prepare for return. */
       return(k);
}
