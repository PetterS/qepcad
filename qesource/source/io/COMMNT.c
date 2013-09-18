/*======================================================================
                      COMMNT()

Comment.
======================================================================*/
#include "qepcad.h"

Word COMMNT()
{
       Word C,n,S;

Step1: /* Read a comment. */
       S = NIL;
       C = CREADB();
       if (C != '[')
         { BKSP(); goto Return; }
       S = COMP(C,S);
       n = 1;
       while (n != 0)
         {
         C = CREAD();
         S = COMP(C,S);
         if (C == '[')
           n = n + 1;
         else if (C == ']')
           n = n - 1;
         }
       S = INV(S);

Return: /* Prepare for return. */
       return(S);
}
