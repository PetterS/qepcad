/*======================================================================
                      PRFINISH()

Process "finish" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRFINISH()
{

Step1: /* Process. */
       PCFINISH = 'y';
       PCUSEDES = 'n';

Return: /* Prepare for return. */
       return;
}
