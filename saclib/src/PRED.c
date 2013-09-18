/*======================================================================
                      B <- PRED(A)

Polynomial reductum.

Inputs
  A : a polynomial.

Outputs
  B : the reductum of A.
======================================================================*/
#include "saclib.h"

Word PRED(A)
       Word A;
{
       Word B;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         B = 0;
       else
         {
         B = RED2(A);
         if (B == NIL)
           B = 0;
         }

Return: /* Prepare for return. */
       return(B);
}
