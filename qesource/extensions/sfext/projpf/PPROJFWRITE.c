/*======================================================================
                      PPROJFWRITE(Ps)

Pruned projection factor write.

Inputs
  Ps : A pruned projection factor list.

Side effects
  The indices of the pruned projection factor list are printed to
  standard out.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

void PPROJFWRITE(Word Ps)
{
      Word i,P,L,I,a,b;

Step1: /* Loop over each level. */
      i = 0;
      for(P = Ps; P != NIL; P = RED(P)) {
	SWRITE("\nLevel "); IWRITE(++i); SWRITE(":\n  ");
	
Step2: /* Loop over the polynomials at this level. */
	for(L = FIRST(P); L != NIL; L = RED(L)) {
	  I = RED(LELTI(FIRST(L),PO_LABEL));
	  FIRST2(I,&a,&b);
	  SWRITE("P(");IWRITE(a);SWRITE(",");IWRITE(b);SWRITE(")  "); } }
      SWRITE("\n");

Return: /* */
      return;
}
