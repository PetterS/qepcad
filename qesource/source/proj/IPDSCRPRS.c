/*===========================================================================
                      B <- IPDSCRPRS(r,A)

Integral polynomial discriminant, subresultant prs algorithm.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr], of degree greater than or equal to two in its
      main variable.

Outputs
  B : in Z[X1,...,X_{r-1}], the discriminant of A, computed using the
      subresultant prs algorithm.
===========================================================================*/
#include "qepcad.h"

Word IPDSCRPRS(Word r, Word A)
{
       Word Ap,B,B1,B2,a,b,c,n,rp;

Step1: /* deg(A) = 2. */
       if (PDEG(A) == 2) {
	 a = PCOEFF(A,2);
	 b = PCOEFF(A,1);
	 c = PCOEFF(A,0);
	 rp = r-1;
	 B1 = IPPROD(rp,b,b);
	 B2 = IPPROD(rp,IPIP(rp,-4,a),c);
	 B = IPSUM(rp,B1,B2);
	 goto Return; }

Step2: /* General case. */
       Ap = IPDMV(r,A);
       B = IPRESPRS(r,A,Ap);
       a = PLDCF(A);
       rp = r - 1;
       B = IPQ(rp,B,a);
       n = PDEG(A);
       if (REM(n,4) >= 2)
         B = IPNEG(rp,B);

Return: /* Prepare for return. */
       return(B);
}
