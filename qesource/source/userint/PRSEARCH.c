/*======================================================================
                      PRSEARCH()

Process "search cells" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRSEARCH()
{
       Word T,F;

Step1: /* Get the flags. */
       T = CREADB();
       F = CREADB();

Step2: /* Check them. */
       if (T != 'y' && T != 'n')
         { SWRITE("Error PRSEARCH: 'y' or 'n' was expected.\n"); goto Step4; }
       if (F != 'y' && F != 'n')
         { SWRITE("Error PRSEARCH: 'y' or 'n' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCSEARCHTRUE = T;
       PCSEARCHFALSE = F;
       goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
