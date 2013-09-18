/*===========================================================================
		       t <- ISCSELT(i,C)

Test for characteristic set membership.

Inputs
  i : a BETA-digit.
  C : a characteristic set.

Output
  t : 0 or 1.  If i is an element of C, then t = 1.  Otherwise t = 0.
===========================================================================*/
#include "saclib.h"

Word ISCSELT(i,C)
       Word i,C;
{
       Word D,d,j,t;

Step1: /* Single precision. */
       if (C < BETA) {
	  if (i >= ZETA)
	     t = 0;
	  else
	     t = (C >> i) & 1;
	  goto Return; }

Step2: /* Multiprecision. */
       D = C;
       j = i;
       while (j >= ZETA && D != NIL) {
	  j = j - ZETA;
	  D = RED(D); }
       if (D == NIL)
	  t = 0;
       else {
	  d = FIRST(D);
	  t = (d >> j) & 1; }

Return: /* Prepare for return. */
       return(t);
}
