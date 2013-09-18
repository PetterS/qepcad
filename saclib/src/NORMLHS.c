/*===========================================================================
    NORMLHS(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B; Qs,Y,Z,Us,As,Bs)

Norm polynomial linear Hensel step.

Inputs
  q : a positive BETA-digit.
  Q : in Z, Q = q^k, k >= 2.
  Qpp : Q / q^2.
  Ab,Bb,Sb,Tb : lists (Ab_1,...,Ab_r),(Bb_1,...,Bb_{r-1}),
                (Sb_1,...,Sb_{r-1}),(Tb_1,...,Tb_{r-1}) of elements
                of Z_q[x] such that
                Ab_i Sb_i + Bb_i Tb_i = 1, deg(Sb_i) < deg(Bb_i),
                deg(Tb_i) < deg(Ab_i) for i = 1,...,r-1 and 
                ldcf(Ab_i) = 1 for i = 1,...,r.

  Ap,Bp : lists (Ap_1,...,Ap_r),(Bp_1,...,Bp_{r-1} of elements of Z_{Q/q}[x]
          such that Ab_i = H_q(Ap_i), Bp_i = H_q(Bp_i)

  Yp,Zp : lists (Yp_1,...,Yp_{r-1}),(Zp_1,...,Zp_{r-1} of elements of Z_q[x]
          such that A_i = Ap_i + (Q/q)Zp_i, B_i = Bp_i + (Q/q)Yp_i.

  U : a list (U_1,...,U_{r-1} of elements of Z[x].
      Yp_i,Zp_i,U_i satisy Ab_i Yp_i + Bb_i Zp_i = U_i (mod q).
  D : in Z_q[x].
  A,B : lists (A_1,...,A_r),(B_1,...,B_{r-1}) of elements of Z_Q[x].
        A_i = Ap_i + (Q/q)Zp_i, B_i = Bp_i + (Q/q)Yp_i for i = 1,...,r-1
        and A_r is the monic associate of B_{r-1}.

Outputs
  Qs : Q * q.
  Y,Z : lists (Y_1,...,Y_{r-1}),(Z_1,...,Z_{r-1}) of elements of Z_q[x].
  Us : a list (U_1,...,U_{r-1}) of elements of Z[x].
       Y_i,Z_i,U_i satisfy Ab_i Y_i + Bb_i Z_i = U_i (mod q).
  As,Bs : lists (As_1,...,As_r), (Bs_1,...,Bs_{r-1}) of elements of Z_{qQ}[x].
          A_i = H_Q(As_i), B_i = H_Q(Bs_i).
===========================================================================*/
#include "saclib.h"

void NORMLHS(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B,
	     Qs_,Y_,Z_,Us_,As_,Bs_)
       Word q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B,
            *Qs_,*Y_,*Z_,*Us_,*As_,*Bs_;
{
       Word As,At,Att,Bs,Qs,Us,Y,Z;

Step1: /* Flatten the factor lists. */
       At = NORMFL(Ap);
       Att = NORMFL(A);

Step2: /* Lift. */
       IUPLHSL(q,Q,Qpp,Ab,Bb,Sb,Tb,At,Bp,Yp,Zp,U,D,Att,B,
	       &Qs,&Y,&Z,&Us,&As,&Bs);
	       
Step3: /* Regroup the factor list. */
       As = NORMRL(Ap,As);

Return: /* Prepare for return. */
       *Qs_ = Qs;
       *Y_  = Y;
       *Z_  = Z;
       *Us_ = Us;
       *As_ = As;
       *Bs_ = Bs;
       return;
}
