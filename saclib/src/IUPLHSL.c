/*===========================================================================
   IUPLHSL(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B; Qs,Y,Z,Us,As,Bs)

Integral univariate polynomial linear Hensel step, list.

Inputs
  q : a positive BETA-digit.
  Q : in Z, Q = q^k, k >= 2.
  Qpp : Q / q^2.
  Ab,Bb,Sb,Tb : lists (Ab_1,...,Ab_r), (Bb_1,...,Bb_{r-1}),
                (Sb_1,...,Sb_{r-1}), (Tb_1,...,Tb_{r-1}) of elements
                of Z_q[x] such that
                Ab_i Sb_i + Bb_i Tb_i = 1, deg(Sb_i) < deg(Bb_i),
                deg(Tb_i) < deg(Ab_i), for i = 1, ..., r-1, and 
                ldcf(Ab_i) = 1, for i = 1, ..., r.
  Ap,Bp : lists (Ap_1,...,Ap_r), (Bp_1,...,Bp_{r-1}) of elements
          of Z_{Q/q}[x] such that Ab_i = H_q(Ap_i) and Bp_i = H_q(Bp_i).
  Yp,Zp : lists (Yp_1,...,Yp_{r-1}), (Zp_1,...,Zp_{r-1} of elements
          of Z_q[x] such that A_i = Ap_i + (Q/q)Zp_i and
          B_i = Bp_i + (Q/q)Yp_i.
  U : a list (U_1,...,U_{r-1}) of elements of Z[x] such that
      Yp_i, Zp_i, U_i satisy Ab_i*Yp_i + Bb_i*Zp_i = U_i (mod q).
  D : in Z_q[x].
  A,B : lists (A_1,...,A_r), (B_1,...,B_{r-1}) of elements of Z_Q[x]
        such that A_i = Ap_i + (Q/q)Zp_i and B_i = Bp_i + (Q/q)Yp_i,
        for i = 1, ..., r-1, and A_r is the monic associate of B_{r-1}.

Outputs
  Qs : Q * q.
  Y,Z : lists (Y_1,...,Y_{r-1}), (Z_1,...,Z_{r-1}) of elements of Z_q[x].
  Us : a list (U_1,...,U_{r-1}) of elements of Z[x] such that
       Y_i, Z_i, U_i satisfy Ab_i*Y_i + Bb_i*Z_i = U_i (mod q).
  As,Bs : lists (As_1,...,As_r), (Bs_1,...,Bs_{r-1}) of elements
          of Z_{qQ}[x] such that A_i = H_Q(As_i), B_i = H_Q(Bs_i).
          As_1*Bs_1 = A_1*B_1 + Q*D (mod qQ). 
===========================================================================*/
#include "saclib.h"

void IUPLHSL(q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B, Qs_,Y_,Z_,Us_,As_,Bs_)
       Word q,Q,Qpp,Ab,Bb,Sb,Tb,Ap,Bp,Yp,Zp,U,D,A,B,*Qs_,*Y_,*Z_,*Us_,*As_,*Bs_;
{
       Word A1,Ab1,Abt,Ap1,Apt,As,As1,At,B1,Bb1,Bbt,Bp1,Bpt,Bs,Bs1,Bt,D1,
            Qs,Sb1,Sbt,Tb1,Tbt,U1,Us,Us1,Ut,Y,Y1,Yp1,Ypt,Z,Z1,Zp1,Zpt;
       Word i;

Step1: /* Initialize. */
       Abt = Ab;
       Bbt = Bb;
       Sbt = Sb;
       Tbt = Tb;
       Apt = Ap;
       Bpt = Bp;
       Ypt = Yp;
       Zpt = Zp;
       Ut  = U;
       D1  = D;
       At  = A;
       Bt  = B;
       Y   = NIL;
       Z   = NIL;
       Us  = NIL;
       As  = NIL;
       Bs  = NIL;

Step2: /* Loop through the lists. */
       i = 0;
       while (RED(Abt) != NIL) {
	  i++;
	  ADV(Abt,&Ab1,&Abt);
	  ADV(Bbt,&Bb1,&Bbt);
	  ADV(Sbt,&Sb1,&Sbt);
	  ADV(Tbt,&Tb1,&Tbt);
	  ADV(Apt,&Ap1,&Apt);
	  ADV(Bpt,&Bp1,&Bpt);
	  ADV(Ypt,&Yp1,&Ypt);
	  ADV(Zpt,&Zp1,&Zpt);
	  ADV(Ut,&U1,&Ut);
	  ADV(At,&A1,&At);
	  ADV(Bt,&B1,&Bt);
	  IUPLHS(q,Q,Qpp,Ab1,Bb1,Sb1,Tb1,Ap1,Bp1,Yp1,Zp1,U1,D1,A1,B1,
		 &Y1,&Z1,&Us1,&As1,&Bs1);
	  D1 = Y1;
	  Y  = COMP(Y1,Y);
	  Z  = COMP(Z1,Z);
	  Us = COMP(Us1,Us);
	  As = COMP(As1,As);
	  Bs = COMP(Bs1,Bs); }

Step3: /* Clean up. */
       Qs  = IDPR(Q,q);
       As1 = MIPMON(1,Qs,Bs1);
       As  = COMP(As1,As);
       Y   = INV(Y);
       Z   = INV(Z);
       Us  = INV(Us);
       As  = INV(As);
       Bs  = INV(Bs);

Return: /* Prepare for return. */
       *Qs_ = Qs;
       *Y_  = Y;
       *Z_  = Z;
       *Us_ = Us;
       *As_ = As;
       *Bs_ = Bs;
       return;
}
