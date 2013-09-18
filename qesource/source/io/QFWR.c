/*======================================================================
                      QFWR(q)

Quantifier Write.

\Input
  \parm{q} is a quantifier,
           written to the output stream.
======================================================================*/
#include "qepcad.h"

void QFWR(Word q)
{

Step1: /* Write it. */
       if (q == UNIVER)
         SWRITE("A");
       else if (q == EXIST)
         SWRITE("E");

Return: /* Prepare for return. */
       return;
}
