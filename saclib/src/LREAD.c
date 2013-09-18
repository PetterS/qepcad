/*======================================================================
                      L <- LREAD()

List read.

Outputs
  L : a list.

Side effects
  The list L is read from the input stream.  Any preceding 
  blanks are skipped.
======================================================================*/
#include "saclib.h"

Word LREAD()
{
       Word C,L,L1;
       /* hide C; */

Step1: /* Read list elements. */
       L = NIL;
       C = CREADB();
       if (C != '(')
         goto Step2;
       do
         {
         C = CREADB();
         if (C == ')')
           {
           L = INV(L);
           goto Return;
           }
         else
           if (C == '(')
             {
             BKSP();
             L1 = LREAD();
             }
           else
             if (C == '+' || C == '-' || DIGIT(C) == 1)
               {
               BKSP();
               L1 = AREAD();
               }
             else
               goto Step2;
         L = COMP(L1,L);
         C = CREADB();
         if (C == ')')
           BKSP();
         else
           if (C != ',')
             goto Step2;
         }
       while (1);

Step2: /* Error. */
       FAIL("LREAD","Unexpected character",C);

Return: /* Prepare for return. */
       return(L);
}
