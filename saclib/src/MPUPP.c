/*======================================================================
                      Ab <- MPUPP(r,p,A)

Modular polynomial univariate primitive part.

Inputs
  r  : a BETA-digit, r >= 2.
  p  : a BETA-digit, prime.
  A  : in Z/(p)[X1,...,Xr].

Outputs
  Ab : in Z/(p)[X1,...,Xr]. If A non-zero then Ab = A/a where a is the
       univariate content of A. Otherwise, Ab = 0.
======================================================================*/
#include "saclib.h"

Word MPUPP(r,p,A)
       Word r,p,A;
{
       Word Ab,a;
       /* hide algorithm */

Step1: /* Compute. */
       MPUCPP(r,p,A,&a,&Ab);

Return: /* Prepare for return. */
       return(Ab);
}
