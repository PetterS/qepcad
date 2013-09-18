/*===========================================================================
	      IUPSQHL(p,Ab,Bb,Sb,Tb,Q,C; A,B,S,T)

Integral univariate polynomial single-precion quadratic Hensel lifting.

Inputs
  p : a BETA-digit, p prime.
  Ab,Bb,Sb,Tb : in Z/(p)[X], with Ab*Sb + Bb*Tb = 1, and deg(Tb) < deg(Ab).
  Q : a single-precision power of p.
  C : in Z/(Q)[X], C = Ab*Bb (mod p).

Outputs
  A,B : in Z/(Q)[X], with ldcf(A) = ldcf(Ab), deg(A) = deg(Ab),
        A congruent to Ab, B congruent to Bb, and C congruent to A*B.
  S,T : in Z/(Q)[X], with A*S + B*T = 1 and deg(T) < deg(A).
===========================================================================*/
#include "saclib.h"

void IUPSQHL(p,Ab,Bb,Sb,Tb,Q,C, A_,B_,S_,T_)
       Word p,Ab,Bb,Sb,Tb,Q,C, *A_,*B_,*S_,*T_;
{
       Word A,B,S,T,Qp,c,n,i,u,q,qp,qs,qt;
       Word *Ah,*As,*At,*Bh,*Bs,*Bt,*Sh,*Ss,*St,*Th,*Ts,*Tt;
       Word *R,*Rp,*Ch,*Cs,*U,*Y,*Z;
       Word d_a,d_b,qss,cs;

Step1: /* Nothing to do. */
       if (p == Q) {
	  A = Ab;
	  B = Bb;
	  S = Sb;
	  T = Tb;
	  goto Return; }

Step2: /* Initialize. */
       q = p;
       d_a = PDEG(Ab);
       d_b = PDEG(Bb);
       As = MAPFMUP(Ab);
       Bs = MAPFMUP(Bb);
       Ss = MAPFMUPS(Sb,d_b - 1);
       Ts = MAPFMUPS(Tb,d_a - 1);
       Cs = MAPFMUP(C);
       Ah = MAPCOPY(As);
       Bh = MAPCOPY(Bs);
       Sh = MAPGET(d_b - 1);
       MAPASSIGN(Ss,Sh);
       Th = MAPGET(d_a - 1);
       MAPASSIGN(Ts,Th);
       At = MAPGET(d_a);
       Bt = MAPGET(d_b);
       St = MAPGET(d_b - 1);
       Tt = MAPGET(d_a - 1);
       R = MAPGET(d_a + d_b);
       Rp = MAPGET(d_b + d_a - 1);
       Ch = MAPGET(PDEG(C));
       U = MAPGET(d_a + d_b);
       Y = MAPGET(d_b);
       Z = MAPGET(d_a - 1);
       qs = IPROD(q,q);
       c = ICOMP(qs,Q);

Step3: /* Prepare for the next lifting step. */
       if (c > 0) {
	  qp = 1;
	  qt = q;
	  Qp = Q/p;
	  do {
	     qp *= p;
	     qt *= p; }
	  while (qt <= Qp);
	  qt = qp;
	  qs = q * qp;
	  MAPHOM(qt,Ah,At);
	  MAPHOM(qt,Bh,Bt);
	  MAPHOM(qt,Sh,St);
	  MAPHOM(qt,Th,Tt); }
       else {
	  qt = q;
	  MAPASSIGN(Ah,At);
	  MAPASSIGN(Bh,Bt);
	  MAPASSIGN(Sh,St);
	  MAPASSIGN(Th,Tt); }
       MAPHOM(qs,Cs,Ch);
       qss = IPROD(qs,qs);
       cs = ICOMP(qss,Q);

Step4: /* Compute the residue for lifting the factors. */
       if (cs > 0)
	  MAPPROD(qs,Ah,Bh,R);
       else
	  MMAPPROD(qs,Ah,Bh,R);
       MAPDIF(qs,Ch,R,U);
       n = MAPDEG(U);
       for (i = 0; i <= n; i++)
	  MAPCF(U,i) /= q;  /* exact division. */

Step5: /* Lift the factors. */
       MMAPSE(qt,At,Bt,St,Tt,U, Y,Z);
       n = MAPDEG(Z);
       for (i = 0; i <= n; i++)
	  MAPCF(As,i) += q * MAPCF(Z,i);
       n = MAPDEG(Y);
       for (i = 0; i <= n; i++)
	  MAPCF(Bs,i) += q * MAPCF(Y,i);

Step6: /* Compute the residue for lifting the lift basis. */
       if (cs > 0) {
	  MAPPROD(qs,As,Sh,R);
	  MAPPROD(qs,Bs,Th,Rp); }
       else {
	  MMAPPROD(qs,As,Sh,R);
	  MMAPPROD(qs,Bs,Th,Rp); }
       MAPSUM(qs,R,Rp,U);
       u = MDDIF(qs,MAPCF(U,0),1);
       MAPCF(U,0) = u;
       n = MAPDEG(U);
       for (i = 0; i <= n; i++)
	  MAPCF(U,i) = MDNEG(qs,MAPCF(U,i)) / q;  /* exact division. */

Step7: /* Lift the lift basis. */
       MMAPSE(qt,At,Bt,St,Tt,U, Y,Z);
       n = minm(MAPDEG(Y),MAPDEG(Ss));
       for (i = 0; i <= n; i++)
	  MAPCF(Ss,i) += q * MAPCF(Y,i);
       while (i <= MAPDEG(Y)) {
	  MAPCF(Ss,i) = q * MAPCF(Y,i);
	  i++; }
       MAPDEG(Ss) = maxm(MAPDEG(Ss),i-1);

       n = minm(MAPDEG(Z),MAPDEG(Ts));
       for (i = 0; i <= n; i++)
	  MAPCF(Ts,i) += q * MAPCF(Z,i);
       while (i <= MAPDEG(Z)) {
	  MAPCF(Ts,i) = q * MAPCF(Z,i);
	  i++; }
       MAPDEG(Ts) = maxm(MAPDEG(Ts),i-1);
       
Step8: /* Advance and check for end. */
       q = qs;
       qs = qss;
       MAPASSIGN(As,Ah);
       MAPASSIGN(Bs,Bh);
       MAPASSIGN(Ss,Sh);
       MAPASSIGN(Ts,Th);
       if (c < 0) {
	  c = cs;
	  goto Step3; }

Step9: /* Convert to lists and free arrays. */
       A = MUPFMAP(Ah);
       B = MUPFMAP(Bh);
       S = MUPFMAP(Sh);
       T = MUPFMAP(Th);
       MAPFREE(Ah);
       MAPFREE(Bh);
       MAPFREE(Sh);
       MAPFREE(Th);
       MAPFREE(As);
       MAPFREE(Bs);
       MAPFREE(Ss);
       MAPFREE(Ts);
       MAPFREE(At);
       MAPFREE(Bt);
       MAPFREE(St);
       MAPFREE(Tt);
       MAPFREE(R);
       MAPFREE(Rp);
       MAPFREE(Ch);
       MAPFREE(Cs);
       MAPFREE(U);
       MAPFREE(Y);
       MAPFREE(Z);

Return: /* Prepare for return. */
       *A_ = A;
       *B_ = B;
       *S_ = S;
       *T_ = T;
       return;
}
