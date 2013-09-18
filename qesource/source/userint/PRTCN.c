/*======================================================================
                      PRTCN()

Process "Treat Trivial Conversion?" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRTCN()
{
       Word C;
       /* hide C; */

Step1: /* Read in the arugment. */
       C = CREADB();

Step2: /* Check for validity. */
       if (C != 'y' && C != 'n')
         { SWRITE("Error PRTCN: Either 'y' or 'n' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCTCN = C; goto Return;

Step4: /* Error exit. */
        DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
