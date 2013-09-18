/*======================================================================
                      ANPROD(A,I,B,J; C,K)

Algebraic number product.  

Inputs
  A : minimal polynomial for a real algebraic number alpha.
  I : an acceptable isolating interval for alpha.
  B : minimal polynomial for a real algebraic number beta.
  J : an acceptable isolating interval for beta.
Outputs
  C : minimal polynomial for alpha * beta.
  K : an acceptable isolating interval for beta.
======================================================================*/
#include "saclib.h"


void ANPROD(A,I,B,J, C_,K_)
  Word A,I,B,J, *C_,*K_;
{
  Word C,K;  
  Word As,Bs,Ip,Jp,R,s,c,L,M,P,F,Ms,v;


Step1: /*[a=0 or b=0.]*/
  if (A == 0 || B == 0)
    {
    C = 0; K = LIST2(0,0);
    goto Return;
    }
  Ip = I;  Jp = J;

Step2: /*[Compute R(x)=res((y^n)*A(x/y),B(y)).]*/
  As = IUPQS(A);
  Bs = PINV(1,B,1);
  R = IPRES(2,As,Bs);

Step3: /*[Compute the list M of all irreducible factors of R.]*/
  IPFAC(1,R,&s,&c,&L);
  M = NIL;
  do
    {
    ADV(L,&P,&L);
    F = SECOND(P);
    M = COMP(F,M);
    }
  while (!(L == NIL));

Step4: /*[Remove from the list M all factors with no coefficient
     sign variations in K=Ip+Jp.]*/
  K = RIPROD(Ip,Jp);
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

Step5: /*[If M contains only one factor, F, and its variation
     is one then set c=(F,K).]*/
  if (RED(M) == NIL && v == 1)
    {
    C = F;
    goto Return;
    }

Step6: /*[Otherwise refine I or J and go back to step (5).]*/
  s = RNCOMP(RIL(Ip),RIL(Jp));
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
