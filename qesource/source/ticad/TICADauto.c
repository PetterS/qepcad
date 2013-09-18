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

Word QepcadCls::TICADauto(Word Q, Word F, Word f, Word P, Word A)
{
       Word As,D,Ps,Ths,Thss,c,cp,k,s,sh,sp,t,R,S;

Step1: /* Initialize. */
       D = INITPCAD();

Step2: /* Choose. */
       GVPC = D;
       P = GVPF;
       CHOOSE(D,&t,&c); 
       if (t == 0 && PCUSEDES == 'n') goto Return;
       k = LELTI(c,LEVEL);
       GVLV = k;                        
       if (k == 0) goto Step4;

Step3: /* Convert. */
       s = LELTI(c,SAMPLE); 
       sh = CONVERT(s,k);
       SLELTI(c,SAMPLE,sh);

Step4: /* Construct stack. */
       Ps = LELTI(P,k + 1); As = LELTI(A,k + 1);
    
       CONSTRUCT(c,k,f,Ps,As);

Step5: /* Evaluate. */
       EVALUATE(c,k,F,A);

Step6: /* Apply equational constraints. */
	if (PCPROPEC == TRUE)
	   APEQC(c,k,P);

Step7: /* Propagate. */
       PROPAGATE(D,c,k,f,Q);
       goto Step2;

Return: /* Prepare for return. */
       return(D);
}





