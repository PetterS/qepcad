/*======================================================================
                      VLWRITE(V)

Variable list write. 

Inputs
  V : a list of variables.

Side effects
  V is written in the output stream.
======================================================================*/
#include "saclib.h"

void VLWRITE(V)
       Word V;
{
       Word Vp,v;
       /* hide algorithm */

Step1: /* Write. */
       Vp = V;
       CWRITE('(');
       if (Vp == NIL)
         {
         CWRITE(')');
         goto Return;
         }
       else
         {
         ADV(Vp,&v,&Vp);
         VWRITE(v);
         }
       while (Vp != NIL)
         {
         CWRITE(',');
         ADV(Vp,&v,&Vp);
         VWRITE(v);
         }
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}
