/*===========================================================================
			    B <- IPBHTMV(r,A,k)

Integral polynomial binary homothetic transformation, main variable.

Inputs
  r : a BETA-digit.  r >= 0.
  A : an element of Z[x_1,...,x_r].
  k : a Beta-digit.

Outputs
  B : an element of Z[x_1,...,x_r].  
      If k >= 0 then B(x_1,...,x_r) = A(x_1,...,2^k x_r).
      If k < 0 then B(x_1,...,x_r) = 2^{-km}A(x_1,...,2^k x_r), 
      where m = deg(A).
===========================================================================*/
#include "saclib.h"

Word IPBHTMV(r,A,k)

       Word r,A,k;
{
       Word B;
       Word Ap,a,b,e,h,m,rp;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* r = 1. */
       if (r == 1) {
	  B = IUPBHT(A,k);
	  goto Return; }

Step3: /* r > 1. */
       Ap = A;
       rp = r - 1;
       m = PDEG(A);
       B = NIL;
       if (k >= 0)
	  h = 0;
       else
	  h = m * k;
       while (Ap != NIL) {
	  ADV2(Ap,&e,&a,&Ap);
	  b = IPP2P(rp,a,k * e - h);
	  B = COMP2(b,e,B); }
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
