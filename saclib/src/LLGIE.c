/*===========================================================================
			Lp <- LLGIE(L,I)

List of lists, get indexed elements.

Inputs
  L : a list ((d_1,F_1),...,(d_s,F_s)) of pairs.
  I : a list (I_1,...,I_s) of indexed lists.

Output
  Lp : a list ((d_1,G_1),...,(d_s,G_s)) where G_i is obtained
       from F_i by taking the elements indexed by I_i.
===========================================================================*/
#include "saclib.h"

Word LLGIE(L,I)
       Word L,I;
{
       Word It,I1,Lp,Lt,L1,d1;

Step1: /* Initialize. */
       Lt = L;
       It = I;
       Lp = NIL;

Step2: /* Loop. */
       while (It != NIL) {
	  ADV(It,&I1,&It);
	  ADV(Lt,&L1,&Lt);
	  FIRST2(L1,&d1,&L1);
	  L1 = LGIE(L1,I1);
	  L1 = LIST2(d1,L1);
	  Lp = COMP(L1,Lp); }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
