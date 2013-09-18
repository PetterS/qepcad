/*======================================================================
                      Lp <- LASTCELL(L)

Last cell.

Inputs
  L  : a non-null list.

Outputs
  Lp : the list handle of the LAST cell of L.
======================================================================*/
#include "saclib.h"

Word LASTCELL(L)
       Word L;
{
       Word Lp,Lpp;
       /* hide algorithm */

Step1: /* Compute. */
       Lp = L;
       Lpp = RED(Lp);
       while (Lpp != NIL)
         {
         Lp = Lpp;
         Lpp = RED(Lp);
         }

Return: /* Prepare for return. */
       return(Lp);
}
