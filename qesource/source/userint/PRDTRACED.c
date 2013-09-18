/*======================================================================
                      PRDTRACED()

Process "display data trace settings" command.
======================================================================*/
#include "qepcad.h"

void PRDTRACED()
{

Step1: /* Process. */
       SWRITE("----------------------------------------------------------------\n");
       CWRITE(TCPC);      TAB(5); SWRITE(":PC       Partial CAD.\n");
       CWRITE(TCPROD);    TAB(5); SWRITE(":PROD     Product.\n");
       CWRITE(TCPIMP);    TAB(5); SWRITE(":PIMP     Prime Implicant.\n");
       CWRITE(TCPIMPTBL); TAB(5); SWRITE(":PIMPTBL  Prime Implicant Table.\n");
       CWRITE(TCEPIMP);   TAB(5); SWRITE(":EPIMP    Essential Prime Implicant.\n");
       CWRITE(TCSTAT);    TAB(5); SWRITE(":STAT     Statistics at the end.\n");
       CWRITE(TCDSTAT);   TAB(5); SWRITE(":DSTAT    Dissertation statistics at the end.\n");
       SWRITE("----------------------------------------------------------------\n");
       goto Return;

Return: /* Prepare for return. */
       return;
}
