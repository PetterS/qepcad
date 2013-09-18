/*======================================================================
                      Ab <- IPPP(r,A)

Integral polynomial primitive part.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr].

Outputs
 Ab : in Z[X1,...,Xr], the primitive part of A.
======================================================================*/
#include "saclib.h"

Word IPPP(r,A)
       Word r,A;
{
       Word Ab,C,s;
       /* hide algorithm */

Step1: /* Compute. */
       IPSCPP(r,A,&s,&C,&Ab);

Return: /* Prepare for return. */
       return(Ab);
}
