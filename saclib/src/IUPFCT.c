/*===========================================================================
	IUPFCT(p,Q,Qp,q,C,M,L,G,D,e,d,k; F,Cb,Mb,Lb,Gb,Db)

Integral univariate polynomial factor combination test.

Inputs
  p : an odd medium prime.
  Q : a positive power of p.  
  Qp: the floor of the square root of Q/2.
  q : a BETA-digit, q = ILOG2(Qp).
  C : a positive, primitive, and squarefree integral polynomial.
  M : the two-factor lifting bound for C.
  L : a list of monic factors of C modulo Q whose product is
      congruent to the monic associate of C.
  G : a list of pairs (p_i,G_i), where p_i is an element of
      SPRIME and G_i is the distinct-degree factorization of
      C (mod p_i), i.e., G_i is a list ((n_1,H_1),...,(n_k,H_k))
      of pairs, where H_i is the product of all monic
      irreducible factors of C (mod p_i) of degree n_i.
  D : a characteristic set, a superset of the possible degrees
      of integral factors of C.
  e : a BETA-digit, the minimum degree for trial factors.
  d : a BETA-digit, the maximum degree for trial factors.
  k : a BETA-digit, LENGTH(L) > k >= 1.  No combination of less
      than k elements of L can be converted into an integral
      factor of C.

Outputs
  F : a (possibly empty) list of all the irreducible factors of
      C that were obtained by performing early factor detection
      on combinations of exactly k elements of L, the degree of
      whose product is >= e and <= d.  (But see Notes below.)
  Cb: C divided by the product of the elements of F.
  Mb: the two-factor lifting bound for Cb.  If Cb = 1, then Mb = 0.
  Lb: a (possibly empty) list of pairs, (i,L_i) where L_i is the
      ith element of L and L_i could not be so combined as to
      produce a factor.  If i < j then (i,L_i) precedes (j,L_j)
      in the list Lb, and Lb contains all uncombined factors.
  Gb: a list of pairs (p_i,Gb_i), where p_i is as in the
      specifications of the input variable G above, and Gb_i is
      the distinct-degree factorization of Cb (mod p_i).
  Db: a characteristic set, a superset of the possible degrees
      of integral factors of Cb.  If Cb = 1, then Db = 0.

Notes 
  Attempts are made to convert products of exactly k elements of
  L into irreducible integral factors of C.  If a true factor is
  found then the factor degree set is properly adjusted which
  may show that the remaining polynomial is irreducible, in
  which case it is added to the output list F.  If the degree of
  the remaining polynomial is 2 then it is factored using the
  quadratic formula and the factor(s) so obtained are added to F.
  Otherwise, the two-factor lifting bound is recomputed and if
  this new bound is <= Q and k >= the number of remaining
  factors, then the remaining polynomial must irreducible and it
  is added to F.  If the irreducibility of the remaining
  polynomial has not been determined by any of these three means
  then all other k-combinations of the remaining elements of L
  are tested.  After trying all such combinations, if k is equal
  to one less than the number of remaining elements of L, and Cb
  <= Q, then the remaining polynomial is irreducible and it is
  added to F.  If no tests are successful then all combinations
  of k elements of L will have been tested.
===========================================================================*/
#include "saclib.h"

void IUPFCT(p,Q,Qp,q,C,M,L,G,D,e,d,k,F_,Cb_,Mb_,Lb_,Gb_,Db_)
       Word p,Q,Qp,q,C,M,L,G,D,e,d,k,*F_,*Cb_,*Mb_,*Lb_,*Gb_,*Db_;
{
       Word B,B1,B2,Cb,Ch,Db,Dp,Dpp,Ds,F,Ft,Gb,Gp,G1,
            H1,H1p,I,L1,L1p,Lb,Lp,Mb,*P,T,T1,T2,
            b,b1,b2,c,c1,dp,d1,f1,g,h,h1,i,j,k1,m,n,n1,p1,r,t;

Step1: /* Convert L to an array Lp with tags and initialize Dp, the list 
          of degrees of the remaining modular factors. */
       Dp = NIL;
       LLTGCA(L,&Lp,&n);
       for (i = 0; i < n; i++) { 
          L1 = GCAGET(Lp,i);
          L1p = LIST2(i+1,L1);
          Dp = COMP(PDEG(L1),Dp);
          GCASET(Lp,i,L1p); }

Step2: /* Get arrays for combinations and trailing coefficient products. */
       P = GETARRAY(k);
       T = GCAMALLOC(k,GC_CHECK);

Step3: /* Initialize F,  the list of factors found,
                     Cb, the polynomial that remains to be factored,
                     Gb, the other modular factors of the remaining poly,
                     Mb, the single-factor bound of Cb,
                     Db, the factor degree set,
                     m,  the number of remaining modular factors,
                     P,  the combination array and
                     t,  the last-changed index. */
       F = NIL;
       Cb = C;
       Gb = G;
       Mb = M;
       Db = D;
       m = n;
       for (i = 0; i < k; i++) 
          P[i] = i;
       t = 0;


       /* Entering the loop executed for each combination. */

Step4: /* Test whether the degree of the factor combination product is a
          possible factor degree and form the list Ds of modular factor
          degrees for this combination. */
       dp = 0;
       Ds = NIL;
       for (i = 0; i < k; i++) {
          f1 = GCAGET(Lp,P[i]);
          d1 = PDEG(SECOND(f1));
          dp = dp + d1;
          if (dp > d)
             goto Step18;
	  Ds = COMP(d1,Ds); }
       if (dp < e)
	  goto Step18;
       if (!ISCSELT(dp,Db))
          goto Step18;
       j = t;
       t = m-1;

Step5: /* Update the trailing coefficient product. */
       if (j == 0)
          T1 = 1;
       else
          T1 = GCAGET(T,j-1);
       for (i = j; i < k; i++) { 
          h = P[i]; 
          f1 = GCAGET(Lp,h);
          L1 = SECOND(f1);
          T2 = PTBCF(1,L1);
          T1 = MIPROD(Q,T1,T2);
          GCASET(T,i,T1); }

Step6: /* Convert the trailing coefficient product to a
          rational number, if possible. */
       r = RNFMRPP(Q,Qp,q,p,T1);
       if (r == NIL)
          goto Step18;
       
Step7: /* Test whether the denominator of r divides the
          leading coefficient of C. */
       b = RNDEN(r); 
       c = PLDCF(C);
       if (IREM(c,b) != 0)
          goto Step18;
       
Step8: /* Compute the modular polynomial product. */
       B = PMON(1,0);
       for (i = 0; i < k; i++) {
          h = P[i];
          f1 = GCAGET(Lp,h);
          L1 = SECOND(f1);
          B = MIPPR(1,Q,B,L1); }

Step9: /* Test whether the product yields factor(s) of Cb. */
       if (PDEG(B) == 2)
          IUPFT2(p,Q,Qp,q,Cb,B,&Ch,&B1,&B2);
       else {
          IUPFT(p,Q,Qp,q,Cb,B,&Ch,&B1);
          B2 = 0; }
       if (B1 == 0)
          goto Step18;

Step10: /* Put the factor(s) in the list of factors found and
           update Cb. */
       F = COMP(B1,F);
       if (B2 != 0)
          F = COMP(B2,F);
       Cb = Ch;

Step11: /* Update the list Dp of degrees of the remaining
           modular factors. */
       do {
          ADV(Ds,&d1,&Ds);
          Dp = LDELETE(d1,Dp); }
       while (Ds != NIL);

Step12: /* Recompute the factor degree set. */
       if (LENGTH(Dp) == 1) { /* Only one remaining modular factor. */
          F = COMP(Cb,F);
          Cb = PMON(1,0);
          Mb = 0;
          Lb = NIL;
          Db = 0;
          goto Step20; }
       else
          Db = CSFPAR(Dp);
       I = CSUN(IMP2(1,PDEG(Cb)),1);
       Gp = NIL;
       while (Gb != NIL) {
          ADV(Gb,&G1,&Gb);
          FIRST2(G1,&p1,&H1);
          b1 = MPHOM(1,p1,B1);
          if (B2 != 0) { /* Taking the product rather than each */
             b2 = MPHOM(1,p1,B2); /* linear factor separately makes */
             b1 = MPPROD(1,p1,b1,b2); } /* the program much simpler. */
          Dpp = NIL;
          H1p = NIL;
          while (H1 != NIL) {
             ADV(H1,&h1,&H1);
             FIRST2(h1,&n1,&h1);
             MPGCDC(1,p1,b1,h1,&c1,&b1,&h1);
             d1 = PDEG(h1);
             if (d1 > 0) {
                k1 = d1/n1;
                for (i = 1; i <= k1; i++)
                   Dpp = COMP(n1,Dpp);
                H1p = COMP(LIST2(n1,h1),H1p); } }
          Db = CSINT(Db,CSFPAR(Dpp)); 
          if (EQUAL(Db,I)) {
             F = COMP(Cb,F);
             Cb = PMON(1,0);
             Mb = 0;
             Lb = NIL;
             Db = 0;
             goto Step20; }
          H1 = INV(H1p);
          Gp = COMP(LIST2(p1,H1),Gp); }
       Gb = INV(Gp); 

Step13: /* Can the remaining polynomial be factored by formula? */
       if (PDEG(Cb) == 2) {
          Ft = IUSFPF2(Cb);
          F = CONC(F,Ft);
          Cb = PMON(1,0);
          Mb = 0;
          Lb = NIL;
          Db = 0;
          goto Step20; }
       
Step14: /* Recompute the two-factor lifting bound. */
       Mb = IUPLB(Cb,2);

Step15: /* Check whether we have lifted beyond the new bound and have
           combined enough factors to prove the irreducibility of the
           remaining polynomial. */
       if (k >= m - k && d >= PDEG(Cb) - 1 && ICOMP(Q,Mb) >= 0) {
          F = COMP(Cb,F);
          Cb = PMON(1,0);
          Mb = 0;
          Lb = NIL;
          Db = 0;
          goto Step20; }

Step16: /* Remove the combined factors from the array Lp. */
       j = 0;
       g = 0;
       i = 0; 
       do { 
          h = P[i]; 
          while (g < h) { 
             f1 = GCAGET(Lp,g); 
             GCASET(Lp,j,f1);
             j++;
             g++; }
          g = h + 1; 
          i++; }
       while (i < k);  
       while (g < m) { 
          f1 = GCAGET(Lp,g); 
          GCASET(Lp,j,f1);
          j++; 
          g++; }
       h = P[0];
       for (i = 1; i < k; i++)
          P[i] = h+i;

Step17: /* Update the number of remaining factors and test for completion. */
       m = m - k; 
       if (m <= k || P[k-1] >= m) {
          Lb = GCATL(Lp,m);
          goto Step20; }
       else {
          t = 0;
          goto Step4; }

Step18: /* Compute the next combination, if any. */
       i = 1;
       while (i <= k && P[k - i] == m - i)
          i++;
       if (i == k+1)
          Lb = GCATL(Lp,m);
       else {
          h = P[k - i];
          for (j = k - i; j < k; j++) { 
             h++; 
             P[j] = h; }
          j = k - i;
          if (j < t)
             t = j;
          goto Step4; }

Step19: /* Have we combined enough factors and lifted far enough to show
           that the remaining factor is irreducible? */
       if (k >= m-1 && d >= PDEG(Cb) - 1 && ICOMP(Q,Mb) >= 0) {
          F = COMP(Cb,F);
          Cb = PMON(1,0);
          Mb = 0;
          Lb = NIL;
          Db = 0; }

Step20: /* Free arrays. */
       GCAFREE(Lp);
       FREEARRAY(P);
       GCAFREE(T);

Return: /* Prepare for return. */
       *F_ = F;
       *Cb_ = Cb;
       *Mb_ = Mb;
       *Lb_ = Lb;
       *Gb_ = Gb;
       *Db_ = Db;
       return;
}
