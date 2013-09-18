/*===========================================================================
		       Lp <- NORMRL(F,L)

Norm polynomial regroup list.

Inputs
  F : a list ((d_1,F_1),...,(d_s,F_s)) of pairs, where the F_i are lists.
  L : a list with as many elements as the total number of
      elements in the lists F_i.

Output
  Lp : a list ((d_1,L_1),...,(d_s,L_s)), where L_1 contains the
       first card(F_1) elements in L, and so on.
===========================================================================*/
#include "saclib.h"

Word NORMRL(F,L)
       Word F,L;
{
       Word Ft,F1,Lp,Lt,L1,d1,f,i,k;

Step1: /* Regroup the elements of L. */
       Ft = F;
       Lt = L;
       Lp = NIL;
       while (Ft != NIL) {
          ADV(Ft,&F1,&Ft);
          FIRST2(F1,&d1,&F1);
          L1 = NIL;
          k = LENGTH(F1);
          for (i = 1; i <= k; i++) {
             ADV(Lt,&f,&Lt);
             L1 = COMP(f,L1); }
          L1 = LIST2(d1,INV(L1));
          Lp = COMP(L1,Lp); }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
