/*======================================================================
                      SIGNWR(s)

Sign write.

\Input
  \parm{s} is a sign to be written to the output stream.
======================================================================*/
#include "qepcad.h"

void SIGNWR(Word s)
{

Step1: /* Write. */
       switch (s)
         {
         case POSITIVE: CWRITE('+'); break;
         case ZERO: CWRITE('0'); break;
         case NEGATIVE: CWRITE('-'); break;
         case UNDET: CWRITE('?'); break;
         }

Return: /* Prepare for return. */
       return;
}
