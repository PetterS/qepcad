/*======================================================================
                      PRDNQFF()

Process "display normalized quantifier-free part of the input formula"
command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDNQFF()
{

Step1: /* Process. */
       QFFWR(GVVL,GVNQFF); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
