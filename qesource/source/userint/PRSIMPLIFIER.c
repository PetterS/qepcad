/*======================================================================
                      PRSIMPLIFIER()

Process simplifier command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRSIMPLIFIER()
{
       Word C;
       /* hide C; */

Step1: /* Get the argument. */
       C = CREADB();

Step2: /* Check for the validity. */
       if (C != 'b' && C != 't')
         { SWRITE("Error PRSIMPLIFIER: 'b' or 't' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCSIMPLIFY = C; goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
