/*===========================================================================
			    LPBSD(L)

List of polynomials bubble-sort, by degrees.

Input
  L : a list of nonzero polynomials.

Side effects
  L is sorted into non-decreasing degree order by the bubble-sort method.
  The sort is stable: polynomials with the same degree appear in the
  sorted list in the same order as they do in the list before the sort.
  The list L, though not its location, is modified.
===========================================================================*/
#include "saclib.h"

void LPBSD(L)
       Word L;
{
       Word Lp,Lpp,M,Mp,ap,app,dp,dpp;

Step1: /* Trivial case. */
       if (L == NIL)
	  goto Return;

Step2: /* General case. */
       M = NIL;
       do {
	  Lp = L;
	  Lpp = RED(Lp);
	  ap = FIRST(Lp);
	  dp = PDEG(ap);
	  Mp = NIL;
	  while (Lpp != M) {
	     app = FIRST(Lpp);
	     dpp = PDEG(app);
	     if (dp > dpp) {
		SFIRST(Lp,app);
		SFIRST(Lpp,ap);
		Mp = Lpp; }
	     else {
		ap = app;
		dp = dpp; }
	     Lp = Lpp;
	     Lpp = RED(Lp); }
	  M = Mp; }
       while (M != NIL);

Return: /* Prepare for return. */
       return;
}
