/*======================================================================
                      VREADR(; v,t)

Variable read, robust.

\Output
   \parm{v} is a variable read from the input stream.
               Any number of preceding blanks are skipped.
   \parm{t} is 1 if successful,  0 otherwise.
======================================================================*/
#include "qepcad.h"

void VREADR(Word *v_, Word *t_)
{
       Word C,t,v;
       /* hide C,t; */

Step1: /* Read in a variable. */
       t = 1; v = NIL;
       C = CREADB();
       if (LETTER(C) == 0)
         { SWRITE("Error VREADR: A letter was expected.\n"); goto Step2; }
       do
         { v = COMP(C,v); C = CREAD(); }
       while (!(!LETTER(C) && !DIGIT(C)));
       v = INV(v); BKSP(); goto Return;

Step2: /* Error. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *v_ = v;
       *t_ = t;
       return;
}
