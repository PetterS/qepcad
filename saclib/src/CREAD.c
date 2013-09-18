/*======================================================================
                      C <- CREAD()

Character read.

Outputs
  C : the next character from the input stream.

Side effects
  LASTCHAR : set to the character C, for backspacing.
======================================================================*/
#include "saclib.h"
#include <stdio.h>

Word CREAD()
{
       Word C;
       /* hide algorithm */

Step1: /* Get the next character. */
       C = getchar();

Step2: /* Remember the character. */
       LASTCHAR = C;

Return: /* Prepare for return. */
       return(C);
}
