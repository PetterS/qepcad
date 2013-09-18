/*===========================================================================
			      IPSRP(r,A; a,Ab)

Integral polynomial similar to rational polynomial.

Inputs
  r : a BETA-digit, r >= 0.
  A : in Q[x_1,...,x_r].

Outputs
  a : in Q, a = 0 if A = 0.
 Ab : in Z[x_1,...,x_r], Ab primitive and positive such that Ab = a * A.
      Ab = 0 if A = 0.
===========================================================================*/
#include "saclib.h"

void IPSRP(r,A, a_,Ab_)
       Word r,A, *a_,*Ab_;
{
       Word Ab,As,a,s,u,up,v;

Step1: /* A = 0. */
       if (A == 0) {
	  a = 0;
	  Ab = 0;
	  goto Return; }

Step2: /* A /= 0. */
       RPBLGS(r,A,&u,&v,&s);
       up = IDPR(u,s);
       a = LIST2(up,v);
       As = RPRNP(r,a,A);
       Ab = IPFRP(r,As);

Return: /* Prepare for return. */
       *a_ = a;
       *Ab_ = Ab;
       return;
}
