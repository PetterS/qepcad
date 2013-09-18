/*===========================================================================
    NORMFCT(N,n,p,Q,Qp,q,B,L,G,C,e,d,k,N1; F,Nb,Bb,Ib,Gb,Cb,Nb1)

Norm polynomial factor combination test.

Inputs
  N : in Z[x], the norm of a polynomial A[alpha,x] in Z[alpha][x],
      where alpha is an algebraic number.  N is squarefree. 
  n : the degree of alpha.
  p : an odd medium prime.
  Q : a positive power of p.  
  Qp: the floor function of the square root of Q/2.
  q : a BETA-digit, q = ILOG2(Qp).
  B : the two-factor lifting bound for N.
  L : a list of pairs ((d_1,L_1),...,(d_s,L_s)).  Let M be the
      minimal polynomial of alpha, and let M_1 * ... * M_s be a
      complete factorization of M (mod p).  Then d_i = deg(M_i)
      and L_i is a pair (n_i,A_i) where A_i is a GCA handle of
      an array with n_i distinct monic irreducible factors of
      res_t(M_i(t),A(t,x)) (mod Q).
  T : a list (T_1,...,T_s) of GCA handles.  The jth element of
      T_i is the value of the the jth element of A_i evaluated
      at 1.
  G : a list of pairs (p_i,G_i), where p_i is an element of
      SPRIME and G_i is a list of pairs (e_i,H_i).
      Let Mb_1 * ... * Mb_r be a complete factorization of M
      (mod p_i).  Then e_i = deg(Mb_i) and H_i is the
      distinct-degree factorization of res_t(Mb_i(t),A[t,x]),
      that is, H_i is a list of pairs (f_j,Hb_j) where Hb_j is
      the product of all monic irreducible factors of H_i of
      degree f_j.
  C : a characteristic set, a superset of the possible degrees
      of integral factors of A(alpha,x).
  e : a BETA-digit, the minimum degree for trial factors of A[alpha,x].
  d : a BETA-digit, the maximum degree for trial factors of A[alpha,x].
  k : a BETA-digit, 1 <= k < LENGTH(L_1).  No combination of
      less than k elements of L_1 can be converted into an
      integral factor of N.
  N1: in Z, N1 = N(1).

Outputs
  F  : a (possibly empty) list of all the irreducible factors of
       N which are obtained by performing early factor detection
       on combinations of modular factors whose product is at
       most d.
  Nb : N divided by the product of the elements of F.
  Bb : in Z, the two-factor lifting bound for Nb.  If Nb = 1,
       then Bb = 0.
  Lb : a list similar to L but with the combined factors removed.
  Tb : a list similar to T but with the combined factors removed.
  Gb : a list obtained from G, having a structure similar to G,
       but with the modular factors that were combined to
       produce a true factor removed.
  Cb : a characteristic set, a superset of the possible degrees
       of integral factors of Ab, where Ab is the polynomial
       corresponding to the norm Nb.  If Nb = 1 then Cb = 0.
  Nb1: in Z, Nb1 = Nb(1).
===========================================================================*/
#include "saclib.h"

void NORMFCT(N,n,p,Q,Qp,q,B,L,T,G,C,e,d,k,N1,
	     F_,Nb_,Bb_,Lb_,Tb_,Gb_,Cb_,Nb1_)
       Word N,n,p,Q,Qp,q,B,L,T,G,C,e,d,k,N1,
            *F_,*Nb_,*Bb_,*Lb_,*Tb_,*Gb_,*Cb_,*Nb1_;
{
       Word Bb,Cb,Ct,D,Db,F,Fb,Fp,F1,Gb,Gp,Gt,G1,G1t,Hb,H1,H1p,
            *I,Ib,Ib1,I1,J,K,
            L1,Lb,Lp,Lpp,Lp1,Nb,Nb1,S,Tb,Tp,Tpp,Tp1,T1,W,W1,
            c1,d_min,d_max,d1,dp,ds,dt,e1,f1,g1,g1p,hb,
            i,j,k1,m,m1,n1,nt,p1,s,t,tp;

       Word all_ok,none_ok;

Step1: /* Initialize. */
       F  = NIL;
       Nb = N;
       Bb = B;
       Lb = L;
       Tb = T;
       Gb = G;
       Cb = C;
       Nb1 = N1;
       Lp = L;
       ADV(Lp,&L1,&Lp);
       FIRST2(L1,&ds,&F1);
       FIRST2(F1,&n1,&L1);
       m = n1;
       Tp = T;
       ADV(Tp,&T1,&Tp);

Stepx: /* Compute minimum and maximum possible degrees for
	  k-combinations. */  
       d_min = d_max = 0;
       for (i = 0; i < k; i++)
	  d_max += PDEG(SECOND(GCAGET(L1,i)));
       d_max /= ds;
       if (d_max < e)
	  goto Return;

       for (i = n1-1; i >= n1-k; i--)
	  d_min += PDEG(SECOND(GCAGET(L1,i)));
       d_min /= ds;
       if (d_min > d)
	  goto Return;

       none_ok = 1;
       all_ok = 1;
       for (i = d_min; i <= d_max; i++)
	  if (ISCSELT(i,Cb))
	     none_ok = 0;
	  else
	     all_ok = 0;

       if (none_ok)
	  goto Step13;

Step2: /* Initialize F,  the list of factors found,
	             Nb, the polynomial that remains to be factored,
		     Gb, the other modular factors,
		     Bb, the two-factor lifting bound of Nb,
		     Cb, the factor-degree set of A[alpha,x],
		     Db, the factor-dergee set for the first set
                         of factors,
		     m,  the number of remaining modular factors
                         in the first group,
		     I,  the combination array,
		     W,  the array of the products of the polynomials
                         evaluated at 1.
		     t,  the last-changed index of combination and
		     tp, the last-changed index of trailing coefficient
                         product. */
       F = NIL;
       Nb = N;
       Gb = G;
       Bb = B;
       Cb = C;
       D = NIL;
       S = SFCS(C);
       while (S != NIL) {
	  ADV(S,&s,&S);
	  D = COMP(s*ds,D); }
       Db = CSFS(D);  /* factor-degree set for first group */
       d_min = ds * e;
       d_max = ds * d;
       m = n1;
       I = GETARRAY(k);
       for (i = 0; i < k; i++)
	  I[i] = i;
       W = GCAMALLOC(k,GC_CHECK);
       t = tp = 0;
       

       /* Entering loop executed of each combination. */
       
Step3: /* Test whether the degree of the factor combination
	  product is a possible factor degree. */
       dp = 0;
       K = NIL;
       for (i = 0; i < k; i++) {
          f1 = SECOND(GCAGET(L1,I[i]));
          dp += PDEG(f1);
	  K = COMP(f1,K); }
       if (!all_ok && ((dp > d_max) || (dp < d_min) || (!ISCSELT(dp,Db))))
	  goto Step12;

Step4: /* Update the product of the polynomials evaluated at 1. */
       if (tp == 0)
	  W1 = 1;
       else
	  W1 = GCAGET(W,tp-1);
       for (i = tp; i < k; i++) {
	  W1 = MIPROD(Q,GCAGET(T1,I[i]),W1);
	  GCASET(W,i,W1); }
       tp = t;

Step5: /* Check if this combination yields a factor. */
       NORMFCTS(Nb,p,Q,Qp,q,LIST1(K),Lp,Tp,dp/ds,W1,Nb1, &Fb,&Nb,&Ib);
       if (PDEG(Fb) == 0)
	  goto Step12;

Step6: /* Put factor in factor list. */
       F = COMP(Fb,F);

Step7: /* Remove combined factors from arrays and update
	  the number of remaining factors. */
       I1 = NIL;
       for (i = k-1; i >= 0; i--)
	  I1 = COMP(I[i],I1);
       ARIE(L1,m,I1);
       ARIE(T1,m,I1);
       m = m - k;
       Lpp = NIL;
       Tpp = NIL;
       while (Ib != NIL) {
	  ADV(Ib,&Ib1,&Ib);
	  ADV(Lp,&Lp1,&Lp);
	  ADV(Tp,&Tp1,&Tp);
	  FIRST2(Lp1,&dt,&Lp1);
	  FIRST2(Lp1,&nt,&Lp1);
	  ARIE(Lp1,nt,Ib1);
	  ARIE(Tp1,nt,Ib1);
	  nt = nt - LENGTH(Ib1);
	  Lp1 = LIST2(nt,Lp1);
	  Lp1 = LIST2(dt,Lp1);
	  Lpp = COMP(Lp1,Lpp);
	  Tpp = COMP(Tp1,Tpp); }
       Lp = INV(Lpp);
       Tp = INV(Tpp);

Step8: /* Recompute factor degree set. */
       Lpp = COMP(LIST2(ds,LIST2(m,L1)),Lp);
       J = CSUN(IMP2(1,PDEG(Nb)/n),1);
       Ct = IDIF(IMP2(1,(PDEG(Nb)/n)+1),1);
       Cb = CSINT(Cb,Ct);
       while (Lpp != NIL) {
	  ADV(Lpp,&Lp1,&Lpp);
	  FIRST2(Lp1,&dt,&Lp1);
	  FIRST2(Lp1,&m1,&Lp1);
	  Ct = NIL;
	  for (i = 0; i < m1; i++) {
	     f1 = SECOND(GCAGET(Lp1,i));
	     d1 = PDEG(f1);
	     Ct = COMP(d1/dt,Ct); }
	  Cb = CSINT(Cb,CSFPAR(Ct));
	  if (EQUAL(Cb,J)) {
	     F = COMP(Nb,F);
	     Nb = PMON(1,0);
	     Bb = 0;
	     Lb = NIL;
	     Tb = NIL;
	     Gb = NIL;
	     Cb = 0;
	     goto Return; } }
       Gp = Gb;
       Gt = NIL;
       while (Gp != NIL) {
	  ADV(Gp,&G1,&Gp);
	  FIRST2(G1,&p1,&G1);  /* p1 = current prime */
	  Fp = MPHOM(1,p1,Fb);
	  G1t = NIL;
	  while (G1 != NIL) {
	     ADV(G1,&H1,&G1); 
	     FIRST2(H1,&e1,&H1); /* e1 = degree of factor of minpoly */
	     Ct = NIL;
	     H1p = NIL;
	     while (H1 != NIL) {
		ADV(H1,&Hb,&H1);
		FIRST2(Hb,&g1,&Hb);
		MPGCDC(1,p1,Fp,Hb,&c1,&Fp,&Hb);
		hb = PDEG(Hb);
		if (hb > 0) {
		   k1 = hb/g1;
		   g1p = g1/e1;
		   for (i = 1; i <= k1; i++)
		      Ct = COMP(g1p,Ct);
		   H1p = COMP(LIST2(g1,Hb),H1p); } }
	     Cb = CSINT(Cb,CSFPAR(Ct));
	     if (EQUAL(Cb,J)) {
		F = COMP(Nb,F);
		Nb = PMON(1,0);
		Bb = 0;
		Lb = NIL;
		Tb = NIL;
		Gb = NIL;
		Cb = 0;
		goto Return; }
	     H1p = INV(H1p);
	     G1t = COMP(LIST2(e1,H1p),G1t); }
	  G1t = INV(G1t);
	  Gt = COMP(LIST2(p1,G1t),Gt); }
       Gb = INV(Gt);

Step9: /* Recompute the two-factor lifting bound and Nb(1). */
       Bb = IUPLB(Nb,2);
       Nb1 = IPEMV(1,Nb,1);

Step10: /* Check whether we have lifted beyond the new bound and
	  have combined enough factors to prove irreducibility
	  of the remaining polynomial. */
       if (k >= m && d >= PDEG(Nb)/n - 1 && ICOMP(Q,Bb) >= 0) {
	  F = COMP(Nb,F);
	  Nb = PMON(1,0);
	  Bb = 0;
	  Lb = NIL;
	  Tb = NIL;
	  Gb = NIL;
	  Cb = 0;
	  Nb1 = 1;
	  goto Return; }

Step11: /* Get next combination after finding a factor. */
       j = I[0];
       t = 0;
       for (i = 1; i < k; i++)
	  I[i] = j+i;
       if (k < m && I[k-1] < m)
	  goto Step3;
       else
	  goto Step13;

Step12: /* Get next combination, if any. */
       LEXNEXTC(m,k,I,&t);
       if (t < tp)
	  tp = t;
       if (I[0] >= 0)
	  goto Step3;
       FREEARRAY(I);

Step13: /* Check whether we have lifted beyond the new bound and
	   have combined enough factors to prove irreducibility
	   of the remaining polynomial. */
       if (k >= m-1 && d >= PDEG(Nb)/n - 1 && ICOMP(Q,Bb) >= 0) {
	  F = COMP(Nb,F);
	  Nb = PMON(1,0);
	  Bb = 0;
	  Lb = NIL;
	  Gb = NIL;
	  Cb = 0;
	  Nb1 = 1; }

Step14: /* Prepare the list Lb. */
       Lp1 = LIST2(ds,LIST2(m,L1));
       Lb = COMP(Lp1,Lp);

Return: /* Prepare for return. */
       *F_  = F;
       *Nb_ = Nb;
       *Bb_ = Bb;
       *Lb_ = Lb;
       *Tb_ = Tb;
       *Gb_ = Gb;
       *Cb_ = Cb;
       *Nb1_ = Nb1;
       return;
}
