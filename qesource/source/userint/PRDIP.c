/*======================================================================
                      PRDIP()

Process "display input polynomials" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDIP()
{

Step1: /* Display. */
       IPLLDWR(GVVL,GVNIP); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
