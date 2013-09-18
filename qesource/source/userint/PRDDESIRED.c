/*======================================================================
                      PRDDESIRED()

Process "display the condition for desired cell" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDDESIRED()
{

Step1: /* Process. */
       SWRITE("The condition for desired cells: "); 
       DESIREDWR(PCDESIRED);
       SWRITE("\n");
       SWRITE("This condition is currenly ");
       if (PCUSEDES == 'y') 
         SWRITE("ACTIVE.\n");
       else
         SWRITE("INACTIVE.\n");

Return: /* Prepare for return. */
       return;
}
