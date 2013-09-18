/*===========================================================================
		      AFUPSFN(M,B; s,Bt,F)

Algebraic number field univariate polynomial squarefree norm.

Inputs
  M : in Z[t], the minimal polynomial of an algebraic number alpha.
  B : in Q(alpha)[x].  B is squarefree and deg(B) >= 2.

Outputs
  s : a nonnegative BETA-digit.
  Bt : in Q(alpha)[x].  Bt(alpha,x) = B(alpha,x-t*alpha), and
       the norm of Bt(alpha,x) is squarefree.
  F : a list (F_1,...,F_t) of the positive irreducible factors
      of the norm of Bt(alpha,x).
===========================================================================*/
#include "saclib.h"

void AFUPSFN(M,B,s_,Bt_,F_)

       Word M,B,*s_,*Bt_,*F_;
{
       Word Bp,Bs,Bt,F,Mp,P,R,Rp,S,b,d,n,p,s;

Step1: /* Compute norm and check if it is squarefree. */
       S = PBIN(PMON(1,0),1,PMON(-1,1),0);
       S = RPFIP(2,S);
       S = AFPCR(1,S);
       if (PDEGSV(2,AFPICR(1,B),1) == 0) {
          Bt = AFPCMV(1,M,B,S);
	  s = 1; }
       else {
          Bt = B;
	  s = 0; }
       P = MPRIME;
       n = LENGTH(P);
       d = MDRAN(n) + 1;
       p = LELTI(P,d);
       Mp = PINV(1,M,1);
       while (1) {
	  Bp = AFPICR(1,Bt);
	  IPSRP(2,Bp,&b,&Bp);
	  Bp = PCPV(2,Bp,1,2);
	  if (PDEG(Bp) > 0) {
	    R = MPRES(2,p,MPHOM(2,p,Mp),MPHOM(2,p,Bp));
	    Rp = MUPDER(p,R);
	    if (PDEG(MUPGCD(p,R,Rp)) == 0) {
	      Bs = IPRES(2,Mp,Bp);
	      Bs = IPABS(1,IPIPP(1,Bs));
	      break; } }
	  Bt = AFPCMV(1,M,Bt,S);
	  d = MDRAN(n) + 1;
	  p = LELTI(P,d);
	  s++; }

Step2: /* Factor the norm. */
       F = NORMFAC(M,Bt,Bs);

Return: /* Prepare for return. */
       *s_  = s;
       *Bt_ = Bt;
       *F_  = F;
       return;
}
