/*======================================================================
                      PRIGS()

Process Implication Generation Strategy command.
======================================================================*/
#include "qepcad.h"

void PRIGS()
{
       Word C;
       /* hide C; */

Step1: /* Read in the strategy. */
       C = CREADB();

Step2: /* Check for validity. */
       if (C != 'l' && C != 'r')
         { SWRITE("Error PRIGS: Either 'l' or 'r' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCIGS = C; goto Return;

Step4: /* Error exit. */
        DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
