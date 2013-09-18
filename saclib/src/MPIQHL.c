/*======================================================================
                      Fp <- MPIQHL(r,p,F,M,D,C)

Modular polynomial mod ideal quadratic hensel lemma, list.

Inputs
  r : a BETA-digit, r >= 1.
  p : a BETA-digit, p prime.
  F : a list (f1,...,fm), with fi in Z/(p)[X], fi monic, deg(fi) > 0,
      gcd(fi,fj) = 1 for 1 <= i < j <= m.
  M : in Z, M = p^j for some j in Z, j > 0.
  D : a list (d1,...,d_{r-1}), with di BETA-integers, di >= 0.
  C : in Z[X1,...,Xr], with C(0,...,0,Xr) congruent to f1 * ... * fm,
      and p does not divide ldcf(C).

Outputs
 Fp : a list (fp1,...,fpm), with fpi in
      Z/(M)[X1,...,X_{r-1},x]/(X1^d1,...,X_{r-1}^d_{r-1}), fpi monic,
      deg(fpi) = deg(fi), fpi congruent to fi, C congruent to
      fp1 * ... * fpm.
======================================================================*/
#include "saclib.h"

Word MPIQHL(r,p,F,M,D,C)
       Word r,p,F,M,D,C;
{
       Word A,Ab,B,Bb,Cb,Cp,Dp,Fp,Fs,R,Sb,Tb,i,rp;
       /* hide i,rp; */

Step1: /* Initialize. */
       Fp = NIL;
       Fs = F;
       Cp = IPIHOM(r,D,C);
       Cp = MIPHOM(r,M,Cp);
       B = Cp;
       rp = r - 1;
       Dp = NIL;
       for (i = 1; i <= rp; i++)
         Dp = COMP(1,Dp);

Step2: /* Lift factors. */
       while (Fs != NIL)
         {
         ADV(Fs,&Ab,&Fs);
         Cb = PUFP(r,Cp);
         Cb = MIPHOM(1,p,Cb);
         Bb = MPQ(1,p,Cb,Ab);
         MUPEGC(p,Ab,Bb,&R,&Sb,&Tb);
         Ab = PINV(1,Ab,rp);
         Bb = PINV(1,Bb,rp);
         Sb = PINV(1,Sb,rp);
         Tb = PINV(1,Tb,rp);
         MPIQH(r,p,Dp,Ab,Bb,Sb,Tb,M,D,Cp,&A,&B);
         Fp = COMP(A,Fp);
         if (Fs != NIL)
           MMPIQR(r,M,D,Cp,A,&Cp,&R);
         }
       Fp = INV(Fp);

Return: /* Prepare for return. */
       return(Fp);
}
