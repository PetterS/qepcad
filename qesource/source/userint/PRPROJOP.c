/*======================================================================
                      PRPROJOP()

Process "projection operator" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRPROJOP()
{
       Word C,p;
       /* hide p; */

Step1: /* Read in an argument. */
       C = NIL;
       p = CREADB();
       if (p != '(') { SWRITE("Error PRPROJOP: '(' was expected.\n"); goto Step3; }
       p = CREADB(); if (p == ')') goto Step2; else BKSP();
       do
         {
         p = CREADB();
         if (p != 'c' && p != 'm' && p != 'h' && p != 'l' && p != 'p' && p != 'x')
           { SWRITE("Error PRPROJOP: One of 'c', 'm', 'h', 'l', or 'x' was expected.\n");
            goto Step3; }
         C = COMP(p,C);
         p = CREADB();
         if (p == ')') { C = INV(C); goto Step2; }
         if (p != ',') { SWRITE("Error PRPROJOP: ',' was expected.\n"); goto Step3; }
         } while (1);

Step2: /* Set. */
       if (LENGTH(C) != GVNV - 1)
         {
         SWRITE("Error PRPROJOP: ");
         GWRITE(GVNV - 1);
         SWRITE(" operators were expected.\n");
         goto Step3;
         }
       PCPROJOP = C; goto Return;

Step3: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
