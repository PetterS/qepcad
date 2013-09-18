/*===========================================================================
                         B <- IPABS(r,A)

Integral polynomial absolute value.

Inputs 
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[X1,...Xr].   

Outputs
  B : in Z[X1,...Xr], the absolute value of A.
===========================================================================*/
#include "saclib.h"

Word IPABS(r,A)
       Word r,A;
{
       Word B,s;

Step1: /* Compute. */
       s = IPSIGN(r,A);
       if (s >= 0)
	  B = A;
       else
	  B = IPNEG(r,A);

Return: /* Prepare for return. */
       return(B);
}
