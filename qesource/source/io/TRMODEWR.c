/*======================================================================
                      TRMODEWR(M)

Trace Mode Write.

\Input
  \parm{M} is a trace mode which will be written out to the output stream.
======================================================================*/
#include "qepcad.h"

void TRMODEWR(Word M)
{

Step1: /* Write. */
       if (M == NIL) SWRITE("-");
       else { CLOUT(FIRST(M)); SWRITE(" "); CLOUT(SECOND(M)); }
       goto Return;

Return: /* Prepare for return. */
       return;
}
