/*======================================================================
                      DESIREDRDR(; F,t)

Desired cell condition read, robust.
  
\Output  
  \parm{F} is a condition for desired cells.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"

void DESIREDRDR(Word *F_, Word *t_)
{
       Word C,C1,F,F1,F2,R,V1,V2,p,t;
       /* hide C,C1,R,V1,V2,t; */

Step1: /* Atomic condition. */
       t = 1;
       C = CREADB(); if (C == '[') goto Step2;
       BKSP(); 
       if (DIGIT(C)) 
         V1 = AREAD();
       else
         {CATTRNRDR(&V1,&t);  if (t == 0) goto Return;}
       RLOPRDR(&R,&t); if (t == 0) goto Return;
       C = CREADB(); BKSP();
       if (DIGIT(C))
         V2 = AREAD();
       else
	 {CATTRNRDR(&V2,&t); if (t == 0) goto Return;}
       F = LIST3(R,V1,V2);
       goto Return;

Step2: /* Negation. */
       C = CREADB(); if (C != '~') { BKSP(); goto Step3; }
       DESIREDRDR(&F1,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']')
         { SWRITE("Error DESIREDRDR: ']' was expected.\n"); goto Step11; }
       F = LIST2(NOTOP,F1); goto Return;

Step3: /* Read in the first formula. */
       DESIREDRDR(&F1,&t); if (t == 0) goto Return;

Step4: /* Redundant square brakets. */
       C = CREADB(); if (C == ']') { F = F1; goto Return; }
       BKSP();

Step5: /* Indentify the logical operator. */
       LGOPRDR(&p,&t); if (t == 0) goto Return;
       switch (p)
         {
         case ANDOP:     goto Step6; break;
         case OROP:      goto Step7; break;
         case RIGHTOP:   goto Step8; break;
         case LEFTOP:    goto Step9; break;
         case EQUIOP:    goto Step10; break;
         case NOTOP:     {
                         SWRITE("Error DESIREDRDR: '~' must not be here.\n"); 
                         goto Step11; 
                         }
         }

Step6: /* Conjunction. */
       F = LIST2(F1,ANDOP);
       do
         {
         DESIREDRDR(&F2,&t); if (t == 0) goto Return;
         F = COMP(F2,F);
         C1 = CREADB();
         if (C1 == ']') { F = INV(F); goto Return; }
         BKSP(); LGOPRDR(&p,&t); if (t == 0) goto Return;
         if (p != ANDOP)
           { SWRITE("Error DESIREDRDR: '/\\' was expected.\n"); goto Step11; }
         } 
       while (1);

Step7: /* Disjunction. */
       F = LIST2(F1,OROP);
       do
         {
         DESIREDRDR(&F2,&t); if (t == 0) goto Return;
         F = COMP(F2,F);
         C1 = CREADB();
         if (C1 == ']') { F = INV(F); goto Return; }
         BKSP(); LGOPRDR(&p,&t); if (t == 0) goto Return;
         if (p != OROP)
           { SWRITE("Error DESIREDRDR: '\\/' was expected.\n"); goto Step11; }
         } 
       while (1);

Step8: /* $\Rightarrow$. */
       DESIREDRDR(&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error DESIREDRDR: ']' was expected.\n"); goto Step11; }
       F = LIST3(RIGHTOP,F1,F2); goto Return;

Step9: /* $\Leftarrow$. */
       DESIREDRDR(&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error DESIREDRDR: ']' was expected.\n"); goto Step11; }
       F = LIST3(LEFTOP,F1,F2); goto Return;

Step10: /* $\LeftRightarrow$. */
       DESIREDRDR(&F2,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ']') { SWRITE("Error DESIREDRDR: ']' was expected.\n"); goto Step11; }
       F = LIST3(EQUIOP,F1,F2); goto Return;

Step11: /* Error exit. */
       DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *F_ = F;
       *t_ = t;
       return;
}
