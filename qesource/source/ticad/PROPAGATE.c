/*======================================================================
                      PROPAGATE(D,c,k,f,Q)

Propagate truth values.

\Input
   \parm{D} is a partial CAD.
   \parm{c} is a cell in $D$.
   \parm{k} is the level of the cell~$c$.
   \parm{f} is the number of free variables in the input formula.
   \parm{Q} is the list $(Q_{f+1},\ldots,Q_r)$  of the quantifiers
            in the input formula.

\Output
   The truth values of the cell~$c$ and some of its ancestors 
   are determined if possible.
   The descendants of each cell whose truth value
   has been determined through the propagation are removed from the
   partial CAD~$D$.
======================================================================*/
#include "qepcad.h"

void PROPAGATE(Word D, Word c, Word k, Word f, Word Q)
{
       Word A0,A1,E0,E1,cp,k0,kp,q,C0;
       /* hide A0,A1,E0,E1,kp; */

Step1: /* Initialize. */
       cp = c; kp = k; k0 = LELTI(D,LEVEL);

Step2: /* Done? */
       if (kp < f  || kp < k0) goto Return;

       /* "X" quantifier! Exactly k */
       q = LELTI(Q,kp + 1 - f);
       if (ISLIST(q) && FIRST(q) == EXISTk) {
	 C0 = TCHILD4EXk(cp,SECOND(q));
	 if (C0 == TRUE || C0 == FALSE)
         { SLELTI(cp,TRUTH,C0); SLELTI(cp,HOWTV,BYPRP); goto Step8;}
	 goto Return; }
       /* End "X" quantifier. */

       /* "C" quantifier! Conected */
       if (LELTI(Q,kp + 1 - f) == CONTQ) {
	 C0 = TCHILD4C(cp);
	 if (C0 == TRUE || C0 == FALSE)
	   { SLELTI(cp,TRUTH,C0); SLELTI(cp,HOWTV,BYPRP); goto Step8;}
	 goto Return; }
       /* End "C" quantifier. */

       /* "F" quantifier! Exists full dimensional (i.e. infinitely many) */
       if (LELTI(Q,kp + 1 - f) == FULLDE) {
	 C0 = TCHILD4FDE(cp);
	 if (C0 == TRUE || C0 == FALSE)
	   { SLELTI(cp,TRUTH,C0); SLELTI(cp,HOWTV,BYPRP); goto Step8;}
	 goto Return; }
       /* End "F" quantifier. */

       /* "G" quantifier! Full dimensional "for all" */
       if (LELTI(Q,kp + 1 - f) == FULLDA) {
	 C0 = TCHILD4FDA(cp);
	 if (C0 == TRUE || C0 == FALSE)
	   { SLELTI(cp,TRUTH,C0); SLELTI(cp,HOWTV,BYPRP); goto Step8;}
	 goto Return; }
       /* End "G" quantifier. */

Step3: /* All true. */
       TCHILD(cp,&A1,&A0,&E1,&E0);
       if (A1)
         { SLELTI(cp,TRUTH,TRUE); SLELTI(cp,HOWTV,BYPRP); goto Step8; }

Step4: /* All false. */
       if (A0)
         { SLELTI(cp,TRUTH,FALSE); SLELTI(cp,HOWTV,BYPRP); goto Step8; }

Step5: /* At least one true, $Q_{k'+1} = \exists$. */
       q = LELTI(Q,kp + 1 - f);
       if (E1 && (q == EXIST))
         { SLELTI(cp,TRUTH,TRUE); SLELTI(cp,HOWTV,BYPRP); goto Step8; }

Step6: /* At least one false and $Q_{k'+1} = \forall$. */
       if (E0 && (q == UNIVER))
         { SLELTI(cp,TRUTH,FALSE); SLELTI(cp,HOWTV,BYPRP); goto Step8; }

Step7: /* Fail to propagate. */
       goto Return;

Step8: /* Prune. */
       SLELTI(cp,CHILD,NIL);
       kp = kp - 1;
       cp = DESCENDANT(D,LELTI(cp,INDX),kp);
       goto Step2;

Return: /* Prepare for return. */
       return;
}



