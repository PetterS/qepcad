/*======================================================================
                      LWRITE(L)

List write.

Inputs
  L : a list.

Side effects
  The input list L is written in the output stream.
======================================================================*/
#include "saclib.h"

void LWRITE(L)
       Word L;
{
       Word L1,Lp;

Step1: /* Initialize. */
       CWRITE('(');
       Lp = L;

Step2: /* Write list elements. */
       while (Lp != NIL)
         {
         ADV(Lp,&L1,&Lp);
         if (L1 < BETA)
           AWRITE(L1);
         else
           LWRITE(L1);
         if (Lp != BETA)
           CWRITE(',');
         }

Step3: /* Finish. */
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}
