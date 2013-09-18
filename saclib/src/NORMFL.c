/*===========================================================================
			Lp <- NORMFL(L)

Norm polynomial flatten list.

Input
  L : a list ((d_1,F_1),...,(d_s,F_s)), where the F_i are lists.

Output
  Lp: the list of elements in the F_i in the same order.
===========================================================================*/
#include "saclib.h"

Word NORMFL(L)
       Word L;
{
       Word F1,Lp,Lt,L1,f;

Step1: /* Flatten. */
       Lt = L;
       Lp = NIL;
       while (Lt != NIL) {
          ADV(Lt,&L1,&Lt);
          F1 = SECOND(L1);
          while (F1 != NIL) {
             ADV(F1,&f,&F1);
             Lp = COMP(f,Lp); } }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
