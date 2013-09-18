/*===========================================================================
      NORMEFD(N,n,p,Q,B,L,G,C,d,N1; F,Nb,Bb,Lb,Gb,Cb,Nb1)

Norm polynomial early factor detection.

Inputs
  N : in Z[x], the norm of some A[alpha,x] in Z[alpha][x], where
      alpha is an algebraic number.  N is squarefree.
  n : the degree of alpha.
  p : an odd medium prime.
  Q : a positive power of p.
  B : in Z, the two-factor lifting bound for N.
  L : a list of pairs ((d_1,L_1),...,,(d_s,L_s)).  Let M be the
      minimal polynomial of alpha, and let M_1 * ... * M_s be a
      complete factorization of M (mod p).  Then d_i = deg(M_i)
      and L_i is a list of distinct monic factors of
      N_i = res_t(M_i(t),A(t,x)) (mod Q).
  G : a list of lists (p_i,(e_1,G_1),(e_2,G_2),...,(e_t,G_t)).
      Let M = C_1 * ... * C_s (mod p_i) be a complete
      factorization of M (mod p_i).  Then e_i = deg(C_i) and G_i
      is the distinct-degree factorization of K_i(x) =
      res_t(C_i(t),A(t,x)) (mod p_i).  That is, G_i is a list
      ((n_1,H_1),...,(n_r,H_r)), where H_j is the product of all
      the monic ireducible factors of K_i of degree n_j.
  C : a characteristic set, a superset of the possible degrees
      of factors of A(alpha,x).
  d : the maximum degree of trial factors of A[alpha,x].
  N1: in Z.  N1 = N(1).

Outputs
  F  : a (possibly empty) list of all the irreducible factors of
       N that are obtained by performing early factor detection
       on combinations of modular factors whose product has
       degree at most d.
  Nb : N divided by the product of the elements of F.
  Bb : in Z, the two-factor lifting bound for Nb.  If Nb = 1,
       then Bb = 0. 
  Ib : a (possible empty) list of lists I_i of indices j_i such
       that if f_{j_i} is the j_ith element of L_i, then f_{j_i}
       could not be combined to produce a true factor of N.
  Gb : a list obtained from G, having a structure similar to G,
       but with the modular factors that were combined to
       produce a true factor removed.
  Cb : a characteristic set, a superset of the possible degrees of
       integral factors of Ab, where Ab is the polynomial
       corresponding to the norm Nb.  If Nb = 1, then Cb = 0.
  Nb1: in Z.  Nb1 = Nb(1).
===========================================================================*/
#include "saclib.h"

void NORMEFD(N,n,p,Q,B,L,G,C,d,N1, F_,Nb_,Gb_,Bb_,Ib_,Cb_,Nb1_)
       Word N,n,p,Q,B,L,G,C,d,N1, *F_,*Nb_,*Gb_,*Bb_,*Ib_,*Cb_,*Nb1_;
{
       Word A,A1,Bb,Cb,F,Fb,Fp,F1,Gb,Ib,Ib1,Lb,Lp,Lb1,Lp1,L1,Nb,Nb1,
            Qp,Tb,T1,c,dp,d1,e,i,k,n1,q,s;

Step1: /* Initialize. */
       Qp = IQ(Q,2);
       ISQRT(Qp,&Qp,&s);
       q = ILOG2(Qp);
       Nb = N;
       Bb = B;
       Lb = L;
       Gb = G;
       Cb = C;
       Ib = NIL;
       F = NIL;
       k = LENGTH(SECOND(FIRST(L)))-1;
       Fp = NIL;
       e = 1;
       dp = d;
       c = 1;

Step2: /* Convert list of factors to an arrays with tags,
	  and evaluate the factors at 1. */
       Lp = L;
       Lb = NIL;
       Tb = NIL;
       while (Lp != NIL) {
	  ADV(Lp,&L1,&Lp);
	  FIRST2(L1,&d1,&F1);
	  LLTGCA(F1,&Lp1,&n1);
	  T1 = GCAMALLOC(n1,GC_CHECK);
	  for (i = 0; i < n1; i++) {
	     A = GCAGET(Lp1,i);
	     A1 = MIPEMV(1,Q,A,1);
	     GCASET(T1,i,A1);
	     A = LIST2(i,A);
	     GCASET(Lp1,i,A); }
	  Tb = COMP(T1,Tb);
	  Lb1 = LIST2(d1,LIST2(n1,Lp1));
	  Lb = COMP(Lb1,Lb); }
       Lb = INV(Lb);
       Tb = INV(Tb);

Step3: /* Perform factor combination tests. */
       NORMFCT(Nb,n,p,Q,Qp,q,Bb,Lb,Tb,Gb,Cb,e,dp,c,N1,
	       &Fb,&Nb,&Bb,&Lb,&Tb,&Gb,&Cb,&Nb1);
       F = CONC(F,Fb);
       if (Fb != NIL && Lb != NIL)
	  k = FIRST(SECOND(FIRST(Lb))) - 1;

Step4: /* Check for completion. */
       if (PDEG(Nb) == 0)
	  goto Return;
       if (c < k) {
	  c++;
	  goto Step3; }
       if (F != NIL && ICOMP(Q,Bb) >= 0) {
	  /* all out search for factors, but we have already
	     tested products having degree <= dp. */
	  e = dp + 1;
	  dp = PDEG(Nb)/n - 1;
	  c = 1;
	  goto Step3; }

Step5: /* Prepare the list Ib. */
       Ib = NIL;
       while (Lb != NIL) {
	  ADV(Lb,&L1,&Lb);
	  FIRST2(L1,&d1,&Lp1);
	  FIRST2(Lp1,&n1,&Lp1);
	  Ib1 = NIL;
	  for (i = 0; i < n1; i++) {
	     A = GCAGET(Lp1,i);
	     Ib1 = COMP(FIRST(A),Ib1); }
	  Ib1 = INV(Ib1);
	  Ib = COMP(Ib1,Ib); }
       Ib = INV(Ib);

Return: /* Prepare for return. */
       *F_   = F;
       *Nb_  = Nb;
       *Gb_  = Gb;
       *Bb_  = Bb;
       *Ib_  = Ib;
       *Cb_  = Cb;
       *Nb1_ = Nb1;
       return;
}
