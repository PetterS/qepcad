/*===========================================================================
		   IUPFT(p,Q,Qp,q,A,B; Ab,Bb)

Integral univariate polynomial factor test.

Inputs
  p : an odd medium prime.
  Q : a positive power of p.
  Qp: the floor of the square root of Q/2.
  q : a BETA-digit, q = ILOG2(Qp).
  A : in Z[x], primitive, squarefree and PDEG(A) > 2.
  B : in Z/(Q)[x], monic and PDEG(B) > 2.

Outputs  
  Ab,Bb : in Z[x].  If there is a monic factor F of A in Q[x] which is
          congruent to B modulo Q then Bb is the positive, primitive
	  integral polynomial similar to F and Ab = A / Bb;
	  otherwise Ab = A and Bb = 0.
===========================================================================*/
#include "saclib.h"

void IUPFT(p,Q,Qp,q,A,B,Ab_,Bb_)
       Word p,Q,Qp,q,A,B,*Ab_,*Bb_;
{
       Word Ab,At,Bb,Bp,Bs,Mb,R,a,b,c,n,r,u;

Step1: /* Convert B to a rational polynomial Bs if possible. */
       Bb = 0;
       Ab = A; 
       Bp = B; 
       Bs = NIL; 
       a = PLDCF(A);
       do {
	  PADV(Bp,&n,&u,&Bp); 
	  r = RNFMRPP(Q,Qp,q,p,u);
	  if (r == NIL)
	     goto Return;
	  b = RNDEN(r); 
	  if (IREM(a,b) != 0)
	     goto Return;
	  if (r != 0)
	     Bs = COMP2(r,n,Bs); }
       while (Bp != 0);
       Bs = INV(Bs);

Step2: /* Convert Bs to a primitive integral polynomial Bb. */
       IPSRP(1,Bs,&c,&Bb);

Step3: /* Check if Bb is guaranteed to be irreducible. */
       Mb = IUPLB(Bb,2);
       if (ICOMP(Q,Mb) < 0) {
	  Bb = 0;
	  goto Return; }

Step4: /* Is Bb a factor? */
       IPQR(1,A,Bb,&At,&R);
       if (R != 0) { 
	  Bb = 0; 
	  goto Return; }; 
       Ab = At;

Return: /* Prepare for return. */
       *Ab_ = Ab;
       *Bb_ = Bb;
       return;
}
