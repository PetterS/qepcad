/*======================================================================
                      c <- MPUC(r,p,A)

Modular polynomial univariate content.

Inputs
  r : a BETA-digit, r >= 2.
  p : a BETA-digit, prime.
  A : in Z/(p)[X1,...,Xr].

Outputs
  c : in Z/(p)[X], the univariate content of A.
======================================================================*/
#include "saclib.h"

Word MPUC(r,p,A)
       Word r,p,A;
{
       Word c;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         c = 0;
       else
         c = MPUCS(r,p,A,0);

Return: /* Prepare for return. */
       return(c);
}
