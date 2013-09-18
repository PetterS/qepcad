/*===========================================================================
			  Lp <- IPFLC(r,M,I,A,L,D)

Integral polynomial factor list combine.

Inputs
  r : a BETA-digit, r >= 1.
  M : in Z, M > 0.
  I : a list (d1,...,d_{r-1}), with di BETA-digits, di >= 0.
  A : in Z[x_1,...,x_r], A non-constant.
  L : a list (x_1^{d1},...,x_{r-1}^d_{r-1}) of monic factors of
      A modulo M, such that if b is an integral factor of A, then
      H_M,I(B) is an associate of some product of elements of L.
  D : a characteristic set for the possible degrees of integral factors
      of A, or 0.

Outputs
  Lp : a list of the primitive irreducible integral factors of A.
===========================================================================*/
#include "saclib.h"

Word IPFLC(r,M,I,A,L,D)
       Word r,M,I,A,L,D;
{
       Word As,Bs,C,Cs,Lb,Lp,Ls,P,Rs,S,Ss,as,c,cb,cs,d,ds,i,k,p,rp,s,x;

Step1: /* Initialize. */
       d = 1;
       C = A;
       k = LENGTH(L);
       P = PERMR(k);
       Lb = LPERM(L,P);
       Lp = NIL;
       rp = r - 1;

Step2: /* Prepare polynomial. */
       c = PLDCF(C);
       cs = PTBCF(rp,c);
       c = PMON(c,0);
       Cs = IPPROD(r,c,C);
       cb = PTBCF(r,Cs);
       cs = MIHOM(M,cs);

Step3: /* Done. */
       if (d > k / 2) {
	  Lp = COMP(C,Lp);
	  goto Return; }
       Ls = Lb;
       S = NIL;
       for (i = 1; i <= d; i++) {
	  S = COMP(Ls,S);
	  Ls = RED(Ls); }

Step4: /* See if s is A factor. */
       Ss = S;
       as = cs;
       ds = 0;
       while (Ss != NIL) {
	  ADV(Ss,&s,&Ss);
	  p = FIRST(s);
	  ds = ds + PDEG(p);
	  as = MIPROD(M,as,PTBCF(r,p)); }
       as = SMFMI(M,as);
       if (as == 0 && cb != 0)
	  goto Step5;
       if ((D == 0 || IODD(IDP2(D,ds)) == 1) 
	   && (cb == 0 || IREM(cb,as) == 0)) {
	  Ss = S;
	  As = c;
	  while (Ss != NIL) {
	     ADV(Ss,&s,&Ss);
	     p = FIRST(s);
	     As = MIPIPR(r,M,I,As,p); }
	  As = SMFMIP(r,M,As);
	  IPQR(r,Cs,As,&Bs,&Rs);
	  if (Rs == 0)
	     goto Step6; }

Step5: /* Advance to next set. */
       S = LEXNEX(S);
       if (S != NIL)
	  goto Step4;
       d = d + 1;
       goto Step3;

Step6: /* Remove a factor. */
       As = IPPP(r,As);
       Lp = COMP(As,Lp);
       C = IPEQ(r,Bs,PMON(PLDCF(As),0));
       k = k - d;
       do {
	  ADV(S,&s,&S);
	  if (s == Lb)
	     Lb = RED(Lb);
	  else {
	     x = RED(s);
	     Lb = INV(Lb);
	     s = RED(s);
	     Lb = INV(Lb);
	     SRED(s,x); } }
       while (S != NIL);
       goto Step2;

Return: /* Prepare for return. */
       return(Lp);
}
