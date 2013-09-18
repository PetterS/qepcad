/*===========================================================================
			      B <- IPDSCRBEZ(r,A)

Integral polynomial discriminant, Bezout method.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[x_1,...,x_r], of degree greater than or equal to two in its
      main variable.

Outputs
  B : in Z[x_1,...,x_{r-1}], the discriminant of A.
===========================================================================*/
#include "saclib.h"

Word IPDSCRBEZ(r,A)
       Word r,A;
{
       Word Ap,B,a,n,rp;

Step1: /* Compute. */
       Ap = IPDMV(r,A);
       B = IPRESBEZ(r,A,Ap);
       a = PLDCF(A);
       rp = r - 1;
       B = IPEQ(rp,B,a);
       n = PDEG(A);
       if (REM(n,4) >= 2)
	  B = IPNEG(rp,B);

Return: /* Prepare for return. */
       return(B);
}
