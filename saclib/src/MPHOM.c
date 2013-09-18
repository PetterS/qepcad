/*===========================================================================
			     B <- MPHOM(r,m,A)

Modular polynomial homomorphism.

Inputs
  A : in Z[X1,...,Xr].
  r : a BETA-digit, r >= 0, the number of variables.
  m : a BETA-digit.

Outputs
  B : in Z/(m)[X1,...,Xr],the image of A under the   
      homomorphism H_m .
===========================================================================*/
#include "saclib.h"

Word MPHOM(r,m,A)
       Word r,m,A;
{
       Word Ap,B,a,b,e,rp;

Step1: /* A=0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* r=0. */
       if (r == 0) {
	  B = MDHOM(m,A);
	  goto Return; }

Step3: /* General case. */
       rp = r - 1;
       Ap = A;
       B = NIL;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  if (rp == 0)
	     b = MDHOM(m,a);
	  else
	     b = MPHOM(rp,m,a);
	  if (b != 0)
	     B = COMP2(b,e,B); }
       while (Ap != NIL);
       B = INV(B);
       if (B == NIL)
	  B = 0;

Return: /* Prepare for return. */
       return(B);
}
