/*======================================================================
                      Fs <- RMCAON(F)

Remove Consecutive And's, Or's, and Not's.

\Input
   \parm{F} is a quantifier--free formula.

\Output
   \parm{F*} is a quantifier--free formula obtained from \v{F}
             by removing all the consecutive And's, Or's, and Not's.
======================================================================*/
#include "qepcad.h"

Word RMCAON(Word F)
{
       Word F1,F2,Fp,Fs,Fs1,Fs11,Fs2,T;

Step1: /* Classify the formula $F$. */
       T = FIRST(F);
       if (T == OROP) goto Step3;
       if (T == ANDOP) goto Step3;
       if (T == NOTOP) goto Step3;
       if (T == RIGHTOP) goto Step4;
       if (T == LEFTOP) goto Step4;
       if (T == EQUIOP) goto Step4;

Step2: /* Atomic formula. */
       Fs = F; goto Return;

Step3: /* Disjunction/Conjunction/Negation. */
       Fp = RED(F); Fs = LIST1(T);
       while (Fp != NIL)
         {
         ADV(Fp,&F1,&Fp);
         Fs1 = RMCAON(F1);
         if (FIRST(Fs1) == T)
           {
           Fs1 = RED(Fs1);
           while (Fs1 != NIL) { ADV(Fs1,&Fs11,&Fs1); Fs = COMP(Fs11,Fs); }
           }
         else
           Fs = COMP(Fs1,Fs);
         }
       Fs = INV(Fs);
       goto Return;

Step4: /* $\Rightarrow$,$\Leftarrow$, $\Leftrightarrow$. */
       F1 = SECOND(F); F2 = THIRD(F);
       Fs1 = RMCAON(F1); Fs2 = RMCAON(F2);
       Fs = LIST3(T,Fs1,Fs2);
       goto Return;

Return: /* Prepare for return. */
       return(Fs);
}
