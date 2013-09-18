/*======================================================================
                      PRRSP()

Process "Treat Rational Sample Point?" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRRSP()
{
       Word C;
       /* hide C; */

Step1: /* Read in the arugment. */
       C = CREADB();

Step2: /* Check for validity. */
       if (C != 'y' && C != 'n')
         { SWRITE("Error PRRSP: Either 'y' or 'n' was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCRSP = C; goto Return;

Step4: /* Error exit. */
        DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
