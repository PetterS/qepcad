/*======================================================================
                      PREQNCONST()

Process "Equational Constraint" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PREQNCONST()
{
       Word C,P_i,P_ij,i,j,t;

Step1: /* Read in arguments. */
       GREADR(&i,&t); if (t == 0) goto Return;
       C = CREADB();
       if (C != ',') { SWRITE("Error PREQNCONST: ',' was expected.\n"); goto Step5; }
       GREADR(&j,&t); if (t == 0) goto Return;

Step2: /* Legal index? */
       if (i != GVLV)
         {
         SWRITE("Now you can work with only a ");
         GWRITE(GVLV); SWRITE("--level projection factor now.\n"); goto Return;
         }

Step3: /* Confirm. */
       P_i = LELTI(GVPF,i);
       while (P_i != NIL)
	 {
         ADV(P_i,&P_ij,&P_i);
         if (THIRD(LELTI(P_ij,PO_LABEL)) == j)
           {
           SWRITE("Setting the following to be equational constraint:\n");
           PLABELWR(P_ij); SWRITE(" = "); IPDWRITE(i,LELTI(P_ij,PO_POLY),GVVL); SWRITE("\n");
           SWRITE("Do you really want to do it (y/n)?\n");
           C = CREADB();
           if (C != 'y')
             SWRITE("Ignored.\n");
           else
             {
             SLELTI(P_ij,PO_TYPE,PO_ECON);
             PCEQC  = 1;
	     }
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




