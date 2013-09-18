/*======================================================================
                      a <- PLDCF(A)

Polynomial leading coefficient.

Inputs
  A : a polynomial.

Outputs
  a : the leading coefficient of A.
======================================================================*/
#include "saclib.h"

Word PLDCF(A)
       Word A;
{
       Word a;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         a = 0;
       else
         a = SECOND(A);

Return: /* Prepare for return. */
       return(a);
}
