/*======================================================================
                      VWRITE(v)

Variable Write.

\Input
  \parm{v} is a variable.
  
\Output
  The variable is written to the output stream.
======================================================================*/
#include "qepcad.h"

void VWRITE(Word v)
{

Step1: /* Write it. */
       CLOUT(v);

Return: /* Prepare for return. */
       return;
}
