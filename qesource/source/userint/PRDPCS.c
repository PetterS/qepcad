/*======================================================================
                      PRDPCS()

Process "display the current partial CAD with signature" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDPCS()
{
       Word c,t;
       /* hide t; */

Step1: /* Read in an argument. */
       CELLRDR(GVPC,&c,&t); if (t == 0) goto Return;

Step2: /* Process. */
       SWRITE("--------------------------------------------\n");
       SWRITE("The Partial CAD over "); LWRITE(LELTI(c,INDX)); SWRITE("\n\n");
       PCADSWR(c);
       SWRITE("--------------------------------------------\n");
       goto Return;

Return: /* Prepare for return. */
       return;
}
