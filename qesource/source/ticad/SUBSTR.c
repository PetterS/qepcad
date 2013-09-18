/*======================================================================
                      S <- SUBSTR(c,k,b,B)

Substitute the rational sample point into the projection factors.

\Input
  \parm{c} is a cell.
  \parm{k} is a positive $\beta$--integer.
  \parm{b} is the $k$-tuple coordinates of a rational sample point.
  \parm{B} is a list~$(B_1,\ldots,B_m)$ of 
           $(k+1)$--variate integral polynomials.

\Output
  \parm{S} is the list~$(S_1,\ldots,,S_m)
            where $S_i = B_i(b_1,\ldots,b_k,x_{k+1})$.
======================================================================*/
#include "qepcad.h"


Word QepcadCls::SUBSTR(Word c, Word k, Word b, Word B)
{
       Word B1,Bp,S,S1;
       Word dV,IV;
       Word P,L,Q,T1,T2,Sp,G,f,i;

Step1: /* Do it. */
       L = NIL;
       S = NIL;
       Bp = B;
       i = 0;
       while (Bp != NIL)
	 {
	   i++;
           ADV(Bp,&B1,&Bp);
           S1 = IPRNME(k + 1,B1,b);

	   /* This is just to warn me that previously we'd be in trouble! */
	   if (PCVERBOSE  && S1 == 0 && k + 1 != GVNV) { 
	     SWRITE("@R");
	   }
	   
Step2: /* Check if S1 vanishes and, if so, whether this invalidates McCallum's projection*/
	   if (S1 == 0 && (PCPROPEC == TRUE || 
			   MEMBER('m',REDI(PCPROJOP,k)) ||
			   MEMBER('p',REDI(PCPROJOP,k))) 
	       && PFPRDQ(LELTI(LELTI(GVPF,k + 1),i))) {
	     if (CELLDIM(c) > 0) {
	       f = ACCCVBCR(k,c,B1,b);
	       if (f != TRUE && !NZFOPQR(c,k,b,B1) && PFCOICQ(k+1,B1,c,GVPF,GVPC) != TRUE) {
		 SWRITE("WARNING! Projection factor ");
		 IPDWRITE(k+1,B1,GVVL);
		 SWRITE("\nis everywhere zero");
		 SWRITE(" in the cylinder ");
		 SWRITE("over the cell ");
		 LWRITE(LELTI(c,INDX));
		 SWRITE(" of postive dimension.  The McCallum projection ");
		 SWRITE("may not be valid.\n"); } }
	     
	     if (CELLDIM(c) == 0 || f == TRUE) {
	       P = DELINPOLR(k,B1,b);
	       if (P != NIL && CELLDIM(c) == 0) {
		 L = COMP(P,L); }
	       else if (P != NIL && CELLDIM(c) > 0) {
		 SWRITE("WARNING! A projection factor is everywhere zero");
		 SWRITE(" in the cylinder \n");
		 SWRITE("over the cell ");
		 LWRITE(LELTI(c,INDX));
		 SWRITE(" of postive dimension.  The McCallum projection \n");
		 SWRITE("may not be valid.\n");
	       }
	     }
	   }

           S = COMP(S1,S);
           }

Step3: /* Searches non-zero substituted projection factors to see if the factors
          of necessary delineating polynomials are included. */
       while(L != NIL) {
	 ADV(L,&P,&L);
	 P = IPPGSD(1,P); /* gets squarefree part */
         for(Sp = S; Sp != NIL && PDEG(P) > 0; Sp = RED(Sp)) {
	   Q = FIRST(Sp);
	   if (Q != 0) {
	     IPGCDC(1,P,IPFRP(1,Q),&G,&T1,&T2);
	     if (PDEG(G) != 0)
	       P = T1; }
	 }
	 if (PDEG(P) > 0) {
	   SWRITE("Error! Delineating polynomial should be added over cell");
	   OWRITE(LELTI(c,INDX));
	   SWRITE("!\n");
	 }	
	 else {
	   if (GVNFV > k+1) {
	     SWRITE("Warning! Some ");
	     IWRITE(k+1);
	     SWRITE("-level projection factor is acting as a \n");
	     SWRITE("delineating polynomial for another!  CAD Simplification does not\n");
	     SWRITE("take this into account!\n");
	   }
	 }	
       }

        S = INV(S);
        goto Return;

Return: /* Prepare for return. */
       return(S);
}

