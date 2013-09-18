/*=======================================================================
                            M = LFML(L)

List from multilist.

Input
   L : a multilist of beta-integers, L = (a_1,...,a_n) with 
       a_1 <= a_2 <= ... <= a_n.

Output
   M : a list M = (b_1,...,b_k) with b_1 < b_2 < ... < b_k,
       consisting of all a_i in the list L.
========================================================================*/
#include "saclib.h"

Word LFML(L)
	Word L;
{
	BDigit e,f;
	Word Lp,M;

Step1: /* L empty.*/
	if (L == NIL) {
	   M = NIL;
	   goto Return; }

Step2: /* L nonempty.*/
	ADV(L,&e,&Lp);
	M = LIST1(e);
	while (Lp != NIL) {
	   ADV(Lp,&f,&Lp);
	   if (e != f) {
	      M = COMP(f,M);
	      e = f; } }
	M = INV(M);

Return: /* Return M. */
	return(M);
}
