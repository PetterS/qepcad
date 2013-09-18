/*===========================================================================
		     AFUPGC(M,A,B; C,Ab,Bb)

Algebraic number field univariate polynomial greatest common divisor
and cofactors.

Inputs
    M : in Z[x], the minimal polynomial of an algebraic number alpha.
  A,B : in Q(alpha)[x].

Outputs
     C : in Q(alpha)[x], C is the monic gcd of A and B.
 Ab,Bb : in Q(alpha)[x], the cofactors Ab = A / C and Bb = B / C.
===========================================================================*/
#include "saclib.h"

void AFUPGC(M,A,B,C_,Ab_,Bb_)
       Word M,A,B,*C_,*Ab_,*Bb_;
{
       Word A1,A1p,A2,A2p,Ab,Bb,C,Cp,Ct,D,G,L,Lt,Mp,Mpp,P,Q,Qp,Qt,Qtp,R,T,
            c,d,p,q,qp,qt,t;
       Word *Dp,*Sp,*Spp;

Step1: /* A = B = 0. */
       if (A == 0 && B == 0) {
	  C = 0;
	  Ab = 0;
	  Bb = 0;
	  goto Return; }

Step2: /* A = 0 or B = 0. */
       if (A == 0) {
	  C = AFPMON(1,M,B);
	  Ab = 0;
	  Bb = PINV(0,PLDCF(B),1);
	  goto Return; }
       if (B == 0) {
	  C = AFPMON(1,M,A);
	  Bb = 0;
	  Ab = PINV(0,PLDCF(A),1);
	  goto Return; }

Step3: /* deg A = 1 or deg B = 1. */
       if (PDEG(A) == 1 || PDEG(B) == 1) {
	  AFUPGC1(M,A,B,&C,&Ab,&Bb);
	  goto Return; }


       /* General case. */

Step4: /* Initialize. */
       P = MPRIME;
       A1 = AFPICR(1,A);
       A2 = AFPICR(1,B);
       IPSRP(2,A1,&R,&A1);
       IPSRP(2,A2,&R,&A2);
       Q = 1;
       C = 0;
       Ct = 0;
       Qt = 1;
       q = 1;
       L = NIL;
       d = PDEG(B) + 1;

Step5: /* Reduce polynomials modulo a prime. */
       if (P == NIL)
	  FAIL("AFUPGCD","Prime list exhausted");
       ADV(P,&p,&P);
       Mp = MPHOM(1,p,M);
       if (PDEG(Mp) < PDEG(M))
	  goto Step5;
       A1p = MPHOM(2,p,A1);
       if (PDEG(A1p) < PDEG(A1))
	  goto Step5;
       A2p = MPHOM(2,p,A2);
       if (PDEG(A2p) < PDEG(A2))
	  goto Step5;

Step6: /* Check if p divides disc(M). */
       Mpp = MUPDER(p,Mp);
       Sp = MAPFMUP(Mp);
       Spp = MAPFMUP(Mpp);
       Dp = MMAPGCD(p,Sp,Spp);
       D = MUPFMAP(Dp);
       MAPFREE(Sp);
       MAPFREE(Spp);
       MAPFREE(Dp);
       if (PDEG(D) > 0)
	  goto Step5;

Step7: /* Compute monic gcd modulo p. */
       Mp = MPMON(1,p,Mp);
       Cp = FRUPGCD(p,Mp,A1p,A2p);
       if (Cp == NIL)
	  goto Step5;

Step8: /* Check degree. */
       c = PDEG(Cp);
       if (c == 0)           /* gcd is 1. */
	  goto Step12;
       if (c > d)            /* degree too large, throw prime away */
	  goto Step5;
       if (c < d) {          /* all previous primes were unlucky */
	  C = Cp;
	  d = c;
	  Q = p;
	  Qp = IQ(Q,2);
	  ISQRT(Qp,&Qp,&t);
	  q = ILOG2(Qp);
	  L = NIL;
	  goto Step5; }

Step9: /* Apply Chinese remaindering. */
       if (Q != p) {
	  qp = MDINV(p,MDHOM(p,Q));
	  Qt = IDPR(Q,p);
	  Ct = IPCRA(Q,p,qp,2,C,Cp); }
       
Step10: /* Recover rational coefficients, if possible. */
       Qtp = IQ(Qt,2);
       ISQRT(Qtp,&Qtp,&t);
       qt = ILOG2(Qtp);
       AFUPFMRC(Q,Qp,q,C,L,Qt,Qtp,qt,Ct, &Lt,&G);
       Q = Qt;
       Qp = Qtp;
       q = qt;
       C = Ct;
       L = Lt;
       if (G == NIL)
	  goto Step5;

Step11: /* Trial division. */
       AFUPQR(M,A,G,&Ab,&T);
       if (T != 0)
	  goto Step5;
       else {
	  AFUPQR(M,B,G,&Bb,&T);
	  if (T != 0)
	     goto Step5; }
       C = G;
       goto Return;

Step12: /* Relatively prime. */
       C = PMON(AFFINT(1),0);
       Ab = A;
       Bb = B;

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       *Bb_ = Bb;
}
