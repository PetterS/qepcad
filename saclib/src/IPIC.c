/*======================================================================
                      c <- IPIC(r,A)

Integral polynomial integer content.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr]

Outputs
  c : in Z, the content of A.
======================================================================*/
#include "saclib.h"

Word IPIC(r,A)
       Word r,A;
{
       Word c;
       /* hide algorithm */

Step1: /* Compute. */
       if (A == 0)
         c = 0;
       else
         c = IPICS(r,A,0);

Return: /* Prepare for return. */
       return(c);
}
