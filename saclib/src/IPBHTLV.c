/*===========================================================================
			    B <- IPBHTLV(r,A,k)

Integral polynomial binary homothetic transformation, leading variable.

Inputs
  r : A BETA-digit.  r >= 0.
  A : an element of Z[x_1,...,x_r].
  k : a BETA-digit.

Outputs
  B : an element of Z[x_1,...,x_r].  
      B(x_1,...,x_r) = 2^{-h} A(2^kx_1,x_2,...,x_r), where h is uniquely 
      determined so that B is an integral polynomial not divisible by 2.
===========================================================================*/
#include "saclib.h"

Word IPBHTLV(r,A,k)
       Word r,A,k;
{
       Word B;
       Word Ap,a,b,e;

Step1: /* A = 0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* r = 1. */
       if (r == 1) {
	  B = IUPBHT(A,k);
	  goto Return; }

Step3: /* r > 1. */
       B = NIL;
       Ap = A;
       while (Ap != NIL) {
	  ADV2(Ap,&e,&a,&Ap);
	  b = IPBHTLV(r - 1,a,k);
	  B = COMP2(b,e,B); }
       B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
