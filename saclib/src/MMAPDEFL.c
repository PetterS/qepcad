/*===========================================================================
			MMAPDEFL(m,A,c)

Medium modulus array polynomial deflation.

Inputs
  m : a medium BETA-digit.
  A : in Z/(m)[x] in array representation.
  c : in Z/(m) such that A(c) = 0.

Side effects
  A / (x - c) is computed and put in A.
===========================================================================*/
#include "saclib.h"

void MMAPDEFL(m,A,c)
       Word m,*A,c;
{
       Word a,b,i,n;

Step1: /* Initialize. */
       n = MAPDEG(A) - 1;
       a = MAPCF(A,n);
       MAPCF(A,n) = MAPLDCF(A);
       MAPDEG(A) = n;

Step2: /* Loop. */
       for (i = n-1; i >= 0; i--) {
	  b = a + c * MAPCF(A,i+1);
	  a = MAPCF(A,i);
	  MAPCF(A,i) = b % m; }

Return: /* Prepare for return. */
       return;
}
