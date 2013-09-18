/*======================================================================
                      a <- PTBCF(r,A)

Polynomial trailing base coefficient.

Inputs
  A : in R[X1,...,Xr], R ring.
  r : a BETA-digit, r >= 0.

Outputs
  a : in R, the trailing base coefficient of A.
======================================================================*/
#include "saclib.h"

Word PTBCF(r,A)
       Word r,A;
{
       Word As,a,b,e,rp;
       /* hide b,e,rp; */

Step1: /* r=0 or A=0. */
       if (r == 0 || A == 0)
         {
         a = A;
         goto Return;
         }

Step2: /* General case. */
       rp = r - 1;
       As = CINV(A);
       ADV2(As,&b,&e,&As);
       if (e == 0)
         a = PTBCF(rp,b);
       else
         a = 0;

Return: /* Prepare for return. */
       return(a);
}
