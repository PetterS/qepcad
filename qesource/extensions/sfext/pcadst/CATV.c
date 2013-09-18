/*======================================================================
                     t <- CATV(c)

Cell truth value.

inputs
  c : A cad cell.

outputs
  t : If c has a truth value, or if all cells in the sub-cad rooted at
      c have the same truth value, that value is returned.  Otherwise
      UNDET is returned.
======================================================================*/
#include "qepcad.h"

Word CATV(Word c)
{
      Word t,L;

Step1: /* C has a truth value. */
      t = LELTI(c,TRUTH);
      if (t != UNDET)
	goto Return;

Step2: /* See if truth value of the children is consistent. */
      L = LELTI(c,CHILD);
      if (L == NIL) goto Return; /* Not necessary. */
      t = CATV(FIRST(L));
      L = RED(L);
      while ( (L != NIL) && (t == CATV(FIRST(L))))
	L = RED(L);
      if (L != NIL)
	t = UNDET;

Return: /* Prepare to return. */
      return (t);
}
