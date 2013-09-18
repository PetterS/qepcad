/*======================================================================
                      n <- DIPDEG(r,A)

Distributive polynomial degree.

Inputs 
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[X1,...,Xr], distributive representation.

Outputs
  n : the degree of A in its main variable.
======================================================================*/
#include "saclib.h"

Word DIPDEG(r,A)
       Word r,A;
{
       Word n;
       /* hide algorithm */

Step1:
       if (r == 0 || A == 0)
         n = 0;
       else
         n = FIRST(SECOND(A));

Return: /* Prepare for return. */
       return(n);
}
