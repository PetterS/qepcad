/*===========================================================================
			      Lp <- LCOPY(L)

List copy.

Input
  L : a list of objects.
  
Output
  Lp : a list of objects.  Lp is a copy of L.  The objects are not copied.
===========================================================================*/
#include "saclib.h"

Word LCOPY(L)
       Word L;
{
       Word L_i,Lp,Ls;

Step1: /* Copy. */
       Lp = NIL;
       Ls = L;
       while (Ls != NIL) {
	  ADV(Ls,&L_i,&Ls);
	  Lp = COMP(L_i,Lp); }
       Lp = INV(Lp);
       goto Return;

Return: /* Prepare for return. */
       return(Lp);
}
