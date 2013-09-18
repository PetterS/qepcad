/*==========================================================================
                          Lp <- LGIE(L,I)

List, get indexed elements.

Inputs
  L : a list (A_0, A_1, ..., A_n).
  I : a list (i_1, ..., i_k) of distinct BETA-digits such that
      0 <= i_1 < ... < i_k <= n.

Output
  Lp : the list (A_{i_1}, ..., A_{i_k}).
==========================================================================*/
#include "saclib.h"

Word LGIE(L,I)
       Word L,I;
{
       Word Lp,Ls,L1,Is,i1,i;

Step1: /* Initialize. */
       Ls = L;
       Is = I;
       Lp = NIL;
       i = -1;

Step2: /* Extract the elements. */
       while (Is != NIL) {
	  ADV(Is,&i1,&Is);
	  while (i != i1) {
	     ADV(Ls,&L1,&Ls);
	     i++; }
	  Lp = COMP(L1,Lp); }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
