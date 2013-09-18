/*======================================================================
                      v <- VREAD()

Variable read.

Outputs
  v : a variable, is read from the input stream.  
      Any number of preceding blanks are skipped.
======================================================================*/
#include "saclib.h"

Word VREAD()
{
       Word C,v;
       /* hide C; */

Step1: /* Read. */
       C = CREADB();
       if (LETTER(C) == 0)
         FAIL("VREAD","Unexpected character",C);
       v = NIL;
       do
         {
         v = COMP(C,v);
         C = CREAD();
         }
       while (LETTER(C) || DIGIT(C));
       v = INV(v);
       BKSP();

Return: /* Prepare for return. */
       return(v);
}
