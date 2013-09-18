/*======================================================================
                      C <- MPQ(r,p,A,B)

Modular polynomial quotient.

Inputs
  A,B : in Z/(p)[X1,...,Xr], B a non-zero divisor of A.
  r : a BETA-digit, r >= 0, the number of variables.
  p : a prime BETA-digit.

Outputs
  C : in Z/(p)[X1,...,Xr], C = A / B.
======================================================================*/
#include "saclib.h"

Word MPQ(r,p,A,B)
       Word r,p,A,B;
{
       Word C,R;
       /* hide algorithm */

Step1: /* Compute. */
       if (r == 0)
         C = MDQ(p,A,B);
       else
         MPQR(r,p,A,B,&C,&R);

Return: /* Prepare for return. */
       return(C);
}
