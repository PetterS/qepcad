/*===========================================================================
		     IPIQH(r,p,D,Ab,Bb,Sb,Tb,M,C; A,B)

Integral polynomial mod ideal quadratic hensel lemma.

Inputs
 r        : a BETA-digit, r >= 1.
 p        : a BETA-digit, p prime.
 D        : a list (d1,...,d_{r-1}), with di BETA-digits, di >= 0.
 Ab       : in Z/(p)[x_1,...,x_{r-1},y]/(x_1^d1,...,x_{r-1}^d_{r-1}), 
            Ab monic, deg_y(Ab) > 0.
 Bb,Sb,Tb : in Z/(p)[x_1,...,x_{r-1},y]/(x_1^d1,...,x_{r-1}^d_{r-1}),
            such that Ab*Sb + Bb*Tb = 1.
 M        : in Z, M = p^j for some j in Z, j > 0.
 C        : in Z[x_1,...,x_{r-1}], C congruent to Ab*Bb.

Outputs
 A,B : Z/(M)[x_1,...,x_{r-1},y]/(x_1^d1,...,x_{r-1}^d_{r-1}), with
       A monic, 
       deg_y(A) = deg_y(Ab), 
       A congruent to Ab, 
       B congruent to Bb, and 
       A*B congruent to C.
===========================================================================*/
#include "saclib.h"

void IPIQH(r,p,D,Ab,Bb,Sb,Tb,M,C, A_,B_)
       Word r,p,D,Ab,Bb,Sb,Tb,M,C, *A_,*B_;
{
       Word A,As,At,B,Bs,Bt,I,R,Rp,S,Ss,St,T,Ts,Tt,U,U1,Ut,Y,Y1,Z,Z1,
            c,q,qs,qt;

Step1: /* Initialize. */
       q = p;
       A = Ab;
       B = Bb;
       S = Sb;
       T = Tb;
       I = PINV(0,1,r);
       if (q == M)
	  goto Return;

Step2: /* Compute Y,Z. */
       R = MIPIPR(r,M,D,A,B);
       R = IPDIF(r,C,R);
       U = IPIQ(r,R,q);
       qs = IPROD(q,q);
       c = ICOMP(qs,M);
       if (c > 0) {
	  qt = IEQ(M,q);
	  At = MIPHOM(r,qt,A);
	  Bt = MIPHOM(r,qt,B);
	  St = MIPHOM(r,qt,S);
	  Tt = MIPHOM(r,qt,T); }
       else {
	  qt = q;
	  At = A;
	  Bt = B;
	  St = S;
	  Tt = T; }
       Ut = MIPHOM(r,qt,U);
       MIPISE(r,qt,D,At,Bt,St,Tt,Ut,&Y,&Z);

Step3: /* Compute As,Bs and check for end. */
       R = IPIP(r,q,Z);
       As = IPSUM(r,A,R);
       R = IPIP(r,q,Y);
       Bs = IPSUM(r,B,R);
       if (c >= 0) {
	  A = As;
	  B = Bs;
	  goto Return; }

Step4: /* Compute Y1,Z1. */
       R = MIPIPR(r,qs,D,As,S);
       Rp = MIPIPR(r,qs,D,Bs,T);
       R = MIPSUM(r,qs,R,Rp);
       R = MIPDIF(r,qs,R,I);
       U1 = IPIQ(r,R,q);
       MIPISE(r,q,D,A,B,S,T,U1,&Y1,&Z1);

Step5: /* Compute Ss,Ts. */
       R = IPIP(r,q,Y1);
       Ss = MIPDIF(r,qs,S,R);
       R = IPIP(r,q,Z1);
       Ts = MIPDIF(r,qs,T,R);

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
