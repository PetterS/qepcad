/*===========================================================================
		  Ft <- IUPHLEFD(p,F,C,E,G)

Integral univariate polynomial Hensel lifting with
early factor detection.

Inputs
  p : an odd medium prime.
  F : a list (A_1,...,A_r), of monic, irreducible elements of
      Z_p[x], r >= 2.  gcd(Ai,Aj) = 1 for 1 <= i < j <= r.
  C : in Z[x], with C congruent to c * A_1 * ... * A_r, where p
      does not divide ldcf(C) and c = H_p(ldcf(C)).
  E : a characteristic set, a set of possible degrees of
      factors of C.
  G : a list ((p_1,G_1),...,(p_t,G_t)) such that p_i is an
      element of SPRIME, and G_i is the distinct-degree
      factorization of C, i.e., G_i is a list
      ((n_1,H_1),...,(n_k,H_k)) of pairs, where H_i is the
      product of all monic irreducible factors of C (mod p_i) of
      degree n_i.

Outputs
  Ft : a list of elements of Z[x].  Ft is the list of distinct
       positive irreducible factors of C.

Notes
  Quadratic lifting is used to lift the mod p factorization of C
  to a mod q factorization, where q is the full single-precision
  power of p.  Linear lifting is used to lift from mod q^j to
  mod q^{j+1}, for j >= 1.  Early factor detection on the lifted
  modular factors is performed.  See Collins & Encarnacion,
  "Improved Techniques for Factoring Univariate Polynomials",
  JSC Vol. 21, No. 3 (March 1996) for algorithm details.
===========================================================================*/
#include "saclib.h"
#define TIME_RATIO 4

Word IUPHLEFD(p,F,C,E,G)
       Word p,F,C,E,G;
{
       Word A,Ab,Ap,As,B,Bb,Bp,Bs,Cb,Cs,Ct,D,Eb,Fb,Fs,Ft,Gb,
            Ib,Ip,M,Q,Qp,Qpp,Qs,Sb,Tb,Th,Tt,U,Us,Y,Yp,Z,Zp,
            b,c,cb,cq,d,e,ep,f,k,n,q,qp,t,th,tt;

Step0: /* Initialize the lifting and testing times. */
       Th = Tt = 0;

Step1: /* Compute the two-factor lifting bound and the highest
          single-precision power of p not exceeding the bound. */ 
       M = IUPLB(C,2);
       q = p;
       while (ICOMP(q,M) < 0 && q < BETA/q)
	  q = q * q;
       while (ICOMP(q,M) < 0 && q < BETA/p)
	  q = q * p;

Step2: /* Lift quadratically to single-precision. */
       IUPSQHLL(p,q,F,C,&Ab,&Bb,&Sb,&Tb);
       e = 1;

Step3: /* Compute the maximum degree d of trial factors. */
       c = ILOG2(IPMAXN(1,C));
       c = c + c;
       cq = ILOG2(q);
       k = RNCEIL(RNRED(c,cq));
       n = PDEG(C);
       d = RNFLOR(RNRED(n,k));

Step4: /* Factor testing. */
       tt = ACLOCK();
       IUPEFD(p,q,C,M,Ab,G,E,d,&Fs,&Cb,&Gb,&M,&Ib,&Eb);
       tt = ACLOCK()-tt;
       if (Fs == NIL)
	  Tt += tt;
       if (Ib == NIL)
	  goto Return; /* All factors have been found. */

Step5: /* Perform the initial linear lifting step. */
       th = ACLOCK();
       Q = IPROD(q,q);
       Ct = MIPHOM(1,Q,C);
       IUPILHS(q,Q,Ab,Bb,Sb,Tb,Ct,&Y,&Z,&Us,&As,&Bs); 
       th = ACLOCK()-th;
       Th += th;
       e = 2;

Step6: /* Recompute the maximum degree d of trial factors. */
       if (Fs != NIL) {
	  c = ILOG2(IPMAXN(1,Cb));
	  c = c + c;
	  k = RNCEIL(RNRED(c,cq));
	  n = PDEG(Cb); }
       d = RNFLOR(RNRED(2*n,k));

Step7: /* Compute f, an estimate of the number of true factors and
                 ep, the level at which to test regardless of time. */
       f = IUPENF(Cb);
       cb = IPMAXN(1,Cb);
       IROOT(cb,f,&cb,&t);
       cb = ISUM(cb,t);
       cb = IPROD(cb,cb);
       cb = IPROD(2,cb);
       ep = 1;
       qp = q;
       while (ICOMP(qp,cb) < 0) {
	  qp = IPROD(qp,q);
	  ep++; }

Step8: /* Factor testing. */
       if (Tt == 0 || e == ep || (Th / Tt >= TIME_RATIO) || ICOMP(Q,M) >= 0) {
	  tt = ACLOCK();
	  Ft = LGIE(As,Ib);
	  Ip = Ib;
	  IUPEFD(p,Q,Cb,M,Ft,Gb,Eb,d,&Fb,&Cb,&Gb,&M,&Ib,&Eb);
	  Fs = CONC(Fs,Fb);
	  Ib = LGIE(Ip,Ib);
	  tt = ACLOCK()-tt;
	  if (Fb == NIL)
	     Tt += tt;
	  if (Ib == NIL)
	     goto Return; /* All factors have been found. */ }
       
Step9: /* Prepare for linear lifting. */
       Cs = C;
       IPDQNR(1,Cs,q,&Cs,&D);
       IPDQNR(1,Cs,q,&Cs,&D);
       IPDQNR(1,Cs,q,&Cs,&D);
       Qpp = 1;
       Qp = q;
       Ap = Ab;
       Bp = Bb;
       Yp = Y;
       Zp = Z;
       U = Us;
       A = As;
       B = Bs;

Step10: /* Do one linear Hensel step. */
       th = ACLOCK();
       IUPLHSL(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B,
	       &Qs,&Y,&Z,&Us,&As,&Bs);
       th = ACLOCK()-th;
       Th += th;
       e++;

Step11: /* Compute the maximum degree d of trial factors. */
       b = ICOMP(Qs,M);
       if (b >= 0)
	  d = PDEG(Cb)-1;
       else {
	  if (Fb != NIL) {
	     c = ILOG2(IPMAXN(1,Cb));
	     c = c + c;
	     k = RNCEIL(RNRED(c,cq));
	     n = PDEG(Cb); }
	  d = RNFLOR(RNRED(e*n,k)); }

Step12: /* Factor testing. */
       if (Tt == 0 || ep == e || (Th / Tt >= TIME_RATIO) || b >= 0) {
	  tt = ACLOCK();
	  Ft = LGIE(As,Ib);
	  Ip = Ib;
	  IUPEFD(p,Qs,Cb,M,Ft,Gb,Eb,d,&Fb,&Cb,&Gb,&M,&Ib,&Eb);
	  Fs = CONC(Fs,Fb);
	  Ib = LGIE(Ip,Ib);
	  tt = ACLOCK()-tt;
	  if (Fb == NIL)
	     Tt += tt;
	  if (Ib == NIL)
	     goto Return; /* All factors have been found. */ }

Step13: /* Advance. */
       Qpp = Qp;
       Qp = Q;
       Q = Qs;
       Ap = A;
       Bp = B;
       Yp = Y;
       Zp = Z;
       U  = Us;
       IPDQNR(1,Cs,q,&Cs,&D);
       A  = As;
       B  = Bs;
       goto Step10;

Return: /* Prepare for return. */
       return(Fs);
}
