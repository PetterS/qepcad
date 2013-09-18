/*======================================================================
                      B <- MPEXP(r,m,A,n)

Modular polynomial exponentiation.

Inputs
  A : in Z/(m)[x_1,...,x_r].
  r : a BETA-digit, r >= 0, the number of variables.
  m : a BETA-digit, m > 1.
  n : a non-negative BETA-digit.

Outputs
  B : in Z/(m)[x_1,...,x_r], B = A^n.
======================================================================*/
#include "saclib.h"

Word MPEXP(r,m,A,n)
       Word r,m,A,n;
{
       Word B,i;

Step1: /* n = 0. */
       if (n == 0) {
	  B = PINV(0,1,r);
	  goto Return; }

Step2: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step3: /* General case. */
       B = A;
       for (i = 1; i <= n - 1; i++)
	  B = MPPROD(r,m,B,A);

Return: /* Prepare for return. */
       return(B);
}
