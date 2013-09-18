/*======================================================================
                      SIGNLWR(x)

Sign List Write.

\Input
  \parm{x} is a list of signs to be written to the output stream.
======================================================================*/
#include "qepcad.h"

void SIGNLWR(Word x)
{
       Word s,xp;

Step1: /* $x = ()$. */
       if (x == NIL) { SWRITE("()"); goto Return; }

Step2: /* General case. */
       CWRITE('('); xp = x; ADV(xp,&s,&xp); SIGNWR(s);
       while (xp != NIL) { CWRITE(','); ADV(xp,&s,&xp); SIGNWR(s); }
       CWRITE(')');

Return: /* Prepare for return. */
       return;
}
