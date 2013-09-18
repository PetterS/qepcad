/*======================================================================
                      PRSTEP(; t)

Process "step" command.

\Output
  \parm{t} is 1 if the command is legal, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRSTEP(Word *t_)
{
       Word n,t;
       /* hide t; */

Step1: /* Read in the arugment. */
       GREADR(&n,&t); if (t == 0) goto Return;

Step2: /* Check for the validity. */
       if (n <= 0)
         { SWRITE("Error PRSTEP: A positive integer was expected.\n"); goto Step4; }

Step3: /* Process. */
       PCNSTEP = n; t = 1; goto Return;

Step4: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *t_ = t;
       return;
}
