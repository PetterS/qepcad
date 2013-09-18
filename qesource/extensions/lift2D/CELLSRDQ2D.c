/*
  Cell simple root of discriminant Query 2D
  Takes a QEPCAD Cell c and returns TRUE if that cell is a zero only
  of projection factors that derive from 2-level polynomials as mulitplicity
  one factors of discriminants.
  If TRUE is returned, Q is set to a list of all projection factors the
  discriminants of which have a zero of multiplicity one in c.
 */
#include "lift2d.h"

Word CELLSRDQ2D(Word c, Word P, Word *Q_) /* c a cell, P a projection factor list */
{
  Word t,L,p,Q;
  if (LELTI(c,LEVEL) != 1)
    t = FALSE;
  else {
    t = TRUE;
    for(L = LELTI(c,MULSUB); L != NIL; L = RED(L)) {
      p = FIRST(FIRST(L));
      p = LELTI(LELTI(P,1),p);
      if (PFSRDQ2D(p,&Q) == FALSE) {
	t = FALSE;
	break; } }
  }

  *Q_ = Q;
  return t;
}
