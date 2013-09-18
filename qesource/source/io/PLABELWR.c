/*======================================================================
                      PLABELWR(P)

Polynomial Label Write.

\Input
  \parm{P} is a polynomial structure.
======================================================================*/
#include "qepcad.h"

void PLABELWR(Word P)
{
       Word L;

Step1: /* Write the label. */
       L = LELTI(P,PO_LABEL);
       LABELWR(FIRST(L),RED(L));

Return: /* Prepare for return. */
       return;
}
