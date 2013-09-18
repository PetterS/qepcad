/*===========================================================================
		      IUSFPMF(A; p,F,C,L)

Integral univariate squarefree polynomial modular factorization.

Input
  A : in Z[x], squarefree, positive, primitive, and of positive degree. 

Outputs
  p : in Z, the least examined prime in SPRIME for which A has the
      fewest modular factors, unless A is found to be irreducible,
      in which case p = 0.
  F : a list (A_1,...,A_r) of monic irreducible elements of Z/(p)[x]
      such that A = a A_1 ... A_r (mod p) where a = ldcf(A) (mod p).
      If p = 0, then F = ().
  C : a characteristic set, the intersection of the degree sets of
      factorizations of A (mod q) over Z/(q) for as many as
      NPMODFAC primes q (fewer only if SPRIME is exhausted or A is
      proved irreducible; NPMODFAC is defined below).
  L : a list ((p_1,F_1),...,(p_t,F_t)) of pairs, t = NPMODFAC-1,
      where p_i is an element of SPRIME and F_i is the distinct-
      degree factorization of A (mod p_i), i.e., F_i is a list
      ((n_1,G_1),...,(n_k,G_k)) of pairs, where G_i is the
      product of all monic irreducible factors of A (mod p_i) of
      degree n_i.  The prime p is not among the primes p_i in
      the list L.  The order in which the p_i's appear in SPRIME
      is preserved in L.  If p = 0, then L = NIL.
===========================================================================*/
#include "saclib.h"

/* number of primes for modular factorization */
#define NPMODFAC 5

/* smallest prime for modular factorization */
#define SPMODFAC 3

void IUSFPMF(A, p_,F_,C_,L_)
       Word A, *p_,*F_,*C_,*L_;
{
       Word B,B1,Bp,C,D,F,F1,Fp,G,H,H1,I,J,L,Lp,P,R,
            a,b,d,e,f,i,j,k,n,p,q,s;

Step1: /* Initialize. */
       p = 0;
       F = NIL;
       n = PDEG(A);
       I = CSUN(IMP2(1,n),1);
       n = n + 1;
       C = IDIF(IMP2(1,n),1);
       L = NIL;
       s = 0;
       a = PLDCF(A);
       i = 0;
       P = RED(SPRIME); /* skip over the prime 2 */
       while (P != NIL && FIRST(P) < SPMODFAC)
          P = RED(P);
       J = PMON(1,0);
       
Step2: /* Get the next suitable prime. */
       if (P == NIL)
	  FAIL("IUSFPMF","Prime list exhausted");
       ADV(P,&q,&P);
       if (IDREM(a,q) != 0) {
	  B = MPHOM(1,q,A);
	  Bp = MUPDER(q,B);
	  if (!EQUAL(MMPGCD(q,B,Bp),J)) {
	     goto Step2; } }
       else {
	  goto Step2; }

Step3: /* Compute distinct degree factorization. */
       B = MPMON(1,q,B);
       G = MMPDDF(q,B);

Step4: /* Compute the factor degree set. */
       H = G;
       R = NIL;
       F1 = NIL;
       k = 0;
       do {
	  ADV(H,&H1,&H);
	  FIRST2(H1,&f,&b);
	  d = PDEG(b);
	  e = d / f;
	  k += e;
	  for (j = 1; j <= e; j++)
	     R = COMP(f,R); }
       while (H != NIL);
       D = CSFPAR(R);
       C = CSINT(C,D);
       if (EQUAL(C,I)) {
	  p = 0;
	  F = NIL;
	  L = NIL;
	  s = 1;
	  goto Return; }
       if (k < n) {
	  p = q;
	  F = G;
	  n = k; }
       L = COMP(LIST2(q,G),L);
       i++;

Step5: /* Loop. */
       if (i < NPMODFAC)
	  goto Step2;

Step6: /* Remove F from the list L. */
       Lp = NIL;
       while (L != NIL) {
	  ADV(L,&G,&L);
	  if (FIRST(G) != p)
	     Lp = COMP(G,Lp); }
       L = Lp;

Step7: /* Completely factor mod p. */
       Fp = NIL;
       while (F != NIL) {
	  ADV(F,&F1,&F);
	  ADV2(F1,&f,&b,&F1);
	  d = PDEG(b);
	  if (d > f) { /* split equal degree factors */
	     B1 = MMPFBL(p,b,f);
	     Fp = CONC(B1,Fp); }
	  else
	     Fp = COMP(b,Fp); }
       F = Fp;

Return: /* Prepare for return. */
       *p_ = p;
       *F_ = F;
       *C_ = C;
       *L_ = L;
       return;
}
