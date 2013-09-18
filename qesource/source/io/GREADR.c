/*======================================================================
                      GREADR(; a,t)

Gamma-integer read, robust.

\Output
  \parm{a} is a $\gamma$-integer read from the input stream.  
              Any preceding blanks are skipped.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void GREADR(Word *a_, Word *t_)
{
       Word C,S,a,t;
       /* hide algorithm */

Step1: /* Skip blanks and read sign, if any. */
       t = 1; S = 1;
       C = CREADB();
       if (C == '+')
         C = CREADB();
       else if (C == '-')
         { C = CREADB(); S = -1; }
       if (DIGIT(C) == 0)
         { SWRITE("Error GREADR: A digit was expected.\n"); goto Step3; }

Step2: /* Read digits and convert. */
       a = 0;
       do
         { a = 10 * a + C - '0'; C = CREAD(); }
       while (!(DIGIT(C) == 0));
       BKSP(); a = S * a; goto Return;

Step3: /* Error. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *a_ = a;
       *t_ = t;
       return;
}
