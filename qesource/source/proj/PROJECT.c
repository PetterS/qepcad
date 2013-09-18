/*===========================================================================
                         PROJECT(r,A; P,J)

Projection Phase.
 
\Input
  \item{A} is a list~$(A_1,\ldots,A_r)$, where $A_i$ is a list of
           all the distinct $i$--level normalized input polynomials. 
         
\Output
  \item{P} is a list~$(P_1,\ldots,P_r)$, where $P_i$ is a list of
           $i$--level projection factors.
  \item{J} is a list~$(J_1,\ldots,J_{r-1})$, where $J_i$ is a list of
           $j$--level polynomials.
===========================================================================*/
#include "qepcad.h"

//Word UNNORMALIZEFORMULA

void QepcadCls::PROJECT(Word r, Word A, Word *P_, Word *J_)
{
       Word D,F,J,P,Ps,J_k1,P_k,R,Ths,Thss,k,i;

Step1: /* Initialize. */
       P = LLCOPY(A); 
       J = NIL; for (i=1; i<r; i++) J = COMP(NIL,J);
       k = r; 

Step2: /* Done? */
             /*Int*/ GVLV = k;
             /*Int*/ NMPF[k] = LENGTH(LELTI(P,k));
             /*Int*/ GVPF = P;
             /*Int*/ GVPJ = J;
             /*Int*/ if (INTERACT()) {
	     /*Int*/   if (k > 1)
             /*Int*/     USERINT(LFS("Before Projection"),'b');
             /*Int*/   else
             /*Int*/     USERINT(LFS("At the end of projection phase"),'b'); }
              /*Int*/ if (PCCONTINUE == TRUE) { goto Return; }
             /*Int*/ P = RMMPF(P,k);
             /*Int*/ GVPF = P;
             /*Int*/ NMPF[k] = LENGTH(LELTI(P,k));
       if (k == 1) goto Return;

Step3: /* Project. */
             /*Int*/ Thss = ACLOCK();
       P_k = LELTI(P,k);
             /*Int*/ Ths = ACLOCK();
       J_k1 = PROJ(k,P_k);
       SLELTI(J,k-1,J_k1);
             /*Int*/ PCEQC = 0;
             /*Int*/ Ths = ACLOCK() - Ths;
             /*Int*/ TMPROJ[k - 1] = TMPROJ[k - 1] + Ths;
             /*Int*/ NMPJ[k - 1] = LENGTH(J_k1);
             /*Int*/ GVPJ = J;
             /*Int*/ if (INTERACT()) USERINT(LFS("After Projection"),'c');
             /*Int*/ if (PCCONTINUE == TRUE) { goto Return; }
             /*Int*/ J = RMMPJ(J,k-1);
             /*Int*/ GVPJ = J;
             /*Int*/ J_k1 = LELTI(J,k-1);
             /*Int*/ NMPJ[k - 1] = LENGTH(LELTI(J,k-1));

Step4: /* Factor. */
             /*Int*/ Ths = ACLOCK();
       R = IPLFAC(k - 1,J_k1);
             /*Int*/ Ths = ACLOCK() - Ths;
             /*Int*/ TMIPLFAC[k - 1] = TMIPLFAC[k - 1] + Ths;

StepX: /* Filter out factors that don't vanish given assumptions */
       if (experimentalExtensionFlag)
       {
	 Word Rb = NIL;
	 for(Word Rp = CINV(R); Rp != NIL; Rp = RED(Rp))
	 {
	   Word nextP = LELTI(FIRST(Rp),PO_POLY);
	   bool qfc = qfrCheckNonVanishing(k-1,nextP,GVNA.W,GVNQFF.W,GVVL.W);
	   if (!qfc)
	   {	     
	     Rb = COMP(FIRST(Rp),Rb);
	   }
	   else if (PCVERBOSE)
	   {
	     SWRITE("Found factor ");
	     IPDWRITE(k-1,nextP,GVVL.W);
	     SWRITE(" to be non-zero given assumptions.\n");
	   }
	 }
	 R = Rb;
       }
       if (false)
       {
	 Word AssTmp = (GVNA == NIL) ? TRUE : CHANGEASSUMPTIONSLEVEL(GVNA.W,k-1,1);
	 /* Need to unnormalize AssTmp here! */
	 Word Rb = NIL;
	 for(Word Rp = CINV(R); Rp != NIL; Rp = RED(Rp))
	 {
	   /* must first check whether FIRST(Rp) actually appears in the assumptions! */
	   QepcadCls Qb;
	   Word esu = SYSSOLVECAD(k-1,LIST1(LELTI(FIRST(Rp),PO_POLY)),AssTmp,GVVL.W,Qb);
	   if (esu != NIL)
	     Rb = COMP(FIRST(Rp),Rb);
	   else if (PCVERBOSE)
	   {
	     SWRITE("Found factor ");
	     IPDWRITE(k-1,LELTI(FIRST(Rp),PO_POLY),GVVL.W);
	     SWRITE(" to be non-zero given assumptions.\n");
	   }
	 }
	 R = Rb;
       }

Step5: /* Append. */
             /*Int*/ Ths = ACLOCK();
       if (PCPROPEC)
	  APPENDEC(P,k-1,R,&P,&F);
       else
	  P = APPEND(P,k - 1,R);
             /*Int*/ Ths = ACLOCK() - Ths;
             /*Int*/ TMAPPEND[k - 1] = TMAPPEND[k - 1] + Ths;
             /*Int*/ Thss = ACLOCK() - Thss;
             /*Int*/ TMPROJECT[k - 1] = TMPROJECT[k - 1] + Thss;

Step6: /* Propagate equational constraints. */
       if (PCPROPEC) {
	  /* D = PROPCONS(k,J_k1,R); */
	  D = PROPCONS(k,J_k1,F);
	  UDEQNCONST(D); }

Step7: /* Loop. */
       k = k - 1; goto Step2;

Return: /* Prepare for return. */
       *P_ = P;
       *J_ = J;
       return;
}




