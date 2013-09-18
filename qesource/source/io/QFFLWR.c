/*======================================================================
                      QFFLWR(N,V,F)

Quantifier Free Formula Label Write.

\Input
   \parm{N} is a non-null list of characters used as the name of the labels.
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a quantifier-free formula with variables in $V$,
            written out in labels to the output strem.
======================================================================*/
#include "qepcad.h"

void QFFLWR(Word N, Word V, Word F)
{
       Word F1,F2,Fp,T;

Step1: /* Classify the formula F. */
       T = FIRST(F);
       if (T == OROP) goto Step3;
       if (T == ANDOP) goto Step3;
       if (T == NOTOP) goto Step4;
       if (T == RIGHTOP) goto Step5;
       if (T == LEFTOP) goto Step5;
       if (T == EQUIOP) goto Step5;

Step2: /* Atomic formula. */
       ATOMFLWR(N,V,F); goto Return;

Step3: /* Disjunction/Conjunction. */
       Fp = RED(F);
       if (LENGTH(Fp) == 1) { QFFLWR(N,V,FIRST(Fp)); goto Return; }
       SWRITE("[ "); ADV(Fp,&F1,&Fp); QFFLWR(N,V,F1);
       while (Fp != NIL)
         { ADV(Fp,&F1,&Fp); SWRITE(" "); LGOPWR(T); SWRITE(" "); QFFLWR(N,V,F1); }
       SWRITE(" ]");
       goto Return;

Step4: /* Negation. */
       F1 = SECOND(F);
       SWRITE("[ "); LGOPWR(T); SWRITE(" "); QFFLWR(N,V,F1); SWRITE(" ]");
       goto Return;

Step5: /* $\Rightarrow$,$\Leftarrow$, $\Leftrightarrow$. */
       F1 = SECOND(F); F2 = THIRD(F);
       SWRITE("[ "); QFFLWR(N,V,F1); SWRITE(" "); LGOPWR(T);
       SWRITE(" "); QFFLWR(N,V,F2); SWRITE(" ]");
       goto Return;

Return: /* Prepare for return. */
       return;
}
