/*======================================================================
                      PRDVL()

Process "display variable list" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDVL()
{

Step1: /* Process. */
       VLWRITE(GVVL); SWRITE("\n");

Return: /* Prepare for return. */
       return;
}
