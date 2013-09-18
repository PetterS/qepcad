/*======================================================================
                      PRDCS()

Process "display info about all the cells in a subtree" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDCS()
{
       Word c,t;
       /* hide t; */

Step1: /* Read in an argument. */
       CELLRDR(GVPC,&c,&t); if (t == 0) goto Return;

Step2: /* Write the info. */
       CELLSWR(c);

Return: /* Prepare for return. */
       return;
}



