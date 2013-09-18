/*======================================================================
                      PRUSEDESIRED()

Process "use the condition for desired cells" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRUSEDESIRED()
{
       Word C;
       /* hide C; */

Step1: /* Get the argument. */
       C = CREADB();

Step2: /* Check for the validity. */
       if (C != 'y' && C != 'n')
         { SWRITE("Error PRUSEDESIRED: 'y' or 'n' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCUSEDES = C; goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
