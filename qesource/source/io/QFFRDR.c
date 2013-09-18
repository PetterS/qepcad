/*======================================================================
                      QFFRDR(V; F,t)

Quantifier-free formula read, robust.
  
\Input
  \parm{V} is a non-null list of variables. 

\Output  
  \parm{F} is a quantifier-free formula whose variables 
           all occur in $V$, read from the input stream.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void QFFRDR(Word V, Word *F_, Word *t_)
{
       Word C,C1,F,F1,F2,p,t;
       /* hide C,C1,t; */

Step1: /* Atomic formula. */
       t = 1;
       C = CREADB(); if (C == '[') goto Step2;
       BKSP(); ATOMFRDR(V,&F,&t); goto Return;

Step2: /* Negation. */
       C = CREADB(); if (C != '~') { BKSP(); goto Step3; }
       QFFRDR(V,&F1,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']')
         { SWRITE("Error QFFRDR: ']' was expected.\n"); goto Step11; }
       F = LIST2(NOTOP,F1); goto Return;

Step3: /* Read in the first formula. */
       QFFRDR(V,&F1,&t); if (t == 0) goto Return;

Step4: /* Redundant square brakets. */
       C = CREADB(); if (C == ']') { F = F1; goto Return; }
       BKSP();

Step5: /* Indentify the logical operator. */
       LGOPRDR(&p,&t); if (t == 0) goto Return;
       switch (p)
         {
         case ANDOP: goto Step6; break;
         case OROP: goto Step7; break;
         case RIGHTOP: goto Step8; break;
         case LEFTOP: goto Step9; break;
         case EQUIOP: goto Step10; break;
         case NOTOP: { SWRITE("Error QFFRDR: '~' must not be here.\n"); goto Step11; } break;
         }

Step6: /* Conjunction. */
       F = LIST2(F1,ANDOP);
       do
        {
        QFFRDR(V,&F2,&t); if (t == 0) goto Return;
        F = COMP(F2,F);
        C1 = CREADB();
        if (C1 == ']') { F = INV(F); goto Return; }
        BKSP(); LGOPRDR(&p,&t); if (t == 0) goto Return;
        if (p != ANDOP)
          { SWRITE("Error QFFRDR: '/\\' was expected.\n"); goto Step11; }
        } while (1);

Step7: /* Disjunction. */
       F = LIST2(F1,OROP);
       do
        {
        QFFRDR(V,&F2,&t); if (t == 0) goto Return;
        F = COMP(F2,F);
        C1 = CREADB();
        if (C1 == ']') { F = INV(F); goto Return; }
        BKSP(); LGOPRDR(&p,&t); if (t == 0) goto Return;
        if (p != OROP)
          { SWRITE("Error QFFRDR: '\\/' was expected.\n"); goto Step11; }
        } while (1);

Step8: /* $\Rightarrow$. */
       QFFRDR(V,&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error QFFRDR: ']' was expected.\n"); goto Step11; }
       F = LIST3(RIGHTOP,F1,F2); goto Return;

Step9: /* $\Leftarrow$. */
       QFFRDR(V,&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error QFFRDR: ']' was expected.\n"); goto Step11; }
       F = LIST3(LEFTOP,F1,F2); goto Return;

Step10: /* $\LeftRightarrow$. */
       QFFRDR(V,&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error QFFRDR: ']' was expected.\n"); goto Step11; }
       F = LIST3(EQUIOP,F1,F2); goto Return;

Step11: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *F_ = F;
       *t_ = t;
       return;
}
