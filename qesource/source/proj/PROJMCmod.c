/*======================================================================
                      P <- PROJMCmod(r,A)

A "safe" half-way implementation of the improved McCallum projection.
We ignore equational constraints!

\Input
  \parm{r} is a $\beta$--integer.
  \parm{A} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_r]$ of positive degree in $x_r$.
  
\Output
  \parm{P} is the "safe" half-way improved McCallum's projection of $A$.
======================================================================*/
#include "qepcad.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

Word QepcadCls::PROJMCmod(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,D,L,Lh,P,R,W,i,t,Q,j,S,Sp;
       Word Ls, Lc,LL,f,rp,fp,tf,T1,fef,esu,AssTmp,Sf;

Step1: /* Obtain coefficients. */
       P = NIL;
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 Ap1 = LELTI(A1,PO_POLY); 

	 /* Deal with projection points!: NOT REALLY IMPLEMENTED RIGHT NOW! */
	 if (LELTI(A1,PO_TYPE) == PO_POINT) {
	   W = MPOLY(RED(Ap1),NIL,LIST1(LIST2(PT_PRJ,A1)),PO_POINT,PO_KEEP);
	   P = COMP(W,P);
	   continue;
	 }

	 /* Handle the leading coefficient! */
	 L = PLDCF(Ap1); 
	 Lh = NIL;
	 t = 0;

	 /*-- TEST NEW --*/
	 if (experimentalExtensionFlag)
	 {
	   bool qfc = qfrCheckNonVanishing(r-1,L,GVNA.W,GVNQFF.W,GVVL.W);
	   if (qfc) continue;
	 }
	 /*-- END TEST NEW --*/

	 if (!VERIFYCONSTSIGN(r-1,IPIP(r-1,ISIGNF(PLBCF(r-1,L)),L),1,GVNA.W)) {
	   W = MPOLY(L,NIL,LIST1(LIST3(PO_LCO,0,A1)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P); 
	   Lh = COMP(L,Lh); 
	   t = 1; }
	 
	 /* If r = 2 OR r-1 is in free variable space, the leading coefficient is always enough! */
	 if (t && (r == 2 || (PCMZERROR && r-1 <= GVNFV))
	     || (experimentalExtensionFlag && qfrCheckNonNullified(r,Ap1,GVNA.W,GVNQFF.W,GVVL.W))
	     )
	   t = 0;
	 else if (t) {
	   T1 = ACLOCK();
	   /**************
            If every factor of the leading coefficient is
	    1 identically non-zero, OR
	    2 of a level corresponding to a FULLDE or FULLDA quantifier, OR
	    3 in free variable space when the PCMZERROR option is used, OR
	    4 has no common zero with the system of all other coefficients
	    Then ... we need only include the leading coefficient. 
	   ****************/
	   /* Loop over each factor f of L, the leading coefficient of Ap1 */	 
	   IPFAC(r-1,L,&Ls,&Lc,&LL);
	   S = 0;
	   fef = 1; /* For every factor ... initially true. */
	   for(Word LLp = LL; t != 0 && fef && LLp != NIL; LLp = RED(LLp))
	   {
	     f = SECOND(FIRST(LLp));
	     PSIMREP(r-1,f,&rp,&fp);
	     Word tf = 0;
	     
	     /* Test 1: identically non-zero */
	     //--ORIGINAL-- tf = tf || VERIFYCONSTSIGN(r-1,f,1,GVNA.W);
	     tf = tf || (experimentalExtensionFlag && qfrCheckNonVanishing(r-1,f,GVNA.W,GVNQFF.W,GVVL.W));
	     
	     /* Test 2: of a level corresponding to a FULLDE or FULLDA quantifier */
	     j = rp - GVNFV;
	     Q = j > 0 ? LELTI(GVQ,j) : NIL;
	     tf = tf || (Q == FULLDE || Q == FULLDA);
	     
	     /* Test 3: in free variable space when the PCMZERROR option is used */
	     tf = tf || PCMZERROR && rp <= GVNFV;

	     /* Test 4: has no common zero with the system of all other coefficients */
	     if (!tf)
	     {
	       /* Get coeff sys for reductum & see if it's unsat */
	       if (S == 0) {
		 AssTmp = (GVNA == NIL) ? TRUE : CHANGEASSUMPTIONSLEVEL(GVNA.W,r-1,1);
		 S = COEFSYS(r,PRED(Ap1));
		 if (S != 1) S = SIMPLIFYSYSLIST(r-1,S,AssTmp); }
	       if (S == 1) { t = 0; continue; }
	       
	       /* Add f to S and do a quick test for unsat */
	       Sf = NIL; for(Word Sp = S; Sp != NIL; Sp = RED(Sp)) Sf = COMP(COMP(f,FIRST(Sp)),Sf);
	       Sf = SIMPLIFYSYSLIST(r-1,Sf,AssTmp);
	       tf = tf || Sf == 1;
	       
	       /* Last resort: Try to determine unsat-ness via CAD! */	     
	       if (!tf)
	       {
		 QepcadCls Q;
		 esu = 1; /* Every System Unsat flag */
		 for(; esu && Sf != NIL; Sf = RED(Sf))
		   esu = (SYSSOLVECAD(r-1,FIRST(Sf),GVNA == NIL ? TRUE : GVNA.W,GVVL,Q) == NIL);
		 /* NOTE: "projection points" need to be implemented so when SYSSOLVECAD returns
		    a list of points, we simply add those to the projection points, rather than
		    giving up and adding all coefficients! */
		 tf = esu;
	       }
	     }
	     fef = fef && tf;
	   }
	   t = !fef;
	   T1 = ACLOCK() - T1;
	   if (PCVERBOSE) {
	     SWRITE("LDCF sufficiency check took "); IWRITE(T1); SWRITE("ms\n");
	     if (!t)
	       SWRITE("Found LDCF sufficient for ");
	     else
	       SWRITE("Unable to determine LDCF sufficiency for ");
	     IPDWRITE(r,Ap1,GVVL);
	     SWRITE("\n");
	   }
	 }

	 /* Handle the rest of the coefficients as needed. */
	 i = 0;
	 while (t) {
	   Ap1 = PRED(Ap1); i++;  L = PLDCF(Ap1);
	   t = 0;
	   if (Ap1 != 0) 
	     if (!PCONST(r - 1,L)) 
	       if (!IPFZT(r - 1,Lh)) {
		 W = MPOLY(L,NIL,LIST1(LIST3(PO_LCO,i,A1)),PO_OTHER,PO_KEEP); 
		 P = COMP(W,P); 
		 Lh = COMP(L,Lh); 
		 t = 1; } } 
	 }

Step2: /* Obtain discriminants. */
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 if (LELTI(A1,PO_TYPE) == PO_POINT) continue;
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
	 if (LELTI(A1,PO_TYPE) == PO_POINT) continue;
	 Ap1 = LELTI(A1,PO_POLY);
	 App = Ap;
	 while (App != NIL) {
	   ADV(App,&A2,&App);
	   if (LELTI(A2,PO_TYPE) == PO_POINT) continue;
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


/* 	     QepcadCls Q; Word G; */
/*  	     for(t = 0; t == 0 && Sp != NIL; Sp = RED(Sp)) */
/*  	       if ((G = SYSSOLVECAD(r-1,FIRST(Sp),GVNA == NIL ? TRUE : GVNA.W,GVVL,Q)) != NIL)  */
/* 	       { */
/* 		 /* If there are finitely many solutions, add those points as projection */
/* 		    points. * / */
/* //		 if (ISLIST(G) && G != NIL) { */
/* if (ISLIST(G) && G == NIL) { //-- JUST HERE BECAUSE LIFTING DOESN'T SUPPORT POINTS */
/* 		   for(Word Lp = G; Lp != NIL; Lp = RED(Lp)) { */
/* 		     /* ADD POINTS to PROJECTION POLS! * / */
/* 		     Word X = NIL; /* List of all sample points up to and inluding FIRST(G) * / */
/* 		     Word c = Q.GVPC; */
/* 		     for(Word I = LELTI(FIRST(Lp),INDX); I != NIL; I = RED(I)) */
/* 		     { */
/* 		       c = LELTI(LELTI(c,CHILD),FIRST(I)); */
/* 		       Word s = LELTI(c,SAMPLE); */
/* 		       X = COMP(ISPRIMIT(s) ? (LENGTH(s) > 3 ? FOURTH(s) : s) : s,X); */
/* 		     } */
/* 		     W = MPOLY(X,NIL,LIST1(LIST2(PT_NUL,A1)),PO_POINT,PO_KEEP); */
/* 		     P = COMP(W,P); */
/* 		   } */
/* 		 } */

