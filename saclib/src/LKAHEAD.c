/*===========================================================================
			       C <- LKAHEAD()

Character lookahead.

Outputs
  C : the next non-white-space character from the input stream.

Side effects 
  The next non-whitespace character is read and then put
  back onto the input stream.
===========================================================================*/
#include "saclib.h" 
#include <stdio.h>

Word LKAHEAD()
{
       Word C;

Step1: /* Get the next character. */
       C = CREADB();

Step2: /* backspace */
       BKSP();

Return: /* Prepare for return */
       return(C);
}
