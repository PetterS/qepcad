/*===========================================================================
		 IUPFT2(p,Q,Qp,q,A,B; Ab,B1,B2)

Integral univariate polynomial factor test, degree at most 2.

Inputs
  p : a single-precision prime.
  Q : a positive power of p.
  Qp: the floor of the square root of Q/2.
  q : a BETA-digit, q = ILOG2(Qp).
  A : in Z[x], primitive, squarefree and of degree at least 2.
  B : in Z/(Q)[x], monic, PDEG(B) <= 2.

Outputs  
  Ab : in Z[x].
  B1,B2 : in Z[x]. If there is a monic factor F of A in Q[x] which is 
          congruent to B modulo Q then let Bb be the positive, primitive
	  integral polynomial similar to F.  If Bb is irreducible then
          B1 = Bb and B2 = 0.  If Bb splits into two factors then B1, B2
          are these two factors.  In either case, Ab = A / Bb.  If no
          such Bb exists then Ab = A and B1 = B2 = 0.
===========================================================================*/
#include "saclib.h"

void IUPFT2(p,Q,Qp,q,A,B,Ab_,B1_,B2_)
       Word p,Q,Qp,q,A,B,*Ab_,*B1_,*B2_;
{
       Word Ab,At,B1,B2,Bb,Bp,Bs,L,R,a,b,c,n,r,u;

Step1: /* Convert B to a rational polynomial Bs if possible. */
       B1 = 0;
       B2 = 0;
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
	  Bs = COMP2(r,n,Bs); }
       while (Bp != 0);
       Bs = INV(Bs);

Step2: /* Convert Bs to a primitive integral polynomial Bb. */
       IPSRP(1,Bs,&c,&Bb);

Step3: /* Is Bb a factor? */
       IPQR(1,A,Bb,&At,&R); 
       if (R != 0) { 
	  Bb = 0; 
	  goto Return; }; 
       Ab = At;

Step4: /* Check if Bb factors. */
       if (PDEG(Bb) == 1) {
	  B1 = Bb;
	  B2 = 0; }
       else {
	  L = IUSFPF2(Bb);
	  ADV(L,&B1,&L);
	  if (L == NIL)
	     B2 = 0;
	  else
	     B2 = FIRST(L); }

Return: /* Prepare for return. */
       *Ab_ = Ab;
       *B1_ = B1;
       *B2_ = B2;
       return;
}
