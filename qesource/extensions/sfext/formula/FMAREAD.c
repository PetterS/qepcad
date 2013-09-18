/*
FMAREAD

P : Projection factor set
V : The variable list
F : The formula
t : sucess flag (1 if successfull, 0 otherwise)
 */
#include "extlang.h"

void FMAREAD(Word P,Word V, Word *F_,Word *t_)
{
       Word C,C1,F,F1,F2,p,t;
       /* hide C,C1,t; */

Step1: /* Atomic formula. */
       t = 1;
       C = CREADB(); if (C == '[') goto Step2;
       BKSP(); FMAATOMREAD(P,V,&F,&t); goto Return;

Step2: /* Negation. */
       C = CREADB(); if (C != '~') { BKSP(); goto Step3; }
       FMAREAD(P,V,&F1,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']')
         { SWRITE("Error FMAREAD: ']' was expected.\n"); goto Step11; }
       F = LIST2(NOTOP,F1); goto Return;

Step3: /* Read in the first formula. */
       FMAREAD(P,V,&F1,&t); if (t == 0) goto Return;

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
         case NOTOP: { SWRITE("Error FMAREAD: '~' must not be here.\n"); goto Step11; } break;
         }

Step6: /* Conjunction. */
       F = LIST2(F1,ANDOP);
       do
        {
        FMAREAD(P,V,&F2,&t); if (t == 0) goto Return;
        F = COMP(F2,F);
        C1 = CREADB();
        if (C1 == ']') { F = INV(F); goto Return; }
        BKSP(); LGOPRDR(&p,&t); if (t == 0) goto Return;
        if (p != ANDOP)
          { SWRITE("Error FMAREAD: '/\\' was expected.\n"); goto Step11; }
        } while (1);

Step7: /* Disjunction. */
       F = LIST2(F1,OROP);
       do
        {
        FMAREAD(P,V,&F2,&t); if (t == 0) goto Return;
        F = COMP(F2,F);
        C1 = CREADB();
        if (C1 == ']') { F = INV(F); goto Return; }
        BKSP(); LGOPRDR(&p,&t); if (t == 0) goto Return;
        if (p != OROP)
          { SWRITE("Error FMAREAD: '\\/' was expected.\n"); goto Step11; }
        } while (1);

Step8: /* $\Rightarrow$. */
       FMAREAD(P,V,&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error FMAREAD: ']' was expected.\n"); goto Step11;
 }
       F = LIST3(RIGHTOP,F1,F2); goto Return;

Step9: /* $\Leftarrow$. */
       FMAREAD(P,V,&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error FMAREAD: ']' was expected.\n"); goto Step11;
 }
       F = LIST3(LEFTOP,F1,F2); goto Return;

Step10: /* $\LeftRightarrow$. */
       FMAREAD(P,V,&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error FMAREAD: ']' was expected.\n"); goto Step11;
 }
       F = LIST3(EQUIOP,F1,F2); goto Return;

Step11: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *F_ = F;
       *t_ = t;
       return;
}
