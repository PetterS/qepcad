/*======================================================================
                      V <- VLREAD()

Variable list read.

Outputs
  V : a list of variables, is read from the input stream.
      Any preceding blanks are skipped.
======================================================================*/
#include "saclib.h"

Word VLREAD()
{
       Word C,V,v;
       /* hide C; */

Step1: /* Read variables. */
       V = NIL;
       C = CREADB();
       if (C != '(')
         goto Step2;
       C = CREADB();
       if (C == ')')
         goto Return;
       else
         BKSP();
       do
         {
         v = VREAD();
         V = COMP(v,V);
         C = CREADB();
         if (C == ')')
           {
           V = INV(V);
           goto Return;
           }
         else
           if (C != ',')
             goto Step2;
         }
       while (1);

Step2: /* Error. */
       FAIL("VLREAD","Unexpected character",C);

Return: /* Prepare for return. */
       return(V);
}
