/*======================================================================
                      BKSP()

Backspace.  

Side effects
  The last character read is put back onto the input stream.
======================================================================*/
#include "saclib.h"
#include <stdio.h>

void BKSP()
{
       /* hide algorithm */

Step1: /* Put back. */
       ungetc(LASTCHAR,stdin);

Return: /* Prepare for return. */
       return;
}
