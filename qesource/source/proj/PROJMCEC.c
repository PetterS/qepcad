/*===========================================================================
                        P <- PROJMCEC(k,A)

Projection, McCallum, using equational constraints.

Inputs
   k:  a beta-integer, k >= 2.
   A:  a list of the k-level projection factors.

Output
   P:  the McCallum projection of A in the presence of the
       equational constraints E with specified pivot.
===========================================================================*/
#include "qepcad.h"

Word QepcadCls::PROJMCEC(Word k, Word A)
{
       Word A1,A2,Ap,As1,As2,App,Asp1,C,D,Ds,i,L,L1,L2,Lh,Ls,P,R,Rs,t;

Step1: /* Obtain pivot constraint. */
       C = LELTI(GVPIVOT,k);

Step2: /* Initialize loop. */
       Ap = A;
       P = NIL;
       if (Ap == NIL) goto Return;
       t = 0;

Step3: /* Get next projection factor and test its pivot status. */
       ADV(Ap,&A1,&Ap);
       L1 = LELTI(A1,PO_LABEL);
       if (C != NIL && !MEMBER(L1,C)) goto Step7;
       As1 = LELTI(A1,PO_POLY);
	
Step4: /* Include needed coefficients. The original implementation of this
included all coefficients from the leading coefficient down until it could
be concluded that the system consisting of all coefficients included thus
far has only finitely many common (real) zeros. */
	 Asp1 = As1; i = 0;
	 Lh = NIL;
	 do { 
	   L = PLDCF(Asp1);
	   if (PCONST(k - 1,L)) goto Step5;
	   Ls = MPOLY(L,NIL,LIST1(LIST3(PO_LCO,i,A1)),
		      PO_OTHER,PO_KEEP);
	   P = COMP(Ls,P);
	   Lh = COMP(L,Lh);
	   if (k == 2) goto Step5;
	   Asp1 = PRED(Asp1); i++; }
	 while (!IPFZT(k - 1,Lh) && Asp1 != 0);

Step5: /* Include discriminant. */
       if (PDEG(As1) > 1) {
	 Ds = IPDSCRQE(k,As1);
	 D = MPOLY(Ds,NIL,LIST1(LIST4(PO_DIS,0,0,A1)),
		   PO_OTHER,PO_KEEP);
	 P = COMP(D,P); }

Step6: /* Include resultants. */
       if (C == NIL) App = Ap;
       else          App = A;
       while (App != NIL) {
	 ADV(App,&A2,&App);
	 As2 = LELTI(A2,PO_POLY);
	 L2 = LELTI(A2,PO_LABEL);
	 if (C == NIL || t == 1 || !MEMBER(L2,C)) {
	   Rs = IPRESQE(k,As1,As2);
	   R = MPOLY(Rs,NIL,LIST1(LIST6(PO_RES,0,0,A1,0,A2)),
		     PO_OTHER,PO_KEEP);
	   P = COMP(R,P); }
	 if (App == Ap) t = 1; }

Step7: /* Terminate loop. */
       if (Ap != NIL) goto Step3;
       P = INV(P);

Return: /* Prepare for return. */
       return (P);
}
