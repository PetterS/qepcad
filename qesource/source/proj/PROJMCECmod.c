/*======================================================================
                      P <- PROJMCmod(r,A)

A "safe" half-way implementation of the improved McCallum projection
with equational constraints!  Projects with constraints, but does
not propogate!

\Input
  \parm{r} is a $\beta$--integer.
  \parm{A} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_r]$ of positive degree in $x_r$.
  
\Output
  \parm{P} is the "safe" half-way improved McCallum's projection of $A$.
======================================================================*/
#include "qepcad.h"
#include "db/CAPolicy.h"

Word QepcadCls::PROJMCECmod(Word r, Word A)
{
       Word A1,A2,Ap,Ap1,Ap2,App,D,L,Lh,P,R,W,i,t,Q,j,S,Sp,C;
       Word Ls, Lc,LL,f,rp,fp,tf,T1,fef,esu,AssTmp,Sf,k;

Step0: /* Obtain pivot constraint: If pivot is not all of level k, we can't use it! */
       C = LELTI(GVPIVOT,r);
       for(Word L = C; L != NIL; L = RED(L))
	 if (SECOND(FIRST(L)) != r)
	 {
	   if (PCVERBOSE)
	     SWRITE("Pivot contains a lower level constraint, cannot use it! Reverting to non-eqconst.\n");
	   P = PROJMCmod(r,A);
	   goto Return;
	 }

Step1: /* Obtain coefficients. */
       P = NIL;
       Ap = A;
       while (Ap != NIL) {
	 ADV(Ap,&A1,&Ap);
	 if (C != NIL && !MEMBER(LELTI(A1,PO_LABEL),C)) continue;
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
	 
	 /* Equational constraints invalidated! */
	 if (t)
	 {
	   if (PCVERBOSE)
	   {
	     SWRITE("Pivot constraint at level ");
	     IWRITE(r);
	     SWRITE(" may be nullified.  If nullified on \n");
	     SWRITE("a positive dimensional region equational constraints could be\n");
	     SWRITE("invalid.  Switching to standard projection.\n");
	   }
	   P = PROJMCmod(r,A);
	   goto Return;	   
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
	 Ap1 = LELTI(A1,PO_POLY);
	 if (PDEG(Ap1) < 2) continue;

	 /* discriminants for pivot polynomials are required.  However,
	    discriminants for non-pivot polynomials are only known not
	    to be necessary when either only sign invariance is required
	    of that polynomial, or when its sign-invariance along with the
	    vanishing of a constraint implies its order invariance.	    
	  */
	 if (C != NIL && !MEMBER(LELTI(A1,PO_LABEL),C))
	 {
	   if (r <= 2) continue;
	   if (!PFPRDQ(A1)) continue;
	   if (GVCAP->supports("CONSTORDTEST"))
	   {
	     /* Checks that Ap1 has constant order in V(Ap1,cq) for each
		cq in C.  Better would be to take advantage of any other
		equational constraints --- i.e. non-pivot constraints and
		constraints at lower levels.  Should add later! */
	     bool oiflag = true;
	     for(Word Cp = C; Cp != NIL && oiflag; Cp = RED(Cp))
	     {
	       Word cq = POLFLAB(FIRST(Cp),GVPF);
	       Word tr = GVCAP->CONSTORDTEST(r,Ap1,LIST1(LELTI(cq,PO_POLY)));
	       if (tr != TRUE) oiflag = false;
	     }
	     if (oiflag) {
	       if (PCVERBOSE) {
		 SWRITE("Determined that discriminant of non-pivot polynomial ");
		 IPDWRITE(r,Ap1,GVVL);
		 SWRITE(" may be safely left out of the projection.\n");
		 SWRITE("I.e. the poly will be order-invariant in sections of the pivot.\n");
	       }
	       continue;
	     }
	   }
	   if (PCVERBOSE) {
	     SWRITE("Unable to determine that discriminant of non-pivot polynomial ");
	     IPDWRITE(r,Ap1,GVVL);
	     SWRITE(" may be safely left out of the projection.\n");
	   }
	 }
	 D = IPDSCRQE(r,Ap1);
	 W = MPOLY(D,NIL,LIST1(LIST4(PO_DIS,0,0,A1)),PO_OTHER,PO_KEEP);
	 P = COMP(W,P); }
       
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
	   if (C != NIL &&
	       !MEMBER(LELTI(A1,PO_LABEL),C) &&
	       !MEMBER(LELTI(A2,PO_LABEL),C))
	     continue;
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





/*
Input
 r : a level
 A : an r-level saclib polynomial
 L : a list of r-variate saclib polynomials

Returns TRUE if it is determined that the vanishing of A and 
the elements of L implies that the order of A is constant.
Otherwise returns a GB for A,L and all k-order partials s.t.
some of the partials are not 0.
 */
//Word CONSTORDTEST(Word A, Word L)
//{
  /* Construct Groebner Basis GB for L cup {A}. */
  
  /* Find minimal k such that there is a k-th order 
     partial that is not reduced to 0 by GB. */

  /* Construct S, the set of all k-th order partials. 
     Construct Groebner Basis GB2 for GB cup S. */

  /* If GB2 = [1] return TRUE, else return GB2. */
//}
