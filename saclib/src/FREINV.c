/*==========================================================================
		       B <- FREINV(p,M,A)

Finite ring element inverse.

Input
  p : a medium prime.
  M : in Z/(p)[x], deg(M) > 0.  M is in array representation.
  A : in Z/(p)[x]/(M).  A is in array representation.

Output
  B : in Z/(p)[x].  If A is invertible in Z/(p)[x]/(M), then B = A^(-1).
      Otherwise, deg(B) = -1.
==========================================================================*/
#include "saclib.h"

Word *FREINV(p,M,A)
       Word p,*M,*A;
{
       Word *B,r,rp;

Step1: /* Get array for B. */
       B = MAPGET(MAPDEG(M)-1);

Step2: /* deg(A) == 0. */
       if (MAPDEG(A) == 0) {
	  if (MAPZERO(A))
	     MAPDEG(B) = -1;
	  else {
	     MAPDEG(B) = 0;
	     MAPLDCF(B) = MDINV(p,MAPLDCF(A)); }
	  goto Return; }

Step3: /* Compute resultant and cofactor. */
       MMAPRC(p,M,A,B,&r);

Step4: /* r = 0 ? */
       if (r == 0) {
	  MAPDEG(B) = -1;
	  goto Return; }

Step5: /* Divide cofactor by resultant. */
       rp = MDINV(p,r);
       MMAPMDP(p,rp,B,B);

Return: /* Prepare for return. */
       return(B);
}
