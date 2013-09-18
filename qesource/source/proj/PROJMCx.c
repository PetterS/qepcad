/*======================================================================
                      P <- PROJMC(r,A)

McCallum's projection excluding leading coeff's.

\Input
  \parm{r} is a $\beta$--integer. $r = 3$.
  \parm{A} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_r]$ of positive degree in $x_r$.
  
\Output
  \parm{P} is the McCallum's projection of $A$.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::PROJMCx(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,D,L,Lh,P,R,W,i,t;

Step1: /* Obtain coefficients. */
       P = NIL;

Step2: /* Obtain discriminants. */
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 if (PCEQC && LELTI(A1,PO_TYPE) != PO_ECON) continue;        
	 Ap1 = LELTI(A1,PO_POLY);
	 if (PDEG(Ap1) >= 2) {
	   D = IPDSCRQE(r,Ap1);
	   W = MPOLY(D,NIL,LIST1(LIST4(PO_DIS,0,0,A1)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P); } }

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
	   W = MPOLY(R,NIL,LIST1(LIST6(PO_RES,0,0,A1,0,A2)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P); } }

Step4: /* Finish. */
       P = INV(P);
       goto Return;

Return: /* Prepare for return. */
       return(P);
}
