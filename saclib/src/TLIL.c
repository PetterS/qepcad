/*=======================================================================
                         v = TLIL(a,L)

Table lookup in list.

Inputs
   a : a beta digit.
   L : a nonempty list of the form (a_1,v_1,a_2,v_2,...,a_n,v_n),
       where the a_i's are distinct beta digits and the v_i's
       are arbitrary objects.

Output
   v : if, for some i, a = a_i, then v = v_i.  Otherwise v = NIL.
=======================================================================*/
#include "saclib.h"

Word TLIL(a,L)
	BDigit a;
	Word L;
{
	Word Lp,v;

Step1: /* Search for a. */
	Lp = L;
	v = NIL;
	while (Lp != NIL) {
	   if (FIRST(Lp) == a) {
	      v = SECOND(Lp);
	      goto Return; }
	   else
	      Lp = RED2(Lp); }

Return: /* Return v. */
	return(v);
}
