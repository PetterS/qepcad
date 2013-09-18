/*===========================================================================
			L <- ISFPF(r,A)

Integral squarefree polynomial factorization.

Inputs
  r : a BETA-digit, r >= 1.
  A : in Z[X1,...,Xr], A positive, of positive degree, primitive, and
      squarefree with respect to its main variable Xr.

Outputs
  L : a list (A1,...,Ak), with Ai in Z[X1,...,Xr], the distinct positive
      irreducible factors of A.
===========================================================================*/
#include "saclib.h"

Word ISFPF(r,A)
       Word r,A;
{
       Word Abp,Ap,Ap1,As,As1,B,Bp,B1,C,D,F,L,Lp,Ls,M,N,P,T,Tp,V,
            ap,b,d,f,k,m,n,p,t,v;

Step1: /* r = 1. */
       if (r == 1) {
         L = IUSFPF(A);
         goto Return; }

Step2: /* Degree 1. */
       n = PDEG(A);
       if (n == 1) {
         L = LIST1(A);
         goto Return; }

Step3: /* Degree 2. */
       if (n == 2) {
         L = ISPFAC2(r,A);
         goto Return; }

Step4: /* Look for variable of degree 1 or 2. */
       IPVDEG12(r,A,&k,&B);
       if (k > 0) {
         IPFAC(r,B,&t,&d,&N);
         L = NIL;
         while (N != NIL) {
           ADV(N,&F,&N);
           FIRST2(F,&f,&B1);
           B1 = PCPV(r,B1,k,r);
           B1 = IPABS(r,B1);
           L = COMP(B1,L); }
         goto Return; }

Step5: /* Evaluate to univariate polynomial, As, and factor As. */
       IPCEVP(r,A,&As,&T);
       As = IPABS(1,As);
       As = IPPP(1,As);
       Ls = IUSFPF(As);

Step6: /* As irreducible. */
       if (RED(Ls) == NIL) {
         L = LIST1(A);
         goto Return; }

Step7: /* Translate A to Ap and find prime p not dividing discr(As). */
       T = COMP(0,INV(T));
       Ap = IPTRAN(r,A,T);
       P = LPRIME;
       n = PDEG(As);
       do {
         if (P == NIL)
           FAIL("ISFPF","Prime list exhausted",r,A);
         ADV(P,&p,&P);
         B = MPHOM(1,p,As);
         m = PDEG(B);
         if (m == n) {
           Bp = MUPDER(p,B);
           C = MUPGCD(p,B,Bp);
           k = PDEG(C); } }
       while (m != n || k != 0);

Step8: /* Convert As factors to monic factors modulo p. */
       Lp = NIL;
       do {
         ADV(Ls,&As1,&Ls);
         Ap1 = MPHOM(1,p,As1);
         Ap1 = MPMON(1,p,Ap1);
         Lp = COMP(Ap1,Lp); }
       while (Ls != NIL);

Step9: /* Compute a factor coefficient bound for Abp = Ap*ldcf(Ap). */
       ap = PLDCF(Ap);
       Abp = IPPROD(r,Ap,LIST2(0,ap));
       b = IPGFCB(r,Abp);
       b = IMP2(b,1);
       M = p;
       while (ICOMP(M,b) <= 0)
         M = IDPR(M,p);

Step10: /* Compute factor degree bounds. */
       V = PDEGV(r,Abp);
       D = NIL;
       V = RED(V);
       do {
         ADV(V,&v,&V);
         d = v + 1;
         D = COMP(d,D); }
       while (V != NIL);

Step11: /* Lift modular factors. */
       L = MPIQHL(r,p,Lp,M,D,Ap);

Step12: /* Combine lifted factors. */
       Lp = IPFLC(r,M,D,Ap,L,0);

Step13: /* Translate Ap factors to A factors. */
       Tp = NIL;
       do {
         ADV(T,&t,&T);
         Tp = COMP(INEG(t),Tp); }
       while (T != NIL);
       Tp = INV(Tp);
       L = NIL;
       do {
         ADV(Lp,&Ap1,&Lp);
         L = COMP(IPTRAN(r,Ap1,Tp),L); }
       while (Lp != NIL);

Return: /* Prepare for return. */
       return(L);
}
