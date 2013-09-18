/*===========================================================================
			      C <- IPQ(r,A,B)

Integral polynomial quotient.

Inputs  
  r   : a BETA-digit, r >= 0, the number of variables.
  A,B : in Z[x_1,...,x_r].
        B is a non-zero divisor of A.

Outputs
  C   : in Z[x_1,...,x_r], C = A / B.
===========================================================================*/
#include "saclib.h"

Word IPQ(r,A,B)
       Word r,A,B;
{
       Word C,R;

Step1: /* Compute. */
       if (r == 0)
	  C = IEQ(A,B);
       else
	  C = IPEQ(r,A,B);

Return: /* Prepare for return. */
       return(C);
}
