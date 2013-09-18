/*======================================================================
                      n <- LENGTH(L)

Length.

Inputs
  L  : list

Outputs
  n  : the length of L.
======================================================================*/
#include "saclib.h"

Word LENGTH(L)
       Word L;
{
       Word Lp,n;
       /* hide algorithm */

Step1: /* Compute. */
       n = 0;
       Lp = L;
       while (Lp != NIL)
         {
         Lp = RED(Lp);
         n = n + 1;
         }

Return: /* Prepare for return. */
       return(n);
}
