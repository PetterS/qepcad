/*===========================================================================
                         t <- LCM(L,M)

List Common Member.

Inputs
   L,M:  arbitrary lists.

Output
   t:    1 if L and M have a common member, 0 otherwise.
===========================================================================*/
#include "qepcad.h"

Word LCM(Word L, Word M)
{
       Word a1,Lp,t;

Step1: /* Test whether any element of L belongs to M. */
       t = 0;
       Lp = L;
       while (Lp != NIL) {
	  ADV(Lp,&a1,&Lp);
	  if (MEMBER(a1,M)) { t = 1; goto Return; } }

Return: /* Prepare for return. */
       return(t);
}
