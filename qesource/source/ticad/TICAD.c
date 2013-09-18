/*======================================================================
                      D <- TICAD(Q,F,f,P,A)

Truth Invariant CAD Construction Phase.
     
\Input
  \parm{Q} is the list of quantifiers
           in the input formula.
  \parm{F} $=F(x_1,\ldots,x_r)$
           is the normalized input quantifier-free formula.
  \parm{f} is the number of free variables in the input formula.
  \parm{P} is the list~$(P_1,\ldots,P_r)$, 
           where $P_i$ is the list of
           $i$--level projection factors.
  \parm{A} is the list~$(A_1,\ldots,A_r)$,
           where $A_i$ is the list of all
           the distinct $i$--level normalized input polynomials.
 
Output
  \parm{D} is a truth--invariant partial CAD of $f$--space
           in which every leaf cell has a determined truth value.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::TICAD(Word Q, Word F, Word f, Word P, Word A)
{
       Word As,D,Ps,Ths,Thss,c,cp,k,s,sh,sp,t,R,S;

Step1: /* Initialize. */
       D = INITPCAD();
                           /*Int*/ /* GVSBCELL = D;  Now obsolete. */

Step2: /* Choose. */
                           /*Int*/ GVPC = D;
                           /*Int*/ if (INTERACT()) USERINT(LFS("Before Choice"),'d');
                           /*Int*/ if (PCCONTINUE == TRUE) { goto Return; }
                           /*Int*/ Thss = ACLOCK();
			   D = GVPC;
			   P = GVPF;
                           /*Int*/ Ths = Thss;
       CHOOSE(D,&t,&c); 
       if (t == 0 && PCUSEDES == 'n') goto Return;
       if (t == 0 && PCUSEDES == 'y')
          {
          SWRITE("No more desired candidate cells!\n");
          PCNSTEP = 1;
          goto Step2;
	  }
       k = LELTI(c,LEVEL);
                           /*Int*/ Ths = ACLOCK() - Ths;
                           /*Int*/ TMCHOOSE[k + 1] = TMCHOOSE[k + 1] + Ths;
                           /*Int*/ GVLV = k;
                        
       if (k == 0) goto Step4;

Step3: /* Convert. */
                           /*Int*/ Ths = ACLOCK();
       s = LELTI(c,SAMPLE); 
       sh = CONVERT(s,k);
       SLELTI(c,SAMPLE,sh);
                           /*Int*/ Ths = ACLOCK() - Ths;
                           /*Int*/ TMCONVERT[k + 1] = TMCONVERT[k + 1] + Ths;

Step4: /* Construct stack. */
       Ps = LELTI(P,k + 1); As = LELTI(A,k + 1);
    
                           /*Int*/ Ths = ACLOCK();
       /* 
       SPFRPSFT(P,c,k,&R,&S);
       SWRITE("\n\nR = "); OWRITE(R);
       SWRITE("\nS = "); OWRITE(S);
       */
       CONSTRUCT(c,k,f,Ps,As);
                           /*Int*/ Ths = ACLOCK() - Ths;
                           /*Int*/ TMCONSTRUCT[k + 1] = TMCONSTRUCT[k + 1] + Ths;

Step5: /* Evaluate. */
                           /*Int*/ Ths = ACLOCK();
                           /*Int* / if (PCFULL == 'n' || k + 1 == GVNV) CHANGING PCFULL's MEANING */
       EVALUATE(c,k,F,A);
                           /*Int*/ Ths = ACLOCK() - Ths;
                           /*Int*/ TMEVALUATE[k + 1] = TMEVALUATE[k + 1] + Ths;

Step6: /* Apply equational constraints. */
                           /*Int*/ Ths = ACLOCK();
	if (PCPROPEC == TRUE)
	   APEQC(c,k,P);
                           /*Int*/ Ths = ACLOCK() - Ths;
                           /*Int*/ TMAPEQC[k + 1] = TMAPEQC[k + 1] + Ths;

Step7: /* Propagate. */
                           /*Int*/ Ths = ACLOCK();
                           /*Int* / if (PCFULL == 'n') CHANGING PCFULL's MEANING */
       PROPAGATE(D,c,k,f,Q);
                           /*Int*/ Ths = ACLOCK() - Ths;
                           /*Int*/ TMPROPAGATE[k + 1] = TMPROPAGATE[k + 1] + Ths;
                           /*Int*/ Thss = ACLOCK() - Thss;
                           /*Int*/ TMTICAD[k + 1] = TMTICAD[k + 1] + Thss;
       goto Step2;

Return: /* Prepare for return. */
       return(D);
}





