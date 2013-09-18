/*===========================================================================
			     B <- IPIHOM(r,D,A)

Integral polynomial mod ideal homomorphism.

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  D : a list (d_1,...,d_{r-1}) of non-negative BETA-digits.
  A : in Z[x_1,...,x_r].

Outputs
  B : in Z[x_1,...,x_r]/(x_1^d_1,...,x_{r-1}^d_{r-1}),
      B = A mod (x_1^d_1,...,x_{r-1}^d_{r-1}).
======================================================================*/
#include "saclib.h"

Word IPIHOM(r,D,A)
       Word r,D,A;
{
       Word As,B,a,b,e,rp;

Step1: /* r=0 or A=0. */
       if (r == 0 || A == 0) {
         B = A;
         goto Return; }

Step2: /* General case. */
       rp = r - 1;
       B = NIL;
       As = CINV(A);
       while (As != NIL) {
	  ADV2(As,&a,&e,&As);
	  b = IPTRUN(rp,D,a);
	  if (b != 0)
	     B = COMP2(e,b,B); }
       if (B == NIL)
	  B = 0;

Return: /* Prepare for return. */
       return(B);
}
