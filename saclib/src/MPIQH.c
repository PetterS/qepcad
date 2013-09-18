/*======================================================================
                      MPIQH(r,p,D,Ab,Bb,Sb,Tb,M,Dp,C; A,B)

Modular polynomial mod ideal, quadratic Hensel lemma.

Inputs
  r : a BETA-digit, r >= 1.
  p : a BETA-digit, p prime.
  D : a list (d1,...,d_{r-1}), with di BETA-digits, di > 0.
 Ab,Bb,Sb,Tb : in Z/(p)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}),
               with Ab monic, deg_Y(Ab) > 0, and Ab*Sb + Bb*Tb = 1.
  M : in Z, M = p^j for some j in Z, j > 0.
 Dp : a list (dp1,...,dp_{r-1}, with dpi BETA-digits, dpi > 0.
  C : in Z[X1,...,Xr], with C congruent to Ab*Bb.


Outputs
 A,B : in Z/(p)[X1,...,X_{r-1},Y]/(X1^dp1,...,X_{r-1}^dp_{r-1}),
       with A monic, deg_Y(A) = deg_Y(Ab), A congruent to Ab,
       B congruent to Bb, and A*B congruent to C.
======================================================================*/
#include "saclib.h"

void MPIQH(r,p,D,Ab,Bb,Sb,Tb,M,Dp,C, A_,B_)
       Word r,p,D,Ab,Bb,Sb,Tb,M,Dp,C, *A_,*B_;
{
       Word A,As,B,Bs,Cb,Dh,Dpp,Ds,S,Ss,T,Ts,d,i;
       /* hide d,i; */

Step1: /* Initialize. */
       Dh = D;
       A = Ab;
       B = Bb;
       S = Sb;
       T = Tb;
       Dpp = CINV(Dp);
       i = r - 1;
       Cb = MPHOM(r,p,C);

Step2: /* Lift in Xi. */
       while (i > 0)
         {
         ADV(Dpp,&d,&Dpp);
         MPIQHS(r,p,Dh,A,B,S,T,i,d,Cb,&As,&Bs,&Ss,&Ts,&Ds);
         A = As;
         B = Bs;
         S = Ss;
         T = Ts;
         Dh = Ds;
         i = i - 1;
         }

Step3: /* Lift to M. */
       IPIQH(r,p,Dp,As,Bs,S,T,M,C,&A,&B);

Return: /* Prepare for return. */
       *A_ = A;
       *B_ = B;
       return;
}
