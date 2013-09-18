/*======================================================================
                      ILWRITE(L)

Integer list write.  

Inputs
  L : a list of integers.  

Side effects
  The list L is written in the output stream.
======================================================================*/
#include "saclib.h"

void ILWRITE(L)
       Word L;
{
       Word Lp,a;
       /* hide algorithm */

Step1: /* Write. */
       Lp = L;
       CWRITE('(');
       while (Lp != NIL)
         {
         ADV(Lp,&a,&Lp);
         IWRITE(a);
         if (Lp != NIL)
           CWRITE(',');
         }
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}
