/*===========================================================================
			    IPSCPP(r,A; s,C,Ab)

Integral polynomial sign, content, and primitive part.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[x_1,...,x_r].

Outputs
  s : a BETA-digit, the sign of A.
  C : in Z[x_1,...,x_{r-1}], the content of A.
 Ab : in Z[x_1,...,x_r], the primitive part of A.
===========================================================================*/
#include "saclib.h"

void IPSCPP(r,A, s_,C_,Ab_)
       Word r,A, *s_,*C_,*Ab_;
{
       Word A1,Ab,Ap,C,C1,e,rp,s;

Step1: /* A = 0. */
       if (A == 0) {
	  s = 0;
	  C = 0;
	  Ab = 0;
	  goto Return; }

Step2: /* A /= 0. */
       s = IPSIGN(r,A);
       Ap = IPABS(r,A);
       rp = r - 1;
       C = IPC(r,Ap);
       if (IPONE(rp,C) == 1)
	  Ab = Ap;
       else {
	  Ab = NIL;
	  do {
	     ADV2(Ap,&e,&A1,&Ap);
	     C1 = IPEQ(rp,A1,C);
	     Ab = COMP2(C1,e,Ab); }
	  while (Ap != NIL);
	  Ab = INV(Ab); }

Return: /* Prepare for return. */
       *s_ = s;
       *C_ = C;
       *Ab_ = Ab;
       return;
}
