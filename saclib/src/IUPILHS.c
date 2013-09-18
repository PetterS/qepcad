/*===========================================================================
	    IUPILHS(q,Q,Ab,Bb,Sb,Tb,C; Y,Z,Us,As,Bs)

Integral univariate polynomial initial linear Hensel step.

Inputs
  q : a single-precision power of a prime p.
  Q : in Z, Q = q^2.
  Ab,Bb,Sb,Tb : lists (Ab_1,...,Ab_r), (Bb_1,...,Bb_{r-1}),
                (Sb_1,...,Sb_{r-1}), (Tb_1,...,Tb_{r-1}) of
		elements of Z/(q)[x] such that:
                (1) Bb_{i-1} = Ab_i*Bb_i, for i = 2, ..., r-1.
                (2) Ab_i*Sb_i + Bb_i*Tb_i = 1, for i = 2, ..., r-1.
                (3) deg(Sb_i) < deg(Bb_i) and deg(Tb_i) < deg(Ab_i),
                    for i = 1, ..., r-1.
                (4) ldcf(Ab_i) = 1, for i = 1, ..., r.
                The elements of Ab, Bb, Sb, and Tb are in array
		representation.
  C : in Z[x].  C is congruent to Ab_1*Bb_1 modulo q.

Outputs
  Y,Z : lists (Y_1,...,Y_{r-1}), (Z_1,...,Z_{r-1}) of elements
        of Z/(q)[x]; 
  Us : a list (U_1,...,U_{r-1}) of elements of Z[x], such that
       Y_i, Z_i, U_i satisfy Ab_i*Y_i + Bb_i*Z_i = U_i (mod q).
  As,Bs : lists (As_1,...,As_r), (Bs_1,...,Bs_{r-1}) of elements
          of Z/(Q)[x] such that:
          (1) Bs_{i-1} = As_i*Bs_i, for i = 2, ..., r-1.
          (2) ldcf(Ab_i) = 1, for i = 1, ..., r.
          (3) Ab_i = H_q(As_i), Bb_i = H_q(Bs_i).
          (4) C is congruent to As_1*Bs_1 modulo Q.
===========================================================================*/
#include "saclib.h"

void IUPILHS(q,Q,Ab,Bb,Sb,Tb,C, Y_,Z_,Us_,As_,Bs_)
       Word q,Q,Ab,Bb,Sb,Tb,C, *Y_,*Z_,*Us_,*As_,*Bs_;
{
       Word Ab1,Abt,As,As1,Bb1,Bbt,Bs,Bs1,C1,R1,Sb1,Sbt,Tb1,Tbt,
            Ub1,Us,Us1,Y,Y1,Z,Z1;
       Word *Ap,*Bp,*Sp,*Tp,*Up,*Yp,*Zp;

Step1: /* Initialize. */
       Abt = Ab;
       Bbt = Bb;
       Sbt = Sb;
       Tbt = Tb;
       C1  = C;
       Y   = NIL;
       Z   = NIL;
       Us  = NIL;
       As  = NIL;
       Bs  = NIL;

Step2: /* Loop through the lists. */
       ADV(Abt,&Ab1,&Abt);
       ADV(Bbt,&Bb1,&Bbt);
       ADV(Sbt,&Sb1,&Sbt);
       ADV(Tbt,&Tb1,&Tbt);

Step3: /* Compute Us1 = (As1 * Bs1 - Ab1 * Bb1)/q. */
       R1 = IPDIF(1,C1,IPPROD(1,Ab1,Bb1));
       Us1 = IPEQ(1,R1,PMON(q,0));
       Ub1 = MPHOM(1,q,Us1);

Step4: /* Convert to arrays. */
       Ap = MAPFMUP(Ab1);
       Bp = MAPFMUP(Bb1);
       Sp = MAPFMUP(Sb1);
       Tp = MAPFMUP(Tb1);
       Up = MAPFMUP(Ub1);
       Yp = MAPGET(MAPDEG(Bp));
       Zp = MAPGET(MAPDEG(Ap)-1);

Step5: /* Solve the equation Ap Yp + Bp Zp = Up for Yp and Zp. */
       MAPSE(q,Ap,Bp,Sp,Tp,Up, Yp,Zp);

Step6: /* Convert to lists and free arrays. */
       Y1 = MUPFMAP(Yp);
       Z1 = MUPFMAP(Zp);
       MAPFREE(Ap);
       MAPFREE(Bp);
       MAPFREE(Sp);
       MAPFREE(Tp);
       MAPFREE(Up);
       MAPFREE(Yp);
       MAPFREE(Zp);

Step7: /* Lift Ab1, Bb1. */
       As1 = IPSUM(1,Ab1,IPIP(1,q,Z1));
       Bs1 = IPSUM(1,Bb1,IPIP(1,q,Y1));

Step8: /* Put the results into the output lists and update C1. */
       Y  = COMP(Y1,Y);
       Z  = COMP(Z1,Z);
       Us = COMP(Us1,Us);
       As = COMP(As1,As);
       Bs = COMP(Bs1,Bs);
       C1 = Bs1;

Step9: /* Loop. */
       if (RED(Abt) != NIL)
	  goto Step2;

Step10: /* Clean up. */
       As1 = MIPMON(1,Q,Bs1);
       As = COMP(As1,As);
       Y  = INV(Y);
       Z  = INV(Z);
       Us = INV(Us);
       As = INV(As);
       Bs = INV(Bs);

Return: /* Prepare for return. */
       *Y_  = Y;
       *Z_  = Z;
       *Us_ = Us;
       *As_ = As;
       *Bs_ = Bs;
}
