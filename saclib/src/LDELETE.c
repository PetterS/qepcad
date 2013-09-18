/*===========================================================================
		       Lp <- LDELETE(e,L)

List delete element.

Inputs
  e : an object.
  L : a list.

Output
  Lp : a list.  If e is in L then Lp is the list obtained by removing
       the first occurrence of e in L.  Otherwise, Lp = L.
===========================================================================*/
#include "saclib.h"

Word LDELETE(e,L)
       Word e,L;
{
       Word Lp,Lt,L1;

Step1: /* Initialize. */
       Lt = L;
       Lp = NIL;

Step2: /* Loop. */
       while (Lt != NIL) {
	  ADV(Lt,&L1,&Lt);
	  if (EQUAL(L1,e)) {
	     Lp = INV(Lp);
	     Lp = CONC(Lp,Lt);
	     goto Return; }
	  else
	     Lp = COMP(L1,Lp); }
       Lp = L;

Return: /* Prepare for return. */
       return(Lp);
}
