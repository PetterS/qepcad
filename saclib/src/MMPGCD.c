/*===========================================================================
			    C <- MMPGCD(p,A,B)

Medium modulus polynomial greatest common divisor.

Inputs
  p : a medium prime.
  A,B : in Z/(p)[x] in list representation.

Output
  C : in Z/(p)[x] in list representation.  C = gcd(A,B).
===========================================================================*/
#include "saclib.h"

Word MMPGCD(p,A,B)
       Word p,A,B;
{
       Word *Ap,*Bp,*Cp,C;

Step1: /* A  = 0 or B = 0. */
       if (A == 0) {
	  C = MPMON(1,p,B);
	  goto Return; }
       if (B == 0) {
	  C = MPMON(1,p,A);
	  goto Return; }

Step2: /* Convert to arrays. */
       Ap = MAPFMUP(A);
       Bp = MAPFMUP(B);

Step3: /* Compute gcd. */
       Cp = MMAPGCD(p,Ap,Bp);

Step4: /* Convert to list and free arrays. */
       C = MUPFMAP(Cp);
       MAPFREE(Ap);
       MAPFREE(Bp);
       MAPFREE(Cp);

Return: /* Prepare for return. */
       return(C);
}
