/*===========================================================================
		  Ft <- NORMHLEFD(N,n,p,F,C,G)

Norm polynomial Hensel lifting with early factor detection.

Inputs
  N : in Z[x], the norm of a polynomial A[alpha,x] in Z[alpha][x],
      where alpha is an algebraic number.  N is squarefree.
  n : the degree of alpha.
  p : an odd medium prime.  p divides neither the leading
      coefficient nor the discriminant of N.
  F : a list of pairs ((d_1,F_1),...,,(d_s,F_s)).  Let M be the
      minimal polynomial of alpha, and let M_1 * ... * M_s be a
      complete factorization of M (mod p).  Then d_i = deg(M_i)
      and F_i is a list of the distinct monic irreducible factors
      of res_t(M_i(t),A(t,x)) (mod p).
  C : a characteristic set, a superset of the set of possible
      degrees of factors of A[alpha,x].
  G : a list of pairs (p_i,G_i), where p_i is an element of
      SPRIME and G_i is a list of pairs (e_i,H_i).
      Let Mb_1 * ... * Mb_r be a complete factorization of M
      (mod p_i).  Then e_i = deg(Mb_i) and H_i is the
      distinct-degree factorization of res_t(Mb_i(t),A(t,x)),
      that is, H_i is a list of pairs (f_j,Hb_j) where Hb_j is
      the product of all monic irreducible factors of H_i of
      degree f_j.

Outputs
  Ft : a list of elements of Z[x].  Ft is the list of distinct
       positive irreducible factors of N.
===========================================================================*/
#include "saclib.h"

#define TIME_RATIO 4

Word NORMHLEFD(N,n,p,F,C,G)
       Word N,n,p,F,C,G;
{
       Word A,Ab,Ap,As,B,Bb,Bp,Bs,Cb,D,Fb,Fs,Ft,Gb,Ib,Ib1,Ip,Ipp,Ip1,Ipp1,
            M,Nb,Ns,Nt,N1,Q,Qp,Qpp,Qs,Sb,Tb,Th,Tt,U,Us,Y,Yp,Z,Zp,
            b,c,cb,cq,d,e,ep,f,k,q,qp,t,th,tt;

Step0: /* Initialize the lifting and testing times,
          and evaluate N at 1. */
       Th = Tt = 0;
       N1 = IPEMV(1,N,1);

Step1: /* Compute the two-factor lifting bound and the highest
          single-precision power of p not exceeding the bound. */ 
       M = IUPLB(N,2);
       q = p;
       while (ICOMP(q,M) < 0 && q < BETA/q)
	  q = q * q;
       while (ICOMP(q,M) < 0 && q < BETA/p)
	  q = q * p;

Step2: /* Lift quadratically to single-precision. */
       NORMSQHL(N,p,q,F,&Ab,&Bb,&Sb,&Tb);

Step3: /* Compute the maximum degree d of trial factors. */
       c = ILOG2(IPSUMN(1,N));
       c = c + c;
       cq = ILOG2(q);
       k = RNCEIL(RNRED(c,cq));
       d = RNFLOR(RNRED(PDEG(N)/n,k));

Step4: /* Factor testing. */
       tt = ACLOCK();
       NORMEFD(N,n,p,q,M,Ab,G,C,d,N1,&Fs,&Nb,&Gb,&M,&Ib,&Cb,&N1);
       tt = ACLOCK()-tt;
       if (Ib == NIL)
	  goto Return;
       if (Fs == NIL)
	  Tt += tt;

Step5: /* Perform the initial linear lifting step. */
       th = ACLOCK();
       Q = IPROD(q,q);
       Nt = MIPHOM(1,Q,N);
       NORMILHS(Nt,q,Q,Ab,Bb,Sb,Tb,&Y,&Z,&Us,&As,&Bs); 
       th = ACLOCK()-th;
       Th += th;
       e = 2;

Step6: /* Recompute the maximum degree d of trial factors. */
       if (Fs != NIL) {
          c = ILOG2(IPSUMN(1,Nb));
          c = c + c;
          k = RNCEIL(RNRED(c,cq)); }
       d = RNFLOR(RNRED(2*(PDEG(Nb)/n),k));

Step7: /* Compute f, an estimate of the number of true factors and
                 ep, the level at which to test regardless of time. */
       f = IUPENF(Nb);
       cb = IPSUMN(1,Nb);
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
	  Ft = LLGIE(As,Ib);
	  Ip = Ib;
	  NORMEFD(Nb,n,p,Q,M,Ft,Gb,Cb,d,N1,&Fb,&Nb,&Gb,&M,&Ib,&Cb,&N1);
	  if (Fb != NIL) {
	     Fs = CONC(Fs,Fb);
	     if (Ib == NIL)
		goto Return;
	     Ipp = NIL;
	     while (Ip != NIL) {
		ADV(Ip,&Ip1,&Ip);
		ADV(Ib,&Ib1,&Ib);
		Ipp1 = LGIE(Ip1,Ib1);
		Ipp = COMP(Ipp1,Ipp); }
	     Ib = INV(Ipp); }
	  else {
	     tt = ACLOCK();
	     Tt += tt;
	     Ib = Ip; } }
  
Step9: /* Prepare for linear lifting. */
       Ns = N;
       IPDQNR(1,Ns,q,&Ns,&D);
       IPDQNR(1,Ns,q,&Ns,&D);
       IPDQNR(1,Ns,q,&Ns,&D);
       Qpp = 1;
       Qp = q;
       Ap = Ab;
       Ab = NORMFL(Ab);
       Bp = Bb;
       Yp = Y;
       Zp = Z;
       U = Us;
       A = As;
       B = Bs;

Step10: /* Do one linear Hensel step. */
       th = ACLOCK();
       NORMLHS(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B,
	       &Qs,&Y,&Z,&Us,&As,&Bs);
       th = ACLOCK()-th;
       Th += th;
       e++;

Step11: /* Compute the maximum degree d of trial factors. */
       b = ICOMP(Qs,M);
       if (b >= 0)
          d = PDEG(Nb)/n - 1;
       else {
          if (Fb != NIL) {
             c = ILOG2(IPSUMN(1,Nb));
             c = c + c;
             k = RNCEIL(RNRED(c,cq)); }
          d = RNFLOR(RNRED(e*(PDEG(Nb)/n),k)); }

Step12: /* Factor testing. */
       if (Tt == 0 || e == ep || (Th / Tt >= TIME_RATIO) || b >= 0) {
	  tt = ACLOCK();
	  Ft = LLGIE(As,Ib);
	  Ip = Ib;
	  NORMEFD(Nb,n,p,Qs,M,Ft,Gb,Cb,d,N1,&Fb,&Nb,&Gb,&M,&Ib,&Cb,&N1);
	  if (Fb != NIL) {
	     Fs = CONC(Fs,Fb);
	     if (Ib == NIL)
		goto Return;
	     Ipp = NIL;
	     while (Ip != NIL) {
		ADV(Ip,&Ip1,&Ip);
		ADV(Ib,&Ib1,&Ib);
		Ipp1 = LGIE(Ip1,Ib1);
		Ipp = COMP(Ipp1,Ipp); }
	     Ib = INV(Ipp); }
	  else {
	     tt = ACLOCK()-tt;
	     Tt += tt;
	     Ib = Ip; } }

Step13: /* Advance. */
       Qpp = Qp;
       Qp = Q;
       Q = Qs;
       Ap = A;
       Bp = B;
       Yp = Y;
       Zp = Z;
       U  = Us;
       IPDQNR(1,Ns,q,&Ns,&D);
       A  = As;
       B  = Bs;
       goto Step10;

Return: /* Prepare for return. */
       return(Fs);
}
