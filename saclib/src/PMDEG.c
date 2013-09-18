/*======================================================================
                      n <- PMDEG(A)

Polynomial modified degree.

Inputs
  A : a polynomial.

Outputs
  n : in Z. If A = 0 then n = -1, otherwise n = deg(A).
======================================================================*/
#include "saclib.h"

Word PMDEG(A)
       Word A;
{
       Word n;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         n = -1;
       else
         n = FIRST(A);

Return: /* Prepare for return. */
       return(n);
}
