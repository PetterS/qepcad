/*======================================================================
                      B <- OREAD()

Object read.

Outputs
  B : an object.

Side effects
  The object B is read from the input stream. 
  Any preceding blanks are skipped.
======================================================================*/
#include "saclib.h"

Word OREAD()
{
       Word B,C;
       /* hide algorithm */

Step1: /* Read list or atom. */
       C = CREADB();
       BKSP();
       if (C == '(')
         B = LREAD();
       else
         B = AREAD();

Return: /* Prepare for return. */
       return(B);
}
