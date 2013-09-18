/*===========================================================================
                      P <- PROJLA(r,A)

Lazard's projection.

\Input
  \parm{r} is a $\beta$--integer. $r \geq 2$.
  \parm{A} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_r]$ of positive degree in $x_r$.
  
\Output
  \parm{P} is the Lazard's projection of $A$.
===========================================================================*/
#include "qepcad.h"

Word QepcadCls::PROJLA(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,C,D,L,P,R,W;

Step1: /* Obtain Leading/constant coefficients. */
       P = NIL;
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 if (PCEQC && LELTI(A1,PO_TYPE) != PO_ECON) continue;
	 Ap1 = LELTI(A1,PO_POLY); 
	 L = PLDCF(Ap1); 
	 if (!PCONST(r - 1,L)) {
	   W = MPOLY(L,NIL,LIST1(LIST3(PO_LCO,0,A1)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P);            
	   C = PTRCF(Ap1);
	   if (!PCONST(r - 1,C)) {
	     W = MPOLY(C,NIL,LIST1(LIST2(PO_TCO,A1)),PO_OTHER,PO_KEEP);
	     P = COMP(W,P); } } }
       
Step2: /* Obtain discriminants. */
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 if (PCEQC && LELTI(A1,PO_TYPE) != PO_ECON) continue;
	 Ap1 = LELTI(A1,PO_POLY);
	 if (PDEG(Ap1) >= 2) {
	   D = IPDSCRQE(r,Ap1);
	   if (!PCONST(r - 1,D)) {
	     W = MPOLY(D,NIL,LIST1(LIST4(PO_DIS,0,0,A1)),PO_OTHER,PO_KEEP);
	     P = COMP(W,P); } } }

Step3: /* Obtain resultants. */
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
	   R = IPRESQE(r,Ap1,Ap2);
	   if (!PCONST(r - 1,R)) {
	     W = MPOLY(R,NIL,LIST1(LIST6(PO_RES,0,0,A1,0,A2)),
		       PO_OTHER,PO_KEEP);
	     P = COMP(W,P); } } }

Step4: /* Finish. */
       P = INV(P);
       goto Return;

Return: /* Prepare for return. */
       return(P);
}
