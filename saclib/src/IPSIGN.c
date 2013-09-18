/*======================================================================
                      s <- IPSIGN(r,A)

Integral polynomial sign.

Inputs
  A  : in Z[X1,...,Xr].
  r  : a BETA-digit, r >= 0, the number of variables.

Outputs
  s  : the sign of A.
======================================================================*/
#include "saclib.h"

Word IPSIGN(r,A)
       Word r,A;
{
       Word s;
       /* hide algorithm */

Step1: /* Compute. */
       s = ISIGNF(PLBCF(r,A));

Return: /* Prepare for return. */
       return(s);
}
