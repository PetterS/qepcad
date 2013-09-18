/*======================================================================
                      PRUDB()

Process "use databases" command.
======================================================================*/
#include "qepcad.h"

void PRUDB()
{
       Word C;
       /* hide C; */

Step1: /* Get the argument. */
       C = CREADB();

Step2: /* Check for the validity. */
       if (C != 'y' && C != 'n')
         { SWRITE("Error PRUDB: 'y' or 'n' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCDBUSE = C; goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
