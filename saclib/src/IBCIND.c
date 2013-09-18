/*===========================================================================
			     B <- IBCIND(A,n,k)

Integer binomial coefficient induction.

Inputs
  n,k : BETA-digits with 0 <= k <= n.
  A : the binomial coefficient (n choose k).

Outputs
  B : the binomial coefficient (n choose (k+1)).
===========================================================================*/
#include "saclib.h"

Word IBCIND(A,n,k)
       Word A,n,k;
{
       Word B,kp,np;

Step1: /* Compute. */
       np = n - k;
       kp = k + 1;
       if ((A < BETA) && (np < (BETA / A)))
	  B = (A * np) / kp;
       else
	  B = IDEQ(IDPR(A,np),kp);

Return: /* Prepare for return. */
       return(B);
}
