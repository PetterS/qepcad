/*======================================================================
                      IPFAC(r,A; s,c,L)

Integral polynomial factorization.

Inputs
  r : a BETA-digit, r >= 1.
  A : in Z[X1,...,Xr], A non-zero.

Outputs
  s : a BETA-digit, s = sign(A).
  c : in Z, the integer content of A.
  L : a list ((e1,A1),...,(ek,Ak)), k >= 0, with ei in Z, ei > 0,
      Ai in Z[X1,...,Xr], the distinct positive irreducible integral
      factors of A, and A = s * c * A1^e1 * ... * Ak^ek.
======================================================================*/
#include "saclib.h"

void IPFAC(r,A, s_,c_,L_)
       Word r,A, *s_,*c_,*L_;
{
       Word A1,Ab,Ap1,L,L1,Lb,Ls,P,c,cs,e1,rp,s,ss,n;
       Word k,B,t,d,M,N,F,f,B1;

Step1: /* r = 1. */
       if (r == 1) {
         IUPFAC(A,&s,&c,&L);
         goto Return; }

Step2: /* Get monomial factors. */
       IPMONFACT(r,A,&M,&Ab);

Step3: /* Compute sign, content and primitive part. */
       IPSCPP(r,Ab,&s,&cs,&Ab);

Step4: /* Factor content. */
       rp = r - 1;
       IPFAC(rp,cs,&ss,&c,&Ls);

Step5: /* Degree 0. */
       n = PDEG(Ab);  
       if (n == 0) { 
	 L = NIL;
	 goto Step11; }

Step6: /* Degree 1. */
       if (n == 1) { 
	 L = LIST1(LIST2(1,Ab));
	 goto Step11; }

Step7: /* Degree 2. */
       if (n == 2) { 
	 L = IPPFAC2(r,Ab); 
	 goto Step11; }

Step8: /* Look for variable of degree 1 or 2. */
       IPVDEG12(r,Ab,&k,&B);
       if (k > 0) {
	 IPFAC(r,B,&t,&d,&N);
	 L = NIL;
	 while (N != NIL) {
	   ADV(N,&F,&N);
	   FIRST2(F,&f,&B1);
	   B1 = PCPV(r,B1,k,r);
	   B1 = IPABS(r,B1);
	   L = COMP(LIST2(f,B1),L); }
	 goto Step11; }

Step9: /* Compute squarefree factorization of primitive part. */
       if (PDEG(Ab) == 0)
         Lb = NIL;
       else
         Lb = IPSF(r,Ab);

Step10: /* Factor squarefree factors and combine. */
       Lb = INV(Lb);
       L = NIL;
       while (Lb != NIL) {
         ADV(Lb,&P,&Lb);
         FIRST2(P,&e1,&A1);
         L1 = ISFPF(r,A1);
         do {
           ADV(L1,&A1,&L1);
           L = COMP(LIST2(e1,A1),L); } 
	 while (L1 != NIL); }
       
Step11: /* Adjoin monomial factors and factors of content. */
       L = CONC(L,M);
       Ls = INV(Ls);
       while (Ls != NIL) {
         ADV(Ls,&P,&Ls);
         FIRST2(P,&e1,&Ap1);
         A1 = PMON(Ap1,0);
         L = COMP(LIST2(e1,A1),L); }

Return: /* Prepare for return. */
       *s_ = s;
       *c_ = c;
       *L_ = L;
       return;
}
