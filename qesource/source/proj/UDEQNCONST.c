/*===========================================================================
                         UDEQNCONST(D)

Update equational constraint list.

Input
  D : the list of propagated equational constraints.

Side effects
  The global variable GVEQNCONST is updated.
===========================================================================*/
#include "qepcad.h"

void QepcadCls::UDEQNCONST(Word D)
{
       Word Dp,D1,E,k;

Step1: /* Initialize. */
       Dp = D;
       
Step2: /* Loop. */
       while (Dp != NIL) {
	  ADV(Dp,&D1,&Dp);
	  k = ECLEVEL(D1);
	  E = LELTI(GVEQNCONST,k);
	  if (E == NIL)
	     SLELTI(GVPIVOT,k,D1);
	  E = SUFFIX(E,D1);
	  SLELTI(GVEQNCONST,k,E); }

Return: /* Prepare for return. */
       return;
}
