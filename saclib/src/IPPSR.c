/*===========================================================================
			     C <- IPPSR(r,A,B)

Integral polynomial pseudo-remainder.

Inputs 
  r   : a BETA-digit, r >= 0, the number of variables.
  A,B : in Z[x_1,...,x_r], B non-zero.

Outputs
  C   : in Z[x_1,...,x_r], the pseudo-remainder of A and B.
===========================================================================*/
#include "saclib.h"

Word IPPSR(r,A,B)
       Word r,A,B;
{
       Word B1,Bb,Bs,C,C1,c,i,l,m,n;

Step1: /* deg(B) = 0. */
       n = PDEG(B);
       if (n == 0) {
	  C = 0;
	  goto Return; }

Step2: /* deg(B) > 0. */
       m = PDEG(A);
       C = A;
       Bb = PRED(B);
       B1 = PMON(PLDCF(B),0);
       for (i = m; i >= n; i--) {
	  if (C == 0)
	     goto Return;
	  l = PDEG(C);
	  if (l == i) {
	     c = PLDCF(C);
	     C = PRED(C);
	     C = IPPROD(r,C,B1);
	     C1 = PMON(c,l - n);
	     Bs = IPPROD(r,Bb,C1);
	     C = IPDIF(r,C,Bs); }
	  else
	     C = IPPROD(r,C,B1); }

Return: /* Prepare for return. */
       return(C);
}
