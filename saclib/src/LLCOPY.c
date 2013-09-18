/*===========================================================================
			      Lp <- LLCOPY(L)

List of lists copy.

Input
  L : is a list of lists of objects.
  
Output
  Lp : is a copy of L.  The objects are not copied.
===========================================================================*/
#include "saclib.h"

Word LLCOPY(L)
       Word L;
{
       Word L_i,Lp,Lp_i,Ls;

Step1: /* Copy. */
       Lp = NIL;
       Ls = L;
       while (Ls != NIL) {
	  ADV(Ls,&L_i,&Ls);
	  Lp_i = LCOPY(L_i);
	  Lp = COMP(Lp_i,Lp); }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
