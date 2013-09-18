/*======================================================================
                      COMMNTRD()

Comment Read.
======================================================================*/
#include "qepcad.h"

void COMMNTRD()
{
       Word C,n;
       /* hide algorithm */

Step1: /* Read a comment and consume. */
       n = 0;
       C = CREADB();
       if (C != '[')
         { BKSP(); goto Return; }
       n = n + 1;
       while (n != 0)
         {
         C = CREAD();
         if (C == '[')
           n = n + 1;
         else if (C == ']')
           n = n - 1;
         }
       goto Return;

Return: /* Prepare for return. */
       return;
}
