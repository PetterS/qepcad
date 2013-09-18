/*======================================================================
                      TAB(n)

Tabulate.
======================================================================*/
#include "qepcad.h"

void TAB(Word n)
{

Step1: /* Tab. */
       while (OPOS < n)
         CWRITE(' ');

Return: /* Prepare for return. */
       return;
}
