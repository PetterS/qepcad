/*======================================================================
                      LGOPWR(p)

Logical Operator Write.

\Input
  \parm{p} is a logical operator,
           written  out to the ouput stream.
======================================================================*/
#include "qepcad.h"

void LGOPWR(Word p)
{

Step1: /* Write it. */
       switch (p)
         {
         case ANDOP: { SWRITE("/\\"); goto Return; } break;
         case OROP: { SWRITE("\\/"); goto Return; } break;
         case NOTOP: { SWRITE("~"); goto Return; } break;
         case RIGHTOP: { SWRITE("==>"); goto Return; } break;
         case LEFTOP: { SWRITE("<=="); goto Return; } break;
         case EQUIOP: { SWRITE("<==>"); goto Return; } break;
         }

Return: /* Prepare for return. */
       return;
}
