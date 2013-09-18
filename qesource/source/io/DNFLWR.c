/*======================================================================
                      DNFLWR(N,V,F)

Disjuctive Normal Form Label Write.

\Input
   \parm{N} is a non-null list of characters used as the name of the labels.
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a disjunctive normal form with variables in $V$,
            written out in labels to the output strem.
======================================================================*/
#include "qepcad.h"

void DNFLWR(Word N, Word V, Word F)
{
       Word F1,F2,Fp,T;

Step1: /* Classify the formula F. */
       T = FIRST(F);
       if (T == OROP) goto Step3;
       if (T == ANDOP) goto Step4;
       if (T == NOTOP)   FAIL("DNFLWR","NOTOP not expected.");
       if (T == RIGHTOP) FAIL("DNFLWR","RIGHTOP not expected.");
       if (T == LEFTOP)  FAIL("DNFLWR","LEFTOP not expected.");
       if (T == EQUIOP)  FAIL("DNFLWR","EQUIPOP not expected.");

Step2: /* Atomic formula. */
       ATOMFLWR(N,V,F); goto Return;

Step3: /* Disjunction. */
       Fp = RED(F);
       if (LENGTH(Fp) == 1) { DNFLWR(N,V,FIRST(Fp)); goto Return; }
       ADV(Fp,&F1,&Fp); DNFLWR(N,V,F1);
       while (Fp != NIL)
         { ADV(Fp,&F1,&Fp); SWRITE("    "); LGOPWR(T); SWRITE("\n"); DNFLWR(N,V,F1); }
       goto Return;

Step4: /* Conjunction. */
       Fp = RED(F);
       if (LENGTH(Fp) == 1) { DNFLWR(N,V,FIRST(Fp)); goto Return; }
       ADV(Fp,&F1,&Fp); DNFLWR(N,V,F1);
       while (Fp != NIL)
         { ADV(Fp,&F1,&Fp); SWRITE(" "); LGOPWR(T); SWRITE(" "); DNFLWR(N,V,F1); }
       goto Return;

Return: /* Prepare for return. */
       return;
}
