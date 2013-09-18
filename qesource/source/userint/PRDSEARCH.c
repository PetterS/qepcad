/*======================================================================
                      PRDSEARCH()

Process "display the search cells" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDSEARCH()
{

Step1: /* Process. */
       SWRITE("Search for true cell?                 : ");
       CWRITE(PCSEARCHTRUE); SWRITE("\n");
       SWRITE("Search for false cell?                : ");
       CWRITE(PCSEARCHFALSE); SWRITE("\n");

Return: /* Prepare for return. */
       return;
}
