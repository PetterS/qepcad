/*===========================================================================
		 IUPSQHLL(p,q,A,C; Ap,Bp,Sp,Tp)

Integral univariate polynomial single-precision quadratic Hensel lifting,
list.

Inputs
  p : a medium prime.
  q : a single-precision power of p.
  A : a list (A_1,...,A_r), with r >= 2, of monic, squarefree,
      elements of Z/(p)[x] that are pairwise relatively prime.
  C : in Z[x], with C congruent to c * A_1 * ... * A_r, where p
      does not divide ldcf(C) and c = H_p(ldcf(C)).

Outputs
  Ap: a list (Ap_1,...,Ap_r) of monic elements of Z(q)[x] such that
      A_i = H_p(Ap_i) and C congruent to cp * Ap_1 * ... * Ap_r,
      where cp = H_q(ldcf(C)).
  Bp: a list (Bp_1,...Bp_{r-1}) of elements of Z/(q)[x] such that
      C is congruent to A_1 * ... * A_i * B_i.
  Sp: a list (Sp_1,...,Sp_{r-1}) of elements of Z/(q)[x];
  Tp: a list (Tp_1,...,Tp_{r-1}) of elements of Z/(q)[x];
      such that Ap_i*Sp_i + Bp_i*Tp_i = 1, and deg(Tp_i) < deg(Ap_i).
===========================================================================*/
#include "saclib.h"

void IUPSQHLL(p,q,A,C,Ap_,Bp_,Sp_,Tp_)
       Word p,q,A,C,*Ap_,*Bp_,*Sp_,*Tp_;
{
       Word Ab,Ap,As,B,Bb,Bp,Bs,Cb,Cp,L,R,Sb,Sp,Ss,Tb,Tp,Ts;

Step1: /* Initialize. */
       Ap = NIL;
       Bp = NIL;
       Sp = NIL;
       Tp = NIL;
       L  = A;
       Cp = MPHOM(1,q,C);
       B  = Cp;

Step2: /* Lift factors. */
       while (RED(L) != NIL) {
	  ADV(L,&Ab,&L);
	  Cb = MPHOM(1,p,Cp);
	  Bb = MPQ(1,p,Cb,Ab);
	  MMPEGC(p,Ab,Bb,&R,&Sb,&Tb);
	  IUPSQHL(p,Ab,Bb,Sb,Tb,q,Cp,&As,&Bs,&Ss,&Ts);
	  Ap = COMP(As,Ap);
	  Bp = COMP(Bs,Bp);
	  Sp = COMP(MPHOM(1,q,Ss),Sp);
	  Tp = COMP(MPHOM(1,q,Ts),Tp);
	  if (RED(L) != NIL)
	     Cp = MPQ(1,q,Cp,As); }
       As = MPMON(1,q,Bs);
       Ap = COMP(As,Ap);
       Ap = INV(Ap);
       Bp = INV(Bp);
       Sp = INV(Sp);
       Tp = INV(Tp);

Return: /* Prepare for return. */
       *Ap_ = Ap;
       *Bp_ = Bp;
       *Sp_ = Sp;
       *Tp_ = Tp;
       return;
}
