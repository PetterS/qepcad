/*===========================================================================
			     B <- MIPHOM(r,M,A)

Modular integral polynomial homomorphism.

Inputs
  A : in Z[X1,...,Xr].
  M : in Z, M > 0.
  r : a BETA-digit, r >= 0, the number of variables.

Outputs
  B : in Z/(M)[X1,...,Xr], B = A (mod M).
===========================================================================*/
#include "saclib.h"

Word MIPHOM(r,M,A)
       Word r,M,A;
{
       Word Ap,B,a,b,e,rp;

Step1: /* A=0. */
       if (A == 0) {
	  B = 0;
	  goto Return; }

Step2: /* r=0. */
       if (r == 0) {
	  B = MIHOM(M,A);
	  goto Return; }

Step3: /* General case. */
       Ap = A;
       B = NIL;
       rp = r - 1;
       do {
	  ADV2(Ap,&e,&a,&Ap);
	  if (rp == 0)
	     b = MIHOM(M,a);
	  else
	     b = MIPHOM(rp,M,a);
	  if (b != 0)
	     B = COMP2(b,e,B); }
       while (Ap != NIL);
       if (B == NIL)
	  B = 0;
       else
	  B = INV(B);

Return: /* Prepare for return. */
       return(B);
}
