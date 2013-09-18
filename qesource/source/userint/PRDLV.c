/*======================================================================
                      PRDLV()

Process  "display the current level" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDLV()
{

Step1: /* Process. */
       GWRITE(GVLV); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
