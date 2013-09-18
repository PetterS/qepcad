/*======================================================================
                      RLOPRDR(; p,t)

Relational Operator Read, robust.

\Ouput
  \parm{p} is a relational operator, read in from the input stream.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void RLOPRDR(Word *p_, Word *t_)
{
       Word C,D,p,t;
       /* hide C,D,t; */

Step1: /* Read in. */
       t = 1;
       C = CREADB(); D = CREAD();
       if (C == '<' && D == '=') { p = LEOP; }
       else if (C == '<') { p = LTOP; BKSP(); }
       else if (C == '>' && D == '=') { p = GEOP; }
       else if (C == '>') { p = GTOP; BKSP(); }
       else if (C == '=') { p = EQOP; BKSP(); }
       else if (C == '/' && D == '=') { p = NEOP; }
       else
         {
         SWRITE("Error RLOPRDR: A relational operator was expected.\n");
         goto Step2;
         }
       goto Return;

Step2: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *p_ = p;
       *t_ = t;
       return;
}
