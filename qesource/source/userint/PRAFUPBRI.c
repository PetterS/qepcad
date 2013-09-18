/*======================================================================
                      PRAFUPBRI()

Process "afupbri" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRAFUPBRI()
{
       Word t;

Step1: /* Read in the argument. */
        do
           t = CREAD();
        while (t == ' ' || t == '\t' || t == '\n');
        if (t == 'E')
           PCAFUPBRI = 0;
        else if (t == 'H')
           PCAFUPBRI = 1;
        else
           SWRITE("Invalid argument to afupbri command!\n");

Return: /* Prepare for return. */
       return;
}
