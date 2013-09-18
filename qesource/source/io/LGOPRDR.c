/*======================================================================
                      LGOPRDR(; p,t)

Logical Operator Read, robust.

\Output
  \parm{p} is a logical operator, read from the input stream.
  \parm{t} is 1  if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void LGOPRDR(Word *p_, Word *t_)
{
       Word C1,C2,C3,C4,p,t;
       /* hide C1,C2,C3,C4,t; */

Step1: /* Read in. */
       t = 1;
       C1 = CREADB();
       if (C1 == '/')
         {
         C2 = CREAD(); if (C2 == '\\') { p = ANDOP; goto Return; }
         SWRITE("Error LGOPRDR: '/\\' was expected.\n"); goto Step2;
         }
       else if (C1 == '\\')
         {
         C2 = CREAD(); if (C2 == '/') { p = OROP; goto Return; }
         SWRITE("Error LGOPRDR: '\\/' was expected.\n"); goto Step2;
         }
       else if (C1 == '~')
         { p = NOTOP; goto Return; }
       else if (C1 == '=')
         {
         C2 = CREAD(); C3 = CREAD();
         if (C2 == '=' && C3 == '>') { p = RIGHTOP; goto Return; }
         SWRITE("Error LGOPRDR: '==>' was expected.\n"); goto Step2;
         }
       else if (C1 == '<')
         {
         C2 = CREAD(); C3 = CREAD();
         if (C2 == '=' && C3 == '=')
           {
           C4 = CREAD();
           if (C4 == '>') { p = EQUIOP; goto Return; }
           BKSP(); p = LEFTOP; goto Return;
           }
         SWRITE("Error LGOPRDR: Either '<==' or '<==>' was expected.\n"); goto Step2;
         }
       else
         { SWRITE("Error LGOPRDR: Logic operator was expected.\n"); goto Step2; }

Step2: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *p_ = p;
       *t_ = t;
       return;
}
