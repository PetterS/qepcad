/*======================================================================
                      PRQUIT()

Process "quit" Command.
======================================================================*/
#include "qepcad.h"

void PRQUIT()
{

Step1: /* Process. */
       SWRITE("Quitting the QEPCAD system... Bye!\n");
       ENDQEPCAD();
       ENDSACLIB(SAC_FREEMEM);
       exit(0);

Return: /* Prepare for return. */
       return;
}
