/*===========================================================================
                       D <- PROPCONS(k,Q,F)

Propagate Constraints.

Inputs
   k:  a beta-integer, k >= 2.
   Q:  the list of projection polynomials in k - 1 variables.
   F:  the list of irreducible factors of the polynomials in Q.

Output
   D:  A list of propagated (k - 1)-level constraints.
===========================================================================*/
#include "qepcad.h"

Word QepcadCls::PROPCONS(Word k, Word Q, Word F)
{
       Word C,C1,Cb1,Ch,Ch1,Chp,Cp,Cs,Cs1,Csp,D,D1,Dp,F1,Fp,L1,L11,L12,L3;
       Word P,Pb,Ph,R,R1,R11,R12,Rp,t1,t2;

Step1: /* At least two k-level constraints? */
       D = NIL;
       C = LELTI(GVEQNCONST,k);
       if (LENGTH(C) < 2) goto Return;

Step2: /* Remove constraints sharing a factor with the pivot. */
       P = LELTI(GVPIVOT,k);
       Cp = C;
       Cs = NIL;
       while (Cp != NIL) { 
	  ADV(Cp,&C1,&Cp);
	  if (!LCM(C1,P)) Cs = COMP(C1,Cs); }
       if (Cs == NIL) goto Return;
       Cs = INV(Cs);
       
Step3: /* Propagate factors of level less than k. */
       SEPLAB(k,P,&Pb,&Ph);
       Csp = Cs;
       Ch = NIL;
       while (Csp != NIL) {
	  ADV(Csp,&Cs1,&Csp);
	  SEPLAB(k,Cs1,&Cb1,&Ch1);
	  D1 = LMERGE(Pb,Cb1);
	  D = COMP(D1,D);
	  Ch = COMP(Ch1,Ch); }

Step4: /* Propagate k-level factors. */
       Fp = F;
       while (Fp != NIL) {
	  ADV(Fp,&F1,&Fp);
	  L1 = LELTI(F1,PO_LABEL);
	  R = LOAR(k,Q,F1);
	  Rp = R;
	  while (Rp != NIL) {
	     ADV(Rp,&R1,&Rp);
	     R11 = LELTI(R1,RES_PO_1);
	     R12 = LELTI(R1,RES_PO_2);
	     L11 = LELTI(R11,PO_LABEL);
	     L12 = LELTI(R12,PO_LABEL);
	     t1 = MEMBER(L11,Ph);
	     t2 = MEMBER(L12,Ph);
	     if (t1 == t2) break;
	     if (t1 == 0) L3 = L11;
	     else         L3 = L12;
	     Chp = Ch;
	     Dp = D;
	     while (Chp != NIL) {
		ADV(Chp,&Ch1,&Chp);
		D1 = FIRST(Dp);
		if (MEMBER(L3,Ch1)) {
		   D1 = LMERGE(LIST1(L1),D1);
		   SFIRST(Dp,D1); }
		Dp = RED(Dp); } } }

Return: /* Prepare for return. */
	return(D);
}
