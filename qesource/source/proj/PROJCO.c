/*======================================================================
                      P <- PROJCO(r,A)

Collins' projection.

\Input
  \parm{r} is a $\beta$--integer. $r \geq 2$.
  \parm{A} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_r]$ of positive degree in $x_r$.
  
\Output
  \parm{P} is the Collins' projection of $A$.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::PROJCO(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,D,L,L1,P,P1,R,R1,R11,R2,R21,Rp,Rp1,Rp11,Rp2,
            Rpp,Rs2,S1,Sp1,T,W,ap1,b,d,i,i1,i2,k,t;

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
	   i = i + 1; }
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
	   S1 = NIL;
	   Rp1 = R1;
	   i1 = 0;
	   do {
	     ADV(Rp1,&R11,&Rp1);
	     if (PDEG(R11) >= 1) {
	       Rs2 = NIL;
	       Rp2 = R2;
	       Sp1 = S1;
	       do {
		 ADV(Rp2,&R21,&Rp2);
		 Rs2 = COMP(R21,Rs2);
		 Sp1 = COMP(PLDCF(R21),Sp1);
		 t = IPFZT(r - 1,Sp1); }
	       while (t != 1 && Rp2 != NIL);
	       Rs2 = INV(Rs2);
	       Sp1 = S1;
	       i2 = 0;
	       do {
		 ADV(Rs2,&R21,&Rs2);
		 if (PDEG(R21) >= 1) {
		   L = IPPSCT(r,R11,R21,Sp1);
		   k = 0;
		   while (L != NIL) {
		     ADV(L,&L1,&L);
		     W = MPOLY(L1,NIL,LIST1(LIST6(PO_RES,k,i1,A1,i2,A2)),
			       PO_OTHER,PO_KEEP);
		     P = COMP(W,P);
		     k = k + 1; }
		   Sp1 = COMP(PLDCF(R21),Sp1); }
		 i2 = i2 + 1; }
	       while (Rs2 != NIL); }
	     S1 = COMP(PLDCF(R11),S1);
	     i1 = i1 + 1; }
	   while (Rp1 != NIL); } }

Step5: /* Finish. */
       P = INV(P);
       goto Return;

Return: /* Prepare for return. */
       return(P);
}
