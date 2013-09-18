/*===========================================================================
                         IUPQH(p,Ab,Bb,Sb,Tb,M,C; A,B)

Integral univariate polynomial quadratic hensel lemma.

Inputs
  p : a BETA-digit, p prime.
  Ab,Bb,Sb,Tb : in Z/(p)[X], with Ab*Sb + Bb*Tb = 1, deg(Tb) < deg(Ab).
  M : in Z, M = p^j for some j in Z, j > 0.
  C : in Z[x], C congruent to Ab*Bb.

Outputs
  A,B : in Z/(M)[x], with ldcf(A) = ldcf(Ab), deg(A) = deg(Ab),
        A congruent to Ab, B congruent to Bb, and C congruent to A*B.
===========================================================================*/
#include "saclib.h"

void IUPQH(p,Ab,Bb,Sb,Tb,M,C, A_,B_)
       Word p,Ab,Bb,Sb,Tb,M,C, *A_,*B_;
{
       Word A,As,At,B,Bs,Bt,I,R,Rp,S,Ss,St,T,Ts,Tt,U,U1,Y,Y1,Z,Z1,c,q,qs,qt;

Step1: /* Initialize. */
       q = p;
       A = Ab;
       B = Bb;
       S = Sb;
       T = Tb;
       I = PMON(1,0);
       if (q == M)
	  goto Return;

Step2: /* Compute Y,Z. */
       R = IPPROD(1,A,B);
       R = IPDIF(1,C,R);
       U = IPIQ(1,R,q);
       qs = IPROD(q,q);
       c = ICOMP(qs,M);
       if (c > 0) {
	  qt = IEQ(M,q);
	  At = MIPHOM(1,qt,A);
	  Bt = MIPHOM(1,qt,B);
	  St = MIPHOM(1,qt,S);
	  Tt = MIPHOM(1,qt,T); }
       else {
	  qt = q;
	  At = A;
	  Bt = B;
	  St = S;
	  Tt = T; }
       MIUPSE(qt,At,Bt,St,Tt,U,&Y,&Z);

Step3: /* Compute As,Bs and check for end. */
       R = IPIP(1,q,Z);
       As = IPSUM(1,A,R);
       R = IPIP(1,q,Y);
       Bs = IPSUM(1,B,R);
       if (c >= 0) {
	  A = As;
	  B = Bs;
	  goto Return; }

Step4: /* Compute Y1,Z1. */
       R = IPPROD(1,As,S);
       Rp = IPPROD(1,Bs,T);
       R = IPSUM(1,R,Rp);
       R = IPDIF(1,R,I);
       U1 = IPIQ(1,R,q);
       MIUPSE(q,A,B,S,T,U1,&Y1,&Z1);

Step5: /* Compute Ss,Ts. */
       R = IPIP(1,q,Y1);
       Ss = MIPDIF(1,qs,S,R);
       R = IPIP(1,q,Z1);
       Ts = MIPDIF(1,qs,T,R);

Step6: /* Advance. */
       q = qs;
       A = As;
       B = Bs;
       S = Ss;
       T = Ts;
       goto Step2;

Return: /* Prepare for return. */
       *A_ = A;
       *B_ = B;
       return;
}
