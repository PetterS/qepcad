/*======================================================================
                      DNFWR(V,F)

Disjunctive Normal Form Write.

\Input
   \parm{V} is a non-null list of distinct variables.
   \parm{F} is a disjunctive normal form with variables in $V$,
            written out to the output strem
======================================================================*/
#include "qepcad.h"

void DNFWR(Word V, Word F)
{
       Word F1,F2,Fp,T;

Step1: /* Classify the formula F. */
       T = FIRST(F);
       if (T == OROP) goto Step3;
       if (T == ANDOP) goto Step4;
       if (T == NOTOP)   FAIL("DNFWR","NOTOP not expected.");
       if (T == RIGHTOP) FAIL("DNFWR","RIGHTOP not expected.");
       if (T == LEFTOP)  FAIL("DNFWR","LEFTOP not expected."); 
       if (T == EQUIOP)  FAIL("DNFWR","EQUIPOP not expected."); 

Step2: /* Atomic formula. */
       ATOMFWR(V,F); goto Return;

Step3: /* Disjunction. */
       Fp = RED(F);
       if (LENGTH(Fp) == 1) { DNFWR(V,FIRST(Fp)); goto Return; }
       ADV(Fp,&F1,&Fp); DNFWR(V,F1);
       while (Fp != NIL)
         { ADV(Fp,&F1,&Fp); SWRITE("    "); LGOPWR(T); SWRITE("\n"); DNFWR(V,F1); }
       goto Return;

Step4: /* Conjunction. */
       Fp = RED(F);
       if (LENGTH(Fp) == 1) { DNFWR(V,FIRST(Fp)); goto Return; }
       ADV(Fp,&F1,&Fp); DNFWR(V,F1);
       while (Fp != NIL)
         { ADV(Fp,&F1,&Fp); SWRITE(" "); LGOPWR(T); SWRITE(" "); DNFWR(V,F1); }

Return: /* Prepare for return. */
       return;
}
