/*======================================================================
                      B <- PRT(A)

Polynomial reciprocal transformation.

Inputs
  A : a non-zero polynomial.  

Outputs
  B : polynomial in the same ring as A, B(X) = X^n A(1/X),
      where X is the main variable of A and n = deg(A).
======================================================================*/
#include "saclib.h"

Word PRT(A)
       Word A;
{
       Word Ap,B,a,e,n;
       /* hide Ap,a,e,n; */

Step1: /* Compute. */
       n = FIRST(A);
       Ap = A;
       B = NIL;
       do
         {
         ADV2(Ap,&e,&a,&Ap);
         e = n - e;
         B = COMP2(e,a,B);
         }
       while (!(Ap == NIL));

Return: /* Prepare for return. */
       return(B);
}
