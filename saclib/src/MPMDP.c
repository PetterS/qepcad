/*===========================================================================
			    C <- MPMDP(r,m,a,B)

Modular polynomial modular digit product.

Inputs
  r : a BETA-digit, r >= 1, the number of variables;
  m : a positive BETA-digit;
  a : in Z/(m);
  B : in Z/(m)[x_1,...,x_r].

Outputs
  C : in Z/(m)[x_1,...,x_r], C = a * B.
===========================================================================*/
#include "saclib.h"

Word MPMDP(r,m,a,B)
       Word r,m,a,B;
{
       Word Bp,C,b,c,e,rp;

Step1: /* C = 0. */
       if (a == 0 || B == 0) {
	  C = 0;
	  goto Return; }

Step2: /* General case. */
       Bp = B;
       C = NIL;
       rp = r - 1;
       do {
	  ADV2(Bp,&e,&b,&Bp);
	  if (rp == 0)
	     c = MDPROD(m,a,b);
	  else
	     c = MPMDP(rp,m,a,b);
	  C = COMP2(c,e,C); }
       while (Bp != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
