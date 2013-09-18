/*======================================================================
                      FILINE()

Flush the input stream line.
======================================================================*/
#include "qepcad.h"

void FILINE()
{
       Word C,e;
       /* hide C,e; */

Step1: /* Read up to the next newline character. */
       e = setECHO(0);
       do C = CREAD(); while (C != '\n');
       setECHO(e);

Return: /* Prepare for return. */
       return;
}
