/*======================================================================
                      CLOUT(L)

Character list out.

Inputs
  L  : a list of characters.

Side effects
  The characters in L are written to the output stream.
======================================================================*/
#include "saclib.h"

void CLOUT(L)
       Word L;
{
       Word C,Lp;
       /* hide algorithm */

Step1: /* Write them out. */
       Lp = L;
       while (Lp != NIL)
         {
         ADV(Lp,&C,&Lp);
         CWRITE(C);
         }

Return: /* Prepare for return. */
       return;
}
