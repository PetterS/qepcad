/*======================================================================
                      PRDTRACEA()

Process "display algorithm trace settings" command.
======================================================================*/
#include "qepcad.h"

void PRDTRACEA()
{

Step1: /* Process. */
       SWRITE("----------------------------------------------------------------\n");
       TRMODEWR(TCPROJ); TAB(10); SWRITE(":PROJ,   Projection Operation.\n");
       SWRITE("----------------------------------------------------------------\n");
       goto Return;

Return: /* Prepare for return. */
       return;
}
