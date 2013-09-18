/*======================================================================
                      CWRITE(C)

Character write.  

Inputs
  C : character.

Side effects
  C is written to the output stream.
======================================================================*/
#include "saclib.h"
#include <stdio.h>

void CWRITE(C)
       Word C;
{
       /* hide algorithm */

Step1: /* Write. */
       putchar(C);

Return: /* Prepare for return. */
       return;
}
