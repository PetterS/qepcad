/*===========================================================================
			     B <- IPTRUN(r,D,A)

Integral polynomial truncation.

Inputs
  D : a list (d_1,...,d_r) of non-negative BETA-digits.
  r : a BETA-digit, r >= 0, the number of variables.
  A : in Z[x_1,...,x_r].

Outputs
  B : in Z[x_1,...,x_r]/(x_1^d_1,...,x_r^d_r),
      B = A mod (x_1^d_1,...,x_r^d_r).
===========================================================================*/
#include "saclib.h"

Word IPTRUN(r,D,A)
       Word r,D,A;
{
       Word As,B,Dp,a,b,d,e,rp;

Step1: /* r=0 or A=0. */
       if (r == 0 || A == 0) {
	  B = A;
	  goto Return; }

Step2: /* Initialize. */
       rp = r - 1;
       As = CINV(A);
       B = NIL;
       Dp = CINV(D);
       ADV(Dp,&d,&Dp);
       Dp = INV(Dp);

Step3: /* Generate terms. */
       while (As != NIL && SECOND(As) < d) {
	  ADV2(As,&a,&e,&As);
	  if (rp == 0)
	     b = a;
	  else
	     b = IPTRUN(rp,Dp,a);
	  if (b != 0)
	     B = COMP2(e,b,B); }
       if (B == NIL)
	  B = 0;

Return: /* Prepare for return. */
       return(B);
}
