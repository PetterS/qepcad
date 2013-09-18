/*======================================================================
                      PRTRACEA()

Process "trace algorithm" command.
======================================================================*/
#include "qepcad.h"

void PRTRACEA()
{
       Word A,A1,C,E,M,X;
       /* hide C; */

Step1: /* Get the algorithms names. */
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

Step2: /* Get the entry time trace mode. */
       E = NIL;
       C = CREADB();
       while (C != ';')
         {
         if (C != 'n' && C != 'i')
             { SWRITE("Error PRTRACEA: 'n' or 'i' was expected.\n"); goto Step7; }
         E = COMP(C,E);
         C = CREADB();
         }
       E = INV(E);

Step3: /* Get the exit time trace mode. */
       X = NIL;
       C = CREADB();
       while (C != '.')
         {
         if (C != 'n' && C != 'i' && C != 'o' && C != 't')
             { SWRITE("Error PRTRACEA: one of 'n', 'i', 'o', and 't' was expected.\n"); goto Step7; }
         X = COMP(C,X);
         C = CREADB();
         }
       X = INV(X);

Step4: /* Form the trace mode. */
       if (E == NIL && X == NIL)
         M = NIL;
       else
         M = LIST2(E,X);

Step5: /* Setting the trace mode for all the algorithms. */
       if (A != NIL) goto Step6;
       TCPROJ = M;
       goto Return;

Step6: /* Settting the trace mode for only the specified algorithms. */
       while (A != NIL)
         {
         ADV(A,&A1,&A);
         if (EQUAL(A1,LFS("PROJ"))) TCPROJ = M;
         else { SWRITE("Warning PRTRACEA: "); CLOUT(A1); SWRITE(" cannot be traced and ignored.\n"); }
         }
       goto Return;

Step7: /* Error exit. */
       DIELOC(); goto Return;

Return: /* Prepare for return. */
       return;
}
