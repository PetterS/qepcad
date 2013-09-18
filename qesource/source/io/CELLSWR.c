/*======================================================================
                      CELLSWR(c)

Cells Write.

\Input
  \parm{c} is a cell whose subtree will be written out to
           the output stream.
======================================================================*/
#include "qepcad.h"

void QepcadCls::CELLSWR(Word c)
{
       Word cb,cp;

Step1: /* Write the info about c. */
       CELLWR(c);

Step2: /* Write the info about its subtrees. */
       cb = LELTI(c,CHILD);
       while (cb != NIL)
         {
         ADV(cb,&cp,&cb);
         CELLSWR(cp);
         }

Return: /* Prepare for return. */
       return;
}

