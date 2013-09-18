/*======================================================================
                      PRRMPF()

Process "Remove Projection Factor" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRRMPF()
{
       Word A_i,C,P_i,P_ij,i,j,t;
       /* hide C,t; */

Step1: /* Read in arguments. */
       GREADR(&i,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ',') { SWRITE("Error PRRMPF: ',' was expected.\n"); goto Step5; }
       GREADR(&j,&t); if (t == 0) goto Return;

Step2: /* Legal index? */
       if (i != GVLV)
         {
         SWRITE("Now you can remove only a ");
         GWRITE(GVLV); SWRITE("--level projection factor.\n"); goto Return;
         }

Step3: /* Confirm. */
       P_i = LELTI(GVPF,i);
       while (P_i != NIL)
	 {
         ADV(P_i,&P_ij,&P_i);
         if (THIRD(LELTI(P_ij,PO_LABEL)) == j)
           {
           if (LELTI(P_ij,PO_PARENT) != NIL)
             {
             SWRITE("You requested to remove the following projection factor:\n");
             PLABELWR(P_ij); SWRITE(" = "); IPDWRITE(i,LELTI(P_ij,PO_POLY),GVVL); SWRITE("\n");
             SWRITE("Do you really want to remove it (y/n)?\n");
             C = CREADB();
             if (C != 'y')
               SWRITE("Not removed.\n");
             else
               SLELTI(P_ij,PO_STATUS,PO_REMOVE);
             }
           else
             SWRITE("The input polynomnial cannot be removed.\n"); 
           goto Return; 
           }
         }

Step4: /* Note found. */
       SWRITE("No such polynomial exists.\n");
       goto Return;

Step5: /* Error Exit. */
       DIELOC();

Return: /* Prepare for return. */
       return;
}




