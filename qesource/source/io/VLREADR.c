/*======================================================================
                      VLREADR(; V,t)

Variable list read, robust.

\Output
  \parm{V} is a list of variables read from the input stream.
              Any preceding blanks are skipped.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void VLREADR(Word *V_, Word *t_)
{
       Word C,V,t,v;
       /* hide C,t; */

Step1: /* Read variables. */
       t = 1; V = NIL;
       C = CREADB();
       if (C != '(')
         { SWRITE("Error VLREADR: '(' was expected.\n"); goto Step2; }
       C = CREADB(); if (C == ')') goto Return; else BKSP();
       do
         {
         VREADR(&v,&t); if (t == 0) goto Return; V = COMP(v,V);
         C = CREADB();
         if (C == ')') { V = INV(V); goto Return; }
         if (C != ',') { SWRITE("Error VLREADR: ',' was expected.\n"); goto Step2; }
         } while (1);

Step2: /* Error. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *V_ = V;
       *t_ = t;
       return;
}
