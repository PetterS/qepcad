/*======================================================================
                      PRDQFF()

Process "display quantifier-free part of the input formula" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDQFF()
{

Step1: /* Process. */
       QFFWR(GVVL,GVQFF); SWRITE("\n"); goto Return;

Return: /* Prepare for return. */
       return;
}
