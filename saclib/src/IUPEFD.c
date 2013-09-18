/*===========================================================================
	   IUPEFD(p,Q,C,M,L,G,D,d; F,Cb,Gb,Mb,Ib,Db)

Integral univariate polynomial early factor detection.

Inputs
  p : an odd medium prime.
  Q : a positive power of p.
  C : a positive, primitive and squarefree integral polynomial.
  M : in Z, the two-factor lifting bound for C.
  L : a list of monic factors of C modulo Q whose product is equal to C.
  G : a list of pairs (p_i,G_i), where p_i is an element of
      SPRIME and G_i is the distinct-degree factorization of
      C (mod p_i), i.e., G_i is a list ((n_1,H_1),...,(n_k,H_k))
      of pairs, where H_i is the product of all monic
      irreducible factors of C (mod p_i) of degree n_i.
  D : a characteristic set, a superset of the possible degrees of
      integral factors of C.
  d : a non-negative BETA-digit, the maximum degree of trial factors.

Outputs
  F  : a (possibly empty) list of all the irreducible factors
       of C that are obtained by performing early factor
       detection on combinations of elements of L whose product
       is <= d.
  Cb : C divided by the product of the elements of F.
  Gb : a list of pairs (p_i,Gb_i), where p_i is as in the
       specifications of the input variable G above, and Gb_i is
       the distinct-degree factorization of Cb (mod p_i).
  Mb : in Z, the two-factor lifting bound for Cb.  If Cb = 1 then Mb = 0.
  Ib : a (possibly empty) list of increasing indices i where if
       L_i is the i-th element of L then L_i could not be
       combined so as to produce a true factor of C.
  Db : a characteristic set, a superset of the possible degrees of
       integral factors of Cb.  If Cb = 1 then Db = 0.

Note
  For algorithm details, see Collins & Encarnacion "Improved
  Techniques for Factoring Univariate Polynomials", JSC Vol. 21, 
  No. 3 (March 1996)
===========================================================================*/
#include "saclib.h"

void IUPEFD(p,Q,C,M,L,G,D,d,F_,Cb_,Gb_,Mb_,Ib_,Db_)
       Word p,Q,C,M,L,G,D,d,*F_,*Cb_,*Gb_,*Mb_,*Ib_,*Db_;
{
       Word Cb,Db,F,F1,Fp,Gb,*I,Ib,L1,Lb,Lt,Mb,Qp,*S,c,dp,e,i,j,k,n,q,s;

Step1: /* Initialize. */
       Qp = IQ(Q,2);
       ISQRT(Qp,&Qp,&s);
       q = ILOG2(Qp);
       Cb = C;
       Mb = M;
       Lb = L;
       Gb = G;
       Ib = NIL;
       Db = D;
       F = NIL;
       n = LENGTH(L);
       k = n - 1;
       Fp = NIL;
       dp = d;
       e = 1;

Step2: /* Initialize I and S, the arrays for factor removal flags,
		     s, the number of remaining factors and
	             c, the counter for the number of factors to combine. */
       I = GETARRAY(n);
       S = GETARRAY(n);
       for (i = 0; i < n; i++) {
	  I[i] = 1;
	  S[i] = i; }
       s = n;
       c = 1;


       /* Entering loop for each number of factors to combine. */

Step3: /* Perform factor combination tests. */
       IUPFCT(p,Q,Qp,q,Cb,Mb,Lb,Gb,Db,e,dp,c,&Fp,&Cb,&Mb,&Lt,&Gb,&Db);
       F = CONC(F,Fp);

Step4: /* Update factor removal flags and modular factor list. */
       if (Fp != NIL) {
	  k = LENGTH(Lt)-1;
	  Lb = NIL;
	  j = 0;
	  while (Lt != NIL) {
	     ADV(Lt,&L1,&Lt);
	     i = FIRST(L1)-1;
	     F1 = SECOND(L1);
	     while (j < i) {
		I[S[j]] = 0;
		j++; }
	     j++;
	     Lb = COMP(F1,Lb); }
	  for (j = i+1; j < s; j++)
	     I[S[j]] = 0;
	  Lb = INV(Lb);
	  s = 0;
	  for (j = 0; j < n; j++)
	     if (I[j] == 1) {
		S[s] = j;
		s++; } }

Step6: /* Check for completion. */
       if (PDEG(Cb) == 0)
	  s = 0;
       else {
	  if (c < k) {
	     c++;
	     goto Step3; }
	  else if (F != NIL && ICOMP(Q,Mb) >= 0) {
	     /* all out search for factors, but we have already
		tested products having degree <= dp. */
	     e = dp + 1;
	     dp = PDEG(Cb) - 1;
	     c = 1;
	     goto Step3; } }

Step7: /* Prepare the list Ib and free arrays. */
       Ib = NIL;
       for (i = 0; i < s; i++)
	  Ib = COMP(S[i],Ib);
       Ib = INV(Ib);
       FREEARRAY(I);
       FREEARRAY(S);
       
Return: /* Prepare for return. */
       *F_ = F;
       *Cb_ = Cb;
       *Gb_ = Gb;
       *Mb_ = Mb;
       *Ib_ = Ib;
       *Db_ = Db;
       return;
}
