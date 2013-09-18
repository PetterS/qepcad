/*===========================================================================
		       B <- MMAPMON(m,A)

Medium modulus array polynomial monic.

Input
  m : a medium BETA-digit.
  A : in Z/(m), in array representation, and ldcf(A) is a unit.

Output
  B : in Z/(p) in array representation.
      If A = 0 then B = 0.  Otherwise, B is the monic associate of A.
===========================================================================*/
#include "saclib.h"

Word *MMAPMON(m,A)
       Word m,*A;
{
       Word n,*B,a,b,i;

Step1: /* Get array for B. */
       n = MAPDEG(A);
       B = MAPGET(n);

Step2: /* A = 0. */
       if (MAPZERO(A)) {
	  MAPDEG(B) = 0;
	  MAPCF(B,0) = 0;
	  goto Return; }

Step3: /* A != 0. */
       MAPDEG(B) = n;
       a = MDINV(m,MAPLDCF(A));
       for (i = 0; i < n; i++) {
	  b = (a * MAPCF(A,i)) % m;
	  MAPCF(B,i) = b; }
       MAPCF(B,n) = 1;

Return: /* Prepare for return. */
       return(B);
}
