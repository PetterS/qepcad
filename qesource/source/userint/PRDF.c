/*======================================================================
                      PRDF()

Process "display formula" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDF()
{

Step1: /* Process. */
       FWRITE(GVVL,GVF); SWRITE("\n");

Return: /* Prepare for return. */
       return;
}
