/*======================================================================
                      TRUTHWR(t)

Truth Write.

\Input
  \parm{t} is a truth value which will be written out 
           to the output stream.
======================================================================*/
#include "qepcad.h"

void TRUTHWR(Word t)
{

Step1: /* Write. */
       switch (t)
         {
         case TRUE:  CWRITE('T'); break;
         case FALSE: CWRITE('F'); break;
         case UNDET: CWRITE('?'); break;
	 case NA:    CWRITE('*'); break;
         }

Return: /* Prepare for return. */
       return;
}
