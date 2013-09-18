/*===========================================================================
                              L <- LUNION(L1,L2)

List union.

Inputs
   L1,L2:  arbitrary lists.

Output
   L:  the list union of L1 and L2.
===========================================================================*/
#include "qepcad.h"

Word LUNION(Word L1, Word L2)
{
       Word L,L11,Lp1;

Step1: /* Prefix members of L1 which are not members of L2. */
       L = L2;
       Lp1 = L1;
       while (Lp1 != NIL) {
	  ADV(Lp1,&L11,&Lp1);
	  if (!MEMBER(L11,L2)) L = COMP(L11,L); }

Return: /* Prepare for return. */
       return(L);
}
