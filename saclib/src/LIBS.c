/*======================================================================
			    LIBS(L)

List of intervals bubble sort.

Inputs
  L : a list of disjoint open or one-point logarithmic
      binary rational intervals.

Side effects
  L is sorted into non-decreasing order by the bubble-sort method.
  The list L, though not its location, is modified.
======================================================================*/
#include "saclib.h"

void LIBS(L)
       Word L;
{
       Word t,Ip,Ipp,Lp,Lpp,M,Mp;

Step1: /* Trivial case. */
       if (L == NIL)
	  goto Return;

Step2: /* General case. */
       M = NIL;
       do {
	  Lp = L;
	  Lpp = RED(Lp);
	  Ip = FIRST(Lp);
	  Mp = NIL;
	  while (Lpp != M) {
	     Ipp = FIRST(Lpp);
	     t = LBRNCOMP(FIRST(Ip),FIRST(Ipp));
	     if (t > 0 || (t == 0 && (EQUAL(FIRST(Ipp),SECOND(Ipp))))) {
		SFIRST(Lp,Ipp);
		SFIRST(Lpp,Ip);
		Mp = Lpp; }
	     else
		Ip = Ipp;
	     Lp = Lpp;
	     Lpp = RED(Lp); }
	  M = Mp; }
       while (M != NIL);

Return: /* Prepare for return. */
       return;
}
