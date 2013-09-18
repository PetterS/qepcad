/*======================================================================
                      PRLDB()

Process limit entry databases command.
======================================================================*/
#include "qepcad.h"

void PRLDB()
{
       Word n,t;
       /* hide t; */

Step1: /* Get the argument. */
       GREADR(&n,&t); if (t == 0) goto Return;

Step2: /* Set the limit. */
       PCDBLIMIT = n;

Return: /* Prepare for return. */
       return;
}
