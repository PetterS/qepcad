/*======================================================================
                      n <- PDEG(A)

Polynomial degree.

Inputs
  A : a polynomial.

Outputs
  n : the degree of A.
======================================================================*/
#include "saclib.h"

Word PDEG(A)
       Word A;
{
       Word n;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         n = 0;
       else
         n = FIRST(A);

Return: /* Prepare for return. */
       return(n);
}
