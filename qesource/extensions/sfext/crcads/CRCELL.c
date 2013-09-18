/*======================================================================
                     c <- CRCELL(d)

Choose (R)CAD Cell: simple depth first search.

Inputs
  d : A qepcad CAD or a RCAD (i.e. a CAD with RCell's)

Outputs
  c : A cell from d which has no truth value assigned to it, and
      over which no cell has been raised.  If no such cell exists,
      c = NIL.  A simple depth-first search is made for such a cell.

======================================================================*/
#include "qepcad.h"
#include "newpols.h"

Word CRCELL(Word d)
{
      Word c,T;

Step1: /* If d has a truth value, no reason to raise a stack, return NIL. */
      if (LELTI(d,TRUTH) != UNDET) {
	c = NIL;
	goto Return; }

Step2: /* If d has no stack raised above it, return d. */
      if (LELTI(d,CHILD) == NIL) {
	c = d;
	goto Return; }

Step3: /* Go through the children of d and look for a cell to return. */
      c = NIL;
      for(T = LELTI(d,CHILD); T != NIL && c <= BETA; T = RED(T))
	c = CRCELL(FIRST(T));

Return: /* Return. */
      return (c);
}

