/*======================================================================
                      PRDC()

Process "display info about the cell" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDC()
{
       Word c,t;
       /* hide t; */

Step1: /* Read in an argument. */
       CELLRDR(GVPC,&c,&t); if (t == 0) goto Return;

Step2: /* Display the cell info. */
       CELLWR(c);

Return: /* Prepare for return. */
       return;
}

