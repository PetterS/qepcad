/*======================================================================
                      i <- VLSRCH(v,V)

Variable list search.

Inputs
  v : a variable.
  V : a list of variables (v1,...,vn), n non-negative.

Outputs
  i : integer. If v = vj for some j then i=j. Otherwise i=0.
======================================================================*/
#include "saclib.h"

Word VLSRCH(v,V)
       Word v,V;
{
       Word Vp,i,v1;
       /* hide algorithm */

Step1: /* Search. */
       Vp = V;
       i = 1;
       while (Vp != NIL)
         {
         ADV(Vp,&v1,&Vp);
         if (EQUAL(v,v1) == 1)
           goto Return;
         i = i + 1;
         }
       i = 0;

Return: /* Prepare for return. */
       return(i);
}
