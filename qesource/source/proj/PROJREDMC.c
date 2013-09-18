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

Word QepcadCls::PROJMCmod(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,D,L,Lh,P,R,W,i,t,Q,j,S,Sp;

Step1: /* Obtain coefficients. */
       P = NIL;
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 Ap1 = LELTI(A1,PO_POLY); 

	 /* Deal with projection points! */
	 if (LELTI(A1,PO_TYPE) == PO_POINT) {
	   W = MPOLY(RED(Ap1),NIL,LIST1(LIST2(PT_PRJ,A1)),PO_POINT,PO_KEEP);
	   P = COMP(W,P);
	   continue;
	 }

	 /* Handle the leading coefficient! */
	 L = PLDCF(Ap1); 
	 Lh = NIL;
	 t = 0;
	 /* if (!PCONST(r - 1,L)) {*/
	 if (!VERIFYCONSTSIGN(r-1,IPIP(r-1,ISIGNF(PLBCF(r-1,L)),L),1,GVNA.W)) {
	   W = MPOLY(L,NIL,LIST1(LIST3(PO_LCO,0,A1)),PO_OTHER,PO_KEEP);
	   P = COMP(W,P); 
	   Lh = COMP(L,Lh); 
	   t = 1; }

	 /* If r = 2 then we know the leading coefficient is always enough! */
	 if (r == 2)
	   t = 0;

	 /* If x_{r-1} is a bound variable, and the quantifier is
	    either F or G, then we know we'll only be lifting over
	    full dimensional cells so we don't have to add more 
	    coefficients! */
	 if (t) {
	   j = r - GVNFV - 1;
	   if (j > 0) {
	     Q = LELTI(GVQ,j); /* Quantifier for x_{r-1} */
	     if (Q == FULLDE || Q == FULLDA)
	       t = 0; } }


	 /* If PCMZERROR is set to true, then we only need leading coefficients
            when projecting polynomials of level k+1 or lower. */
	 if (t && PCMZERROR && r <= GVNFV + 1)
	   t = 0;

	 /* If it can be determined that the system of coefficients is
	    inconsistent ... we can stop with just the leading coeff! */
	 if (t) {
	   j = CLOCK();
	   S = COEFSYS(r,Ap1);
  	   if (S == 1 || (Sp = SIMPLIFYSYSLIST(r-1,S,GVNA == NIL ? TRUE : GVNA.W)) == 1)
  	     t = 0; 
 	   else {
 	     QepcadCls Q; Word G;
 	     for(t = 0; t == 0 && Sp != NIL; Sp = RED(Sp))
 	       if ((G = SYSSOLVECAD(r-1,FIRST(Sp),GVNA == NIL ? TRUE : GVNA.W,GVVL,Q)) != NIL) 
	       {
		 /* If there are finitely many solutions, add those points as projection
		    points. */
		 if (ISLIST(G)) {
		   for(Word Lp = G; Lp != NIL; Lp = RED(Lp)) {
		     /* ADD POINTS to PROJECTION POLS! */
		     Word X = NIL; /* List of all sample points up to and inluding FIRST(G) */
		     Word c = Q.GVPC;
		     for(Word I = LELTI(FIRST(Lp),INDX); I != NIL; I = RED(I))
		     {
		       c = LELTI(LELTI(c,CHILD),FIRST(I));
		       Word s = LELTI(c,SAMPLE);
		       X = COMP(ISPRIMIT(s) ? (LENGTH(s) > 3 ? FOURTH(s) : s) : s,X);
		     }
		     W = MPOLY(X,NIL,LIST1(LIST2(PT_NUL,A1)),PO_POINT,PO_KEEP);
		     P = COMP(W,P);
		   }
		 }
		 else
		   t = 1; /* Instead of adding all the other coeffs, better to add system! */
	       }
 	   }	   

	   j = CLOCK() - j;
	   if (PCVERBOSE) {
	     SWRITE("Coef consistency check took "); IWRITE(j); SWRITE("ms\n");
	     if (!t)
	       SWRITE("Found system inconsistent for ");
	     else
	       SWRITE("Unable to determine consistency for ");
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
