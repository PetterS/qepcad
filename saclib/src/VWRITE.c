/*======================================================================
                      VWRITE(v)

Variable write.

Inputs
  v  : a variable name.

Side effects
  The variable name v is written to the output stream.
======================================================================*/
#include "saclib.h"

void VWRITE(v)
       Word v;
{
       Word C,vp;
       /* hide algorithm */

Step1: /* Write them out. */
       vp = v;
       while (vp != NIL)
         {
         ADV(vp,&C,&vp);
         CWRITE(C);
         }

Return: /* Prepare for return. */
       return;
}
