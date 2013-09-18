/*======================================================================
                      PRDPF()

Process "display projection factors" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDPF()
{

Step1: /* Display. */
       IPLLDWR(GVVL,GVPF); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
