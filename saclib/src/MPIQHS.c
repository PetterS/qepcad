/*======================================================================
                      MPIQHS(r,M,D,Ab,Bb,Sb,Tb,s,n,C; A,B,S,T,Dp)

Modular polynomial mod ideal, quadratic Hensel lemma on a single
variable.

Inputs
  r : a BETA-digit, r >= 2.
  M : in Z, M > 0.
  D : a list (d1,...,d_{r-1}), with di BETA-digits, di > 0.
  Ab,Bb,Sb,Tb: in Z/(p)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}),
      with Ab monic, deg_Y(Ab) > 0, and Ab*Sb + Bb*Tb = 1.
  s : a BETA-digit, s < r.
  n : a BETA-digit, n >= 0.
  C : Z/(M)[X1,...,X_{r-1},Y], with C congruent to Ab*Bb.

Outputs
  A,B,S,T : in Z/(M)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{s-1}^d_{s-1},Xs^n,
            X_{s+1}^d_{s+1},...,X_{r-1}^d_{r-1}), 
            with A*S + B*T = 1,
            deg_Y(A) = deg_Y(Ab), 
            A monic, 
            A*B congruent to C, 
            A   congruent to Ab, 
            B   congruent Bb, 
            S   congruent fo Sb, and 
            T   congruent to Tb.
  Dp      : a list (d1,...,d_{s-1},n,d_{s+1},...,d_{r-1}), with di
            BETA-digits, di >= 0.
======================================================================*/
#include "saclib.h"

void MPIQHS(r,M,D,Ab,Bb,Sb,Tb,s,n,C, A_,B_,S_,T_,Dp_)
       Word r,M,D,Ab,Bb,Sb,Tb,s,n,C, *A_,*B_,*S_,*T_,*Dp_;
{
       Word A,As,B,Bs,Db,Dh,Dp,Ds,Dt,I,S,Ss,T,Ts,U,U1,V,Vp,Vpp,Y,Y1,
            Yb,Z,Z1,Zb,d,i;
       /* hide Ds,d,i; */

Step1: /* Initialize. */
       A = Ab;
       B = Bb;
       S = Sb;
       T = Tb;
       I = LIST2(0,1);
       I = PINV(1,I,r - 1);
       Db = D;
       Ds = D;
       Dh = NIL;
       for (i = 1; i <= s - 1; i++)
         {
         ADV(Ds,&d,&Ds);
         Dh = COMP(d,Dh);
         }
       ADV(Ds,&d,&Ds);
       Dt = COMP(n,Ds);
       Dp = CINV(Dh);
       Dp = CONC(Dp,Dt);

Step2: /* Done? */
       if (d > n)
         {
         A = IPIHOM(r,Dp,A);
         B = IPIHOM(r,Dp,B);
         S = IPIHOM(r,Dp,S);
         T = IPIHOM(r,Dp,T);
         }
       if (d >= n)
         goto Return;

Step3: /* Compute Y,Z. */
       V = MIPIPR(r,M,Dp,A,B);
       Vp = MIPDIF(r,M,C,V);
       U = PDPV(r,Vp,s,d);
       MIPISE(r,M,Db,A,B,S,T,U,&Y,&Z);

Step4: /* Compute As,Bs the liftings of A and B. */
       Yb = PDPV(r,Y,s,-d);
       Zb = PDPV(r,Z,s,-d);
       As = MIPSUM(r,M,A,Zb);
       Bs = MIPSUM(r,M,B,Yb);

Step5: /* Compute Y1,Z1. */
       V = MIPIPR(r,M,Dp,As,S);
       Vp = MIPIPR(r,M,Dp,Bs,T);
       Vpp = MIPSUM(r,M,V,Vp);
       V = MIPDIF(r,M,Vpp,I);
       U1 = PDPV(r,V,s,d);
       MIPISE(r,M,Db,A,B,S,T,U1,&Y1,&Z1);

Step6: /* Compute Ss,Ts. */
       Yb = PDPV(r,Y1,s,-d);
       Zb = PDPV(r,Z1,s,-d);
       Ss = MIPDIF(r,M,S,Yb);
       Ts = MIPDIF(r,M,T,Zb);

Step7: /* Update. */
       d = d + d;
       Dt = COMP(d,Ds);
       Db = CINV(Dh);
       Db = CONC(Db,Dt);
       A = As;
       B = Bs;
       S = Ss;
       T = Ts;
       goto Step2;

Return: /* Prepare for return. */
       *A_ = A;
       *B_ = B;
       *S_ = S;
       *T_ = T;
       *Dp_ = Dp;
       return;
}
