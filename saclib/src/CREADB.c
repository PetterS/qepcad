/*======================================================================
                      C <- CREADB()

Character read.

Outputs
  C : the next non-white-space character from the input stream.

Remarks
  White space: space, newline, tab, formfeed, carriage return, and vertical tab.
  See ANSI C Appendix A: Page 191.
======================================================================*/
#include "saclib.h"
#include <ctype.h>

Word CREADB()
{
       Word C;
       /* hide C; */

Step1: /* Get the next non-white-space character. */
       do
         C = CREAD();
       while (isspace(C));

Return: /* Prepare for return. */
       return(C);
}
