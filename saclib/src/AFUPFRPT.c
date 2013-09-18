/*==========================================================================
		      t <- AFUPFRPT(M,A,B)

Algebraic number field univariate polynomial fast relative-primality test.

Inputs
    M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A,B : in Q(alpha)[x], A != 0 or B != 0.

Outputs
  t : 0 or 1.  If A and B are shown to be relatively prime, then t = 1.
               Otherwise, t = 0 and the test is inconclusive.
==========================================================================*/
#include "saclib.h"

Word AFUPFRPT(M,A,B)
       Word M,A,B;
{
       Word A1,A1p,A2,A2p,Cp,G,Mp,Mpp,P,R,c,p,t;
       Word *Gp,*Sp,*Spp;

Step1: /* A = 0 or B = 0. */
       if (A == 0 || B == 0) {
	  t = 0;
	  goto Return; }

Step2: /* Initialize. */
       P = MPRIME;
       A1 = AFPICR(1,A);
       A2 = AFPICR(1,B);
       IPSRP(2,A1,&R,&A1);
       IPSRP(2,A2,&R,&A2);

Step3: /* Reduce polynomials modulo a prime. */
       if (P == NIL)
	  FAIL("AFUPGCD","Prime list exhausted");
       ADV(P,&p,&P);
       Mp = MPHOM(1,p,M);
       if (PDEG(Mp) < PDEG(M))
	  goto Step3;
       A1p = MPHOM(2,p,A1);
       if (PDEG(A1p) < PDEG(A1))
	  goto Step3;
       A2p = MPHOM(2,p,A2);
       if (PDEG(A2p) < PDEG(A2))
	  goto Step3;

Step4: /* Check if p divides disc(M). */
       Mpp = MUPDER(p,Mp);
       Sp = MAPFMUP(Mp);
       Spp = MAPFMUP(Mpp);
       Gp = MMAPGCD(p,Sp,Spp);
       G = MUPFMAP(Gp);
       MAPFREE(Sp);
       MAPFREE(Spp);
       MAPFREE(Gp);
       if (PDEG(G) > 0)
	  goto Step3;

Step5: /* Compute monic gcd modulo p. */
       Mp = MPMON(1,p,Mp);
       Cp = FRUPGCD(p,Mp,A1p,A2p);
       if (Cp == NIL)
	  goto Step3;

Step6: /* Check degree. */
       c = PDEG(Cp);
       if (c == 0)
	  t = 1;
       else
	  t = 0;

Return: /* Prepare for return. */
       return(t);
}
