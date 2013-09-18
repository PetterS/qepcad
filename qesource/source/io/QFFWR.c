/*======================================================================
                      QFFWR(V,F)

Quantifier Free Formula Write.

\Input
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a quantifier-free formula with variables in $V$,
            written out to the output strem
======================================================================*/
#include "qepcad.h"

void QFFWR(Word V, Word F)
{
       Word F1,F2,Fp,T;

Step1: /* Classify the formula F. */
       if (F == TRUE)  { SWRITE("1 = 1"); goto Return; }
       if (F == FALSE) { SWRITE("1 = 0"); goto Return; }
       T = FIRST(F);
       if (T == OROP) goto Step3;
       if (T == ANDOP) goto Step3;
       if (T == NOTOP) goto Step4;
       if (T == RIGHTOP) goto Step5;
       if (T == LEFTOP) goto Step5;
       if (T == EQUIOP) goto Step5;

Step2: /* Atomic formula. */
       ATOMFWR(V,F); goto Return;

Step3: /* Disjunction/Conjunction. */
       Fp = RED(F);
       if (LENGTH(Fp) == 1) { QFFWR(V,FIRST(Fp)); goto Return; }
       SWRITE("[ "); ADV(Fp,&F1,&Fp); QFFWR(V,F1);
       while (Fp != NIL)
         { ADV(Fp,&F1,&Fp); SWRITE(" "); LGOPWR(T); SWRITE(" "); QFFWR(V,F1); }
       SWRITE(" ]");
       goto Return;

Step4: /* Negation. */
       F1 = SECOND(F);
       SWRITE("[ "); LGOPWR(T); SWRITE(" "); QFFWR(V,F1); SWRITE(" ]");
       goto Return;

Step5: /* $\Rightarrow$,$\Leftarrow$, $\Leftrightarrow$. */
       F1 = SECOND(F); F2 = THIRD(F);
       SWRITE("[ "); QFFWR(V,F1); SWRITE(" "); LGOPWR(T);
       SWRITE(" "); QFFWR(V,F2); SWRITE(" ]");
       goto Return;

Return: /* Prepare for return. */
       return;
}
