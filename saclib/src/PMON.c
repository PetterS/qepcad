/*======================================================================
                      A <- PMON(a,e)

Polynomial monomial.

Inputs
  a : in R, R ring.  
  e : a BETA-integer, e >=0.

Outputs
  A : in R[X], A(X) = a X^e.
======================================================================*/
#include "saclib.h"

Word PMON(a,e)
       Word a,e;
{
       Word A;
       /* hide algorithm */

Step1: /* Compute. */
       if (a == 0)
         A = 0;
       else
         A = LIST2(e,a);

Return: /* Prepare for return. */
       return(A);
}
