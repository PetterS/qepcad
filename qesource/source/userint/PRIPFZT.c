/*======================================================================
                      PRIPFZT()

Process IPFZT command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRIPFZT()
{
       Word C;
       /* hide C; */

Step1: /* Get the argument. */
       C = CREADB();

Step2: /* Check for the validity. */
       if (C != 'y' && C != 'n')
         { SWRITE("Error PRIPFZT 'y' or 'n' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCIPFZT = C; goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
