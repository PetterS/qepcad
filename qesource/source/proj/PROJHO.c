/*===========================================================================
                      P <- PROJHO(r,A)

Hong's  projection.

\Input
  \parm{r} is a $\beta$--integer. $r \geq 2$.
  \parm{A} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_r]$ of positive degree in $x_r$.
  
\Output
  \parm{P} is the Hong's projection of $A$.
===========================================================================*/
#include "qepcad.h"

Word QepcadCls::PROJHO(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,D,L,L1,P,Ps,R,R1,R11,R2,Rp,Rp11,Rpp,Rs,Rs1,
            S1,T,W,ap1,b,d,i,k,w;

Step1: /* $r = 2$. */
       if (r > 2) goto Step2;
       P = NIL; Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 if (PCEQC && LELTI(A1,PO_TYPE) != PO_ECON) continue;
	 Ap1 = LELTI(A1,PO_POLY);
	 W = MPOLY(PLDCF(Ap1),NIL,LIST1(LIST3(PO_LCO,0,A1)),PO_OTHER,PO_KEEP);
	 P = COMP(W,P);
	 if (PDEG(Ap1) >= 2) {
	   D = IPDSCRQE(2,Ap1);
	   W = MPOLY(D,NIL,LIST1(LIST4(PO_DIS,0,0,A1)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P); } }
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 Ap1 = LELTI(A1,PO_POLY);
	 App = Ap;
	 while (App != NIL) {
	   ADV(App,&A2,&App);
	   if (PCEQC && 
	       LELTI(A1,PO_TYPE) != PO_ECON && 
	       LELTI(A2,PO_TYPE) != PO_ECON) continue;
	   Ap2 = LELTI(A2,PO_POLY);
	   T = IPRESQE(2,Ap1,Ap2);
	   W = MPOLY(T,NIL,LIST1(LIST6(PO_RES,0,0,A1,0,A2)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P); } }
       P = INV(P);
       goto Return;

Step2: /* Determine number of reducta needed for each $A_i$. */
       Ap = A; R = NIL;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 Ap1 = LELTI(A1,PO_POLY);
	 R1 = LIST1(Ap1);
	 ap1 = PLDCF(Ap1);
	 S1 = LIST1(ap1);
	 b = PCONST(r - 1,ap1);
	 d = 0;
	 Ap1 = PRED(Ap1);
	 while (!b && !d && Ap1 != 0) {
	   R1 = COMP(Ap1,R1);
	   ap1 = PLDCF(Ap1);
	   b = PCONST(r - 1,ap1);
	   if (!b) {
	     S1 = COMP(ap1,S1);
	     d = IPFZT(r - 1,S1); }
	   Ap1 = PRED(Ap1); }
	 R1 = INV(R1);
	 R = COMP(R1,R); }
       R = INV(R);

Step3: /* Process each $R_i$. */
       P = NIL; Rp = R;  Ap = A;
       while (Rp != NIL) {
	 ADV(Rp,&R1,&Rp); ADV(Ap,&A1,&Ap);
	 if (PCEQC && LELTI(A1,PO_TYPE) != PO_ECON) continue;
	 S1 = NIL;
	 i = 0;
	 do {
	   ADV(R1,&R11,&R1);
	   W = MPOLY(PLDCF(R11),NIL,LIST1(LIST3(PO_LCO,i,A1)),
		     PO_OTHER,PO_KEEP);
	   P = COMP(W,P);
	   if (PDEG(R11) >= 2) {
	     Rp11 = IPDMV(r,R11);
	     L = IPPSCT(r,R11,Rp11,S1);
	     k = 0;
	     while (L != NIL) {
	       ADV(L,&L1,&L);
	       W = MPOLY(L1,NIL,LIST1(LIST4(PO_DIS,k,i,A1)),PO_OTHER,PO_KEEP);
	       P = COMP(W,P);
	       k = k + 1; }
	     S1 = COMP(PLDCF(R11),S1); }
	   i++; }
	 while (R1 != NIL); }

Step4: /* Process pairs $R_i$, $R_j$. */
       Rp = R; Ap = A;
       while (Rp != NIL) {
	 ADV(Rp,&R1,&Rp); ADV(Ap,&A1,&Ap);
	 Rpp = Rp; App = Ap;
	 while (Rpp != NIL) {
	   ADV(Rpp,&R2,&Rpp); ADV(App,&A2,&App);
	   if (PCEQC && 
	       LELTI(A1,PO_TYPE) != PO_ECON && 
	       LELTI(A2,PO_TYPE) != PO_ECON) continue;
	   if (LENGTH(R1) > LENGTH(R2)) {
	     Ps = FIRST(R1);
	     Rs = R2;
	     w = 1; }
	   else {
	     Ps = FIRST(R2);
	     Rs = R1;
	     w = 0; }
	   S1 = NIL;
	   i = 0;
	   while (Rs != NIL) {
	     ADV(Rs,&Rs1,&Rs);
	     if (PDEG(Rs1) >= 1) {
	       if (w == 1) L = IPPSCT(r,Ps,Rs1,S1);
	       else        L = IPPSCT(r,Rs1,Ps,S1);
	       k = 0;
	       while (L != NIL) {
		 ADV(L,&L1,&L);
		 if (w == 1)
		   W = MPOLY(L1,NIL,LIST1(LIST6(PO_RES,k,0,A1,i,A2)),
			     PO_OTHER,PO_KEEP);
		 else 
		   W = MPOLY(L1,NIL,LIST1(LIST6(PO_RES,k,i,A1,0,A2)),
			     PO_OTHER,PO_KEEP); 
		 P = COMP(W,P);
		 k++; }                    
	       S1 = COMP(PLDCF(Rs1),S1); }
	     i++; } } }

Step5: /* Finish. */
       P = INV(P);

Return: /* Prepare for return. */
       return(P);
}
