/*======================================================================
                      INITSYS()

Initialize the qepcad system globals.
======================================================================*/
#include "qepcad.h"

void INITSYS()
{

Step1: /* Initialize Databases. */
       INITDB();

Step2: /* Initialize Program/Trace Controls. */
       INITCTRL();

Step3: /* Initialize Statistics. */
       INITSTAT();

Return: /* Prepare for return. */
       return;
}
