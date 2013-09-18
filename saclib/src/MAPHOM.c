/*===========================================================================
			 MAPHOM(m,A,B)

Modular array polynomial homomorphism.

Inputs
  m : a BETA-digit.
  A : in Z/(q)[x], where q is a BETA-digit.  A is in array representation.
  B : an array large enough to hold A.

Side effect
  H_m(A) is computed and put in B.
===========================================================================*/
#include "saclib.h"

void MAPHOM(m,A,B)
       Word m,*A,*B;
{
       Word b,n,i;

Step1: /* Initialize. */
       n = MAPDEG(A);

Step2: /* Compute. */
       for (i = 0; i <= n; i++) {
	  b = MAPCF(A,i) % m;
	  MAPCF(B,i) = b; }

Step3: /* Determine degree. */
       i = n;
       while (MAPCF(B,i) == 0 && i > 0)
	  i--;
       MAPDEG(B) = i;

Return: /* Prepare for return. */
       return;
}
