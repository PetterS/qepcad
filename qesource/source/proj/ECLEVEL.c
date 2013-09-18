/*===========================================================================
                         k <- ECLEVEL(L)

Equational constraint level.

Input
  L : a list of the labels of projection factors whose product
      constitutes an equational constraint.

Output
  k : the level of the equational constraint.
===========================================================================*/
#include "qepcad.h"

Word ECLEVEL(Word L)
{
       Word k,Lp,L1;

Step1: /* Initialize. */
       Lp = L;
       k = 0;

Step2: /* Loop. */
       while (L != NIL) {
	  ADV(L,&L1,&L);
	  k = MAX(k,LBLLEVEL(L1)); }

Return: /* Prepare for return. */
       return(k);
}
