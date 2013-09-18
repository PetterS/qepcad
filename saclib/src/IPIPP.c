/*======================================================================
                      Ab <- IPIPP(r,A)

Integral polynomial integer primitive part.

Inputs
  r  : a BETA-digit, r > 0.
  A  : in Z[X1,...,Xr]

Outputs
  Ab : in Z[X1,...,Xr]. 
       If A non-zero then 
         Ab = A/a where a is the integer content of A. 
       Otherwise 
         Ab = 0.
======================================================================*/
#include "saclib.h"

Word IPIPP(r,A)
       Word r,A;
{
       Word Ab,a;
       /* hide algorithm */

Step1: /* Compute. */
       IPICPP(r,A,&a,&Ab);

Return: /* Prepare for return. */
       return(Ab);
}
