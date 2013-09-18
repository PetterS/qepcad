/*======================================================================
                      DESIREDWR(C)

Desired cell condition write.
======================================================================*/
#include "qepcad.h"

void DESIREDWR(Word C)
{
       Word C1,C2,Cp,T,V1,V2;
       /* hide T,V1,V2; */

Step1: /* Classify the condition C. */
       T = FIRST(C);
       if (T == OROP)    goto Step3;
       if (T == ANDOP)   goto Step3;
       if (T == NOTOP)   goto Step4;
       if (T == RIGHTOP) goto Step5;
       if (T == LEFTOP)  goto Step5;
       if (T == EQUIOP)  goto Step5;

Step2: /* Atomic condition. */
       V1 = SECOND(C);
       V2 = THIRD(C);
       if (V1 < 0 )
          CATTRNWR(V1);
       else 
          GWRITE(V1);
       SWRITE(" "); RLOPWR(T); SWRITE(" ");
       if (V2 < 0 )
          CATTRNWR(V2);
       else 
          GWRITE(V2);  
       goto Return;

Step3: /* Disjunction/Conjunction. */
       Cp = RED(C);
       if (LENGTH(Cp) == 1) { DESIREDWR(FIRST(Cp)); goto Return; }
       SWRITE("[ "); ADV(Cp,&C1,&Cp); DESIREDWR(C1);
       while (Cp != NIL)
         { ADV(Cp,&C1,&Cp); SWRITE(" "); LGOPWR(T); SWRITE(" "); DESIREDWR(C1); }
       SWRITE(" ]");
       goto Return;

Step4: /* Negation. */
       C1 = SECOND(C);
       SWRITE("[ "); LGOPWR(T); SWRITE(" "); DESIREDWR(C1); SWRITE(" ]");
       goto Return;

Step5: /* $\Rightarrow$,$\Leftarrow$, $\Leftrightarrow$. */
       C1 = SECOND(C); C2 = THIRD(C);
       SWRITE("[ "); DESIREDWR(C1); SWRITE(" "); LGOPWR(T);
       SWRITE(" ");  DESIREDWR(C2); SWRITE(" ]");

Return: /* Prepare for return. */
       return;
}
