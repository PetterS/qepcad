/*===========================================================================
			    B <- IPBHT(r,A,i,k)

Integral polynomial binary homothetic transformation.

Inputs
  r : A BETA-digit.  r >= 0.
  A : an element of Z[x_1,...,x_r].
  i : 1 <= i <= r.
  k : a BETA-digit.

Outputs
  B : an element of Z[x_1,...,x_r].  
      B(x_1,...,x_i,...,x_r) = 
      2^{-h}A(x_1,...,x_{i-1},2^kx_i,x_{i+1},...,x_r), where h is
      uniquely determined so that B is an integral polynomial not
      divisible by 2.
===========================================================================*/
#include "saclib.h"

Word IPBHT(r,A,i,k)

       Word r,A,i,k;
{
       Word B;
       Word At,Bt;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* i = 1. */
       if (i == 1) {
	  B = IPBHTLV(r,A,k);
	  goto Return; }

Step3: /* i > 1. */
       At = PCPV(r,A,1,i);
       Bt = IPBHTLV(r,At,k);
       B = PICPV(r,Bt,1,i);
       
Return: /* Prepare for return. */
       return(B);
}
