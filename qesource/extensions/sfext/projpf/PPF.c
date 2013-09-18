/*======================================================================
                      L <- PPF(P)

Parents of projection factor.

Inputs
  P  : a qepcad polynomial data structure.

Outputs
  L  : a list (l_1, ..., l_k), where l_i is a list of 1 or 2 elements.
       If l_i has one element, then P is a factor of the discriminant,
       or leading coefficient of that element.  Otherwise, P is a 
       factor of the resultant of the two elements of l_i.  If L is the
       empty list then P is an input polynomial.
======================================================================*/
#include "qepcad.h"

Word PPF(Word P)
{
      Word L,A,a,h;

Step1: /* Extract parent field. */
      A = LELTI(P,PO_PARENT);

Step3: /* Extract parents from A acording to history tag. */
      for(L = NIL; A != NIL; A = RED(A)) {
	a = FIRST(A);
	h = FIRST(a);
	switch (h) {
	case (PO_FAC) :  L = CCONC(PPF(LELTI(a,3)),L); break;
	case (PO_DIS) :  L = COMP(LIST1(LELTI(a,4)),L); break;
	case (PO_LCO) :  L = COMP(LIST1(LELTI(a,3)),L); break;
	case (PO_TCO) :  L = COMP(LIST1(LELTI(a,3)),L); break;
	case (PO_RES) :  L = COMP(LIST2(LELTI(a,4),LELTI(a,6)),L); break; } }

Return: /* Prepare to return. */
      return (L);

}

