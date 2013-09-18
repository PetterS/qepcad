/*======================================================================
                      FILINE()

Flush the input stream line.

Side effects
  It reads away characters from the input stream unil the first
  newline character, including the newline.
======================================================================*/
#include "saclib.h"

void FILINE()
{
       Word C;
       /* hide C; */

Step1: /* Read up to the next newline character. */
       do C = CREAD(); while (C != '\n');

Return: /* Prepare for return. */
       return;
}
