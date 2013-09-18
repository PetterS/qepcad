/*===========================================================================
			    C <- ILCOMB(A,B,u,v)

Integer linear combination.  

Inputs
  A, B : in Z.  A,B >= 0.
  u, v : BETA-integers such that A*u+B*v >= 0.

Outputs
  C    : in Z such that C=A*u+B*v.
===========================================================================*/
#include "saclib.h"

Word ILCOMB(A,B,u,v)
       Word A,B,u,v;
{
       Word Ab,Bb,C,a,a0,a1,b,b0,b1,c0,c1;

Step1: /* Convert to lists. */
       if (A > BETA)
	  Ab = A;
       else
	  Ab = LIST1(A);
       if (B > BETA)
	  Bb = B;
       else
	  Bb = LIST1(B);

Step2: /* Multiply and add. */
       C = NIL;
       c1 = 0;
       do {
	  AADV(Ab,&a,&Ab);
	  AADV(Bb,&b,&Bb);
	  DPR(a,u,&a1,&a0);
	  DPR(b,v,&b1,&b0);
	  c0 = a0 + b0;
	  c0 = c0 + c1;
	  c1 = a1 + b1;
	  while (c0 < 0) {
	     c0 = c0 + BETA;
	     c1 = c1 - 1; }
	  if (c0 >= BETA) {
	     c0 = c0 - BETA;
	     c1 = c1 + 1; }
	  C = COMP(c0,C); }
       while (Ab != NIL || Bb != NIL);
       if (c1 != 0)
	  C = COMP(c1,C);

Step3: /* Normalize. */
       while (C != NIL && FIRST(C) == 0)
	  C = RED(C);
       if (C == NIL)
	  C = 0;
       else if (RED(C) == NIL)
	  C = FIRST(C);
       else
	  C = INV(C);

Return: /* Prepare for return. */
       return(C);
}
