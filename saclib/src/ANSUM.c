/*======================================================================
                      ANSUM(A,I,B,J;C,K)

Algebraic number sum.  

Inputs
  A : Integral minimal polynomial for a real algebraic number alpha.
  I : An acceptable isolating interval for alpha.
  B : Integral minimal polynomial for a real algebraic number beta.
  J : An acceptable isolating interval for beta.
Outputs
  C : Integral minimal polynomial for alpha + beta.
  K : An acceptable isolating interval for alpha + beta.
======================================================================*/
#include "saclib.h"

void ANSUM(A,I,B,J, C_,K_)
       Word A,I,B,J, *C_,*K_;

{
  Word C,K;
  Word As,D,Ah,Bs,Ip,Jp,R,s,c,L,M,P,F,Ms,v;


Step1: /* A=0 or B=0. */
  if (A == 0)
    {
    C = B;  K = J;
    goto Return;
    }
  else
    if (B == 0)
      {
      C = A; K = I;
      goto Return;
      }
  Ip = I;  Jp = J;

Step2: /* Compute R(x)=res(A(x-y),B(y)). */
  As = PINV(1,A,2);
  D = LIST4(1,LIST2(0,-1),0,LIST2(1,1));
  Ah = IPSMV(3,As,D);
  Bs = PINV(1,B,1);
  R = IPRES(2,Ah,Bs);

Step3: /* Compute the list M of all irreducible factors of R. */
  IPFAC(1,R,&s,&c,&L);
  M = NIL;
  do
    {
    ADV(L,&P,&L);
    F = SECOND(P);
    M = COMP(F,M);
    }
  while (!(L == NIL));

Step4: /* Remove from the list M all factors with no coefficient
     sign variations in K=Ip+Jp. */
  K = RISUM(Ip,Jp);
  Ms = NIL;
  do
    {
    ADV(M,&F,&M);
    v = IUPVOI(F,K);
    if (v != 0)
      Ms = COMP(F,Ms);
    }
  while (!(M == NIL));
  M = INV(Ms);

Step5: /* If M contains only one factor, F, and F has one
     variation, set c=(F,K). */
  if (RED(M) == NIL && v == 1)
    {
    C = F;  
    goto Return;
    }

Step6: /* Otherwise refine Ip or Jp. */
  s = RNCOMP(RIL(I),RIL(J));
  if (s > 0)
    Ip = IUPIIR(A,Ip);
  else
    Jp = IUPIIR(B,Jp);
  goto Step4;

Return:
       *C_ = C;
       *K_ = K;
       return;
}
