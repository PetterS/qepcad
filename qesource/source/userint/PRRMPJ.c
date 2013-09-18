/*======================================================================
                      PRRMPJ()

Process "Remove Projection Polynomials" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRRMPJ()
{
       Word C,J_i,J_ij,i,j,t;
       /* hide C,t; */

Step1: /* Read in arguments. */
       GREADR(&i,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ',') { SWRITE("Error PRRMPJ: ',' was expected.\n"); goto Step5; }
       GREADR(&j,&t); if (t == 0) goto Return;

Step2: /* Legal index? */
       if (i != GVLV - 1)
         {
         SWRITE("Now you can remove only a ");
         GWRITE(GVLV - 1); SWRITE("-variate projection polynomial.\n"); goto Return;
         }

Step3: /* Confirm. */
       J_i = LELTI(GVPJ,i);
       while (J_i != NIL)
         {
         ADV(J_i,&J_ij,&J_i);
         if (THIRD(LELTI(J_ij,PO_LABEL)) == j)
	   {
           SWRITE("You requested to remove the following projection polynomial:\n");
           PLABELWR(J_ij); SWRITE(" = "); IPDWRITE(i,LELTI(J_ij,PO_POLY),GVVL); SWRITE("\n");
           SWRITE("Do you really want to remove it (y/n)?\n");
           C = CREADB();
           if (C != 'y') 
             SWRITE("Not removed.\n");
           else
             SLELTI(J_ij,PO_STATUS,PO_REMOVE);
           goto Return;
           }
         }

Step4: /* Not found. */
       SWRITE("No such polynomial exists.\n"); 
       goto Return;

Step5: /* Error Exit. */
       DIELOC();

Return: /* Prepare for return. */
       return;
}
