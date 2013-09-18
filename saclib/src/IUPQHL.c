/*===========================================================================
                         Fp <- IUPQHL(p,F,M,C)

Integral univariate polynomial quadratic hensel lemma, list.

Inputs
  p  : a BETA-digit, p prime.
  F  : a list (f1,...,fr), with fi in Z/(p)[X], fi monic,
       gcd(fi,fj) = 1 for 1 <= i < j <= r.
  M  : in Z, M = p^j for some j in Z, j > 0.
  C  : in Z[X], with C congruent to cp * f1 * ... * fr, where cp is the
       residue of ldcf(C) mod p.

Outputs
  Fp : a list (fp1,...,fpr), with fpi in Z/(M)[X], fpi monic, deg(fpi) =
       deg(fi), fpi congruent to fi, C congruent to cp * 1fp1 * ... fpr,
       where cp is the residue of ldcf(C) mod p.
===========================================================================*/
#include "saclib.h"

Word IUPQHL(p,F,M,C)
       Word p,F,M,C;
{
       Word A,Ab,B,Bb,Cb,Cp,Fp,Fs,Q,R,Sb,Tb;

Step1: /* Initialize. */
       Fp = NIL;
       Fs = F;
       Cp = MIPHOM(1,M,C);
       B = Cp;

Step2: /* Lift factors. */
       while (RED(Fs) != NIL) {
	  ADV(Fs,&Ab,&Fs);
	  Cb = MIPHOM(1,p,Cp);
	  Bb = MPQ(1,p,Cb,Ab);
	  MUPEGC(p,Ab,Bb,&R,&Sb,&Tb);
	  IUPQH(p,Ab,Bb,Sb,Tb,M,Cp,&A,&B);
	  Fp = COMP(A,Fp);
	  if (RED(Fs) != NIL)
	     MIUPQR(M,Cp,A,&Cp,&R); }
       MIUPQR(M,B,LIST2(0,PLDCF(B)),&Q,&R);
       Fp = COMP(Q,Fp);
       Fp = INV(Fp);

Return: /* Prepare for return. */
       return(Fp);
}
