/*===========================================================================
		     NORMMF(M,A,N; p,F,C,L)

Norm polynomial modular factorization.

Inputs
  M : in Z[t], the minimal polynomial of an algebraic number alpha.  
  A : in Q(alpha)[x].  The norm of A is squarefree, and deg(A) >= 2.
  N : in Z[x], the norm of A.

Outputs
  p : in Z, the least examined prime in SPRIME for which N has
      the fewest modular factors, unless N is found to be
      irreducible, in which case p = 0.  Only primes greater
      than or equal to MIN_PRIME (defined below) are examined.
      The number NP of primes that are examined is determined
      dynamically as follows.  Unless N is found to be
      irreducible, between MIN_PRIMES and MAX_PRIMES primes are
      examined.  (Both of these constants are defined below.)
      A minimum of MIN_PRIMES are examined, with more being
      examined until the computed factor degree set for A
      contains no more than deg(A)/2 elements, or until
      MAX_PRIMES have been examined.
  F : a list (N_1,...,N_r) of monic irreducible elements of Z/(p)[x]
      such that N = a N_1 ... N_r (mod p) where a = ldcf(N) (mod p).
      If p = 0, then F = ().
  C : a characteristic set, the intersection of the degree sets of
      factorizations of A (mod q) over Z/(q) for the NP primes q
      that were examined.
  L : a list of lists (p_i,(d_1,F_1),(d_2,F_2),...,(d_t,F_t)),
      i = 1, ..., NP-1.  Let M = M_1 * ... * M_s (mod p_i)
      be a complete factorization of M (mod p_i) and let At(t,x)
      be the primitive and positive integral polynomial similar
      to A(t,x).  Then d_i = deg(M_i) and F_i is the distinct-
      degree factorization of N_i(x) = res_t(M_i(t),At(t,x))
      modulo p_i.  That is, F_i is a list ((n_1,G_1),...,(n_r,G_r)),
      where G_j is the product of all the monic ireducible
      factors of N_i of degree n_j.  The prime p is not among
      the p_i.
===========================================================================*/
#include "saclib.h"

#define MIN_PRIME   3  /* smallest prime for factorization */
#define MIN_PRIMES  3  /* minimum number of primes for factorization */
#define MAX_PRIMES 10  /* maximum number of primes for factorization */

void NORMMF(M,A,N, p_,F_,C_,L_)
       Word M,A,N, *p_,*F_,*C_,*L_;
{
       Word Ap,At,B,C,D,F,F1,F1p,Fp,G,G1,H,H1,I,J,K,
            L,Lp,M1,Mp,Ms,N1,Np,Npp,Ns,P,R,
            a,b,d,d1,e,f,f1,h1,i,j,k,k1,n,p,q;

Step1: /* Initialize. */
       p = 0;
       F = NIL;
       I = CSUN(IMP2(1,PDEG(A)),1);
       C = IDIF(IMP2(1,PDEG(A)+1),1);
       n = IMP2(1,PDEG(N));
       L = NIL;
       i = 0;
       P = RED(SPRIME);
       while (P != NIL && FIRST(P) < MIN_PRIME)
          P = RED(P);
       J = PMON(1,0);
       At = AFPICR(1,A);
       IPSRP(2,At,&a,&At);
       At = PCPV(2,At,1,2);
       
Step2: /* Get the next suitable prime. */
       if (P == NIL)
	  FAIL("NORMMF","Prime list exhausted");
       ADV(P,&q,&P);
/*if (MDHOM(q,PLDCF(M)) != 0 && MDHOM(q,PLDCF(N)) != 0) {*/
/* I'm replacing the above with the below.  3/14/97 */
       if (MDHOM(q,PLDCF(M)) != 0 && MDHOM(q,PLDCF(N)) != 0 &&
	   IREM(FIRST(a),q) != 0) {
	  Np = MPHOM(1,q,N);
	  Npp = MUPDER(q,Np);
	  if (!EQUAL(MMPGCD(q,Np,Npp),J))
	     goto Step2; }
       else
	  goto Step2;

Step3: /* Factor minimal polynomial mod q. */
       Mp = MPHOM(1,q,M);
       Ms = MUPFAC(q,Mp);

Step4: /* Compute modular norms. */
       if (LENGTH(Ms) == 1) {
          d1 = PDEG(Mp);
          Np = MPMON(1,q,Np);
          Ns = LIST1(LIST2(d1,Np)); }
       else {
          Ap = MPHOM(2,q,At);
          Ns = NIL;
          while (Ms != NIL) {
             ADV(Ms,&M1,&Ms);
             M1 = PINV(1,M1,1);
             N1 = IPRES(2,M1,Ap); /* Is this more efficient mod q? */
             N1 = MPHOM(1,q,N1);
             N1 = MPMON(1,q,N1);
             d1 = PDEG(M1);
             Ns = COMP(LIST2(d1,N1),Ns); } }

Step5: /* Compute distinct-degree factorization. */
       G = NIL;
       while (Ns != NIL) {
	  ADV(Ns,&N1,&Ns);
	  FIRST2(N1,&d1,&N1);
	  G1 = MMPDDF(q,N1);
	  G = COMP(LIST2(d1,G1),G); }

Step6: /* Compute the factor degree set. */
       H = G;
       k = PDEG(N) + 1;
       K = NIL;
       while (H != NIL) {
	  ADV(H,&H1,&H);
	  FIRST2(H1,&d1,&H1);
	  R = NIL;
	  while (H1 != NIL) {
	     ADV(H1,&h1,&H1);
	     FIRST2(h1,&f,&b);
	     d = PDEG(b);
	     e = d / f;
	     f = f / d1;
	     for (j = 1; j <= e; j++)
		R = COMP(f,R); }
	  K = COMP(LENGTH(R),K);
	  D = CSFPAR(R);
	  C = CSINT(C,D);
	  if (EQUAL(C,I)) {
	     p = 0;
	     F = NIL;
	     L = NIL;
	     goto Return; } }
       k = 1;
       while (K != NIL) {
	  ADV(K,&k1,&K);
	  k1 = IMP2(1,k1);
	  k1 = IDIF(k1,2);
	  k = IPROD(k,k1); }
       if (ICOMP(k,n) < 0) {
	  p = q;
	  F = G;
	  n = k; }
       L = COMP(LIST2(q,G),L);
       i++;

Step7: /* Loop. */
       if ((i < MIN_PRIMES) ||
	   (i < MAX_PRIMES && LENGTH(SFCS(C)) > PDEG(A)/2))
	  goto Step2;

Step8: /* Remove F from the list L. */
       Lp = NIL;
       while (L != NIL) {
	  ADV(L,&G,&L);
	  if (FIRST(G) != p)
	     Lp = COMP(G,Lp); }
       L = Lp;

Step9: /* Completely factor mod p. */
       Fp = NIL;
       while (F != NIL) {
	  ADV(F,&F1,&F);
	  FIRST2(F1,&d1,&F1);
	  F1p = NIL;
	  while (F1 != NIL) {
	     ADV(F1,&f1,&F1);
	     FIRST2(f1,&f,&b);
	     d = PDEG(b);
	     if (d > f) { /* split equal degree factors */
		B = MMPFBL(p,b,f);
		F1p = CONC(B,F1p); }
	     else
		F1p = COMP(b,F1p); }
	  Fp = COMP(LIST2(d1,F1p),Fp); }
       F = Fp;

Return: /* Prepare for return. */
       *p_ = p;
       *F_ = F;
       *C_ = C;
       *L_ = L;
       return;
}
