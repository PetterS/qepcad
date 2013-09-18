/*======================================================================
                      LABELWR(N,I)

Label Write.

\Input
  \parm{N} is a list of characters used as the name of the label.
  \parm{I} is a list of $\beta$--integers used as the index of
           the label.
======================================================================*/
#include "qepcad.h"

void LABELWR(Word N, Word I)
{
       Word Ip,i;

Step1: /* Write the label. */
       CLOUT(N); SWRITE("_");
       if (I == NIL) goto Return;
       Ip = I; ADV(Ip,&i,&Ip); AWRITE(i);
       while (Ip != NIL)
         { ADV(Ip,&i,&Ip); CWRITE(','); AWRITE(i); }
       goto Return;

Return: /* Prepare for return. */
       return;
}
