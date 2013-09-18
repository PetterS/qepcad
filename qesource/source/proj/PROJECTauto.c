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

void QepcadCls::PROJECTauto(Word r, Word A, Word *P_, Word *J_)
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
             /*Int*/ P = RMMPF(P,k);
             /*Int*/ GVPF = P;
             /*Int*/ NMPF[k] = LENGTH(LELTI(P,k));
       if (k == 1) goto Return;

Step3: /* Project. */
       P_k = LELTI(P,k);
       J_k1 = PROJ(k,P_k);
       SLELTI(J,k-1,J_k1);
             /*Int*/ PCEQC = 0;
             /*Int*/ GVPJ = J;
             /*Int*/ J = RMMPJ(J,k-1);
             /*Int*/ GVPJ = J;
             /*Int*/ J_k1 = LELTI(J,k-1);

Step4: /* Factor. */
       R = IPLFAC(k - 1,J_k1);

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

Step5: /* Append. */
       if (PCPROPEC)
	  APPENDEC(P,k-1,R,&P,&F);
       else
	  P = APPEND(P,k - 1,R);

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
