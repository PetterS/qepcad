/*======================================================================
                      PRDESIRED()

Process "desired cell condition" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDESIRED()
{
       Word C,t;
       /* hide t; */

Step1: /* Process. */
       DESIREDRDR(&C,&t);
       if (t == 1) 
         {
         PCDESIRED = C;
         PCUSEDES = 'y';
         }
       else
         SWRITE("The old condition has been kept.\n");

Return: /* Prepare for return. */
       return;
}
