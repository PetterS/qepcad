/*======================================================================
                      PRTRACED()

Process "trace data" command.
======================================================================*/
#include "qepcad.h"

void PRTRACED()
{
       Word A,A1,C,M;
       /* hide C,M; */

Step1: /* Get the data names. */
       A = NIL;
       C = CREADB();
       while (C != ';')
         {
         BKSP();
         A1 = GETWORD();
         A = COMP(A1,A);
         C = CREADB();
         }
       A = INV(A);

Step2: /* Get the trace mode. */
       M = CREADB();
       if (M != 'y' && M != 'n')
         { SWRITE("Error PRTRACED: 'y' or 'n' was expected.\n"); goto Step5; }

Step3: /* Setting the trace mode for all the data. */
       if (A != NIL) goto Step4;
       TCPC = M;
       TCPROD = M;
       TCPIMP = M;
       TCPIMPTBL = M;
       TCEPIMP = M;
       TCSTAT = M;
       TCDSTAT = M;
       goto Return;

Step4: /* Settting the trace mode for only the specified data. */
       while (A != NIL)
         {
         ADV(A,&A1,&A);
         if (EQUAL(A1,LFS("PC"))) TCPC = M;
         else if (EQUAL(A1,LFS("PROD"))) TCPROD = M;
         else if (EQUAL(A1,LFS("PIMP"))) TCPIMP = M;
         else if (EQUAL(A1,LFS("PIMPTBL"))) TCPIMPTBL = M;
         else if (EQUAL(A1,LFS("EPIMP"))) TCEPIMP = M;
         else if (EQUAL(A1,LFS("STAT"))) TCSTAT = M;
         else if (EQUAL(A1,LFS("DSTAT"))) TCDSTAT = M;
         else { SWRITE("Warning PRTRACED: "); CLOUT(A1); SWRITE(" cannot be traced and ignored.\n"); }
         }
       goto Return;

Step5: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
