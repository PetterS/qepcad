/*===========================================================================
			    r <- IHDREM(A,n,b)

Integer half-digit remainder.

Inputs
  A : in Z, positive, and in array representation.
  n : a BETA-digit, the length of A.
  b : a BETA-digit, 0 < b < 2^15.

Output
  r : a BETA-digit, the remainder of A modulo b, 0 <= r < b.
===========================================================================*/
#include "saclib.h"

Word IHDREM(A,n,b)
       Word *A,n,b;
{
       Word a0,a1,np,r;

Step1: /* Initialize. */
       if (n <= 1) {
	  r = A[0] % b;
          goto Return; }
             
Step2: /* Divide. */
       np = n - 1;
       a1 = A[np];
       r = a1 = a1 % b;
       while (np >= 1) {
          np--;
          a0 = A[np];
          r = PHDREM(a1,a0,b);
          a1 = r; }

Return: /* Prepare for return. */
      return(r);
}
