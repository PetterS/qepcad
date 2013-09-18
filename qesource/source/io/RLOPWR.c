/*======================================================================
                      RLOPWR(p)

Relational Operator Write.

\Input
  \parm{p} is a relational operator,
           written out to the ouput stream.
======================================================================*/
#include "qepcad.h"

void RLOPWR(Word p)
{

Step1: /* Write it. */
       switch (p)
         {
         case EQOP: { SWRITE("="); goto Return; } break;
         case NEOP: { SWRITE("/="); goto Return; } break;
         case LTOP: { SWRITE("<"); goto Return; } break;
         case LEOP: { SWRITE("<="); goto Return; } break;
         case GTOP: { SWRITE(">"); goto Return; } break;
         case GEOP: { SWRITE(">="); goto Return; } break;
         }

Return: /* Prepare for return. */
       return;
}
