/*======================================================================
                      PRDPJ()

Process "display projection polynomials" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDPJ()
{

Step1: /* Display. */
       IPLLDWR(GVVL,GVPJ); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
