/*===========================================================================
			      Lp <- RMDUP(L)

Remove duplicate elements from a list.

Input
  L : a list.

Output
  Lp : the list obtained by removing duplicate elements from L.
       The relative positions of the elements in L are preserved in Lp.
===========================================================================*/
#include "saclib.h"

Word RMDUP(L)
       Word L;
{
       Word L1,Lp,Ls;

Step1: /* Remove. */
       Lp = NIL;
       Ls = L;
       while (Ls != NIL) {
	  ADV(Ls,&L1,&Ls);
	  if (!MEMBER(L1,Lp))
	     Lp = COMP(L1,Lp); }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
