/*===========================================================================
			     C <- IPP2P(r,B,m)

Integral polynomial power of 2 product.  

Inputs
  r : a BETA-digit, r >= 0, the number of variables.
  m : a non-negative integer.
  B : an element of Z[x_1,...,x_r].  

Outputs
  C : an element of Z[x_1...,x_r].  C=(2^m)B.
===========================================================================*/
#include "saclib.h"

Word IPP2P(r,B,m)
       Word r,B,m;
{
       Word C;
       Word Bp,b,c,e,rp;

Step1: /* r = 0 or m = 0 or B = 0. */
       if (r == 0) {
	  C = ITRUNC(B,-m);
	  goto Return; }
       if (m == 0) {
	  C = B;
	  goto Return; }
       if (B == 0) {
	  C = 0;
	  goto Return; }

Step2: /* General case. */
       Bp = B;
       C = NIL;
       rp = r - 1;
       do {
	  ADV2(Bp,&e,&b,&Bp);
	  if (rp == 0)
	     c = ITRUNC(b,-m);
	  else
	     c = IPP2P(rp,m,b);
	  C = COMP2(c,e,C); }
       while (Bp != NIL);
       C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
