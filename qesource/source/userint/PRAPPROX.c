/*======================================================================
                      PRAPPROX()

Process approx-precision command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRAPPROX()
{
       Word N,t;
       /* hide C; */

Step1: /* Get the argument. */
       GREADR(&N,&t); if (t == 0) goto Return;

Step2: /* Check for the validity. */
       if (N < 0)
         { SWRITE("Error PRAPPROX: non-negative value was expected.\n"); goto Step4; }

Step3: /* Set. */
       PCNUMDEC = N; goto Return;

Step4: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
