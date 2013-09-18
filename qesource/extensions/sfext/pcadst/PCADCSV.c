/*======================================================================
                     I <- PCADCSV(cs)

Pruned-CAD cell sign vector.

inputs
  cs : a cell from a pruned CAD.
  Ps : the pruned projection factor set.
outputs
  Vs : the sign vector of cs.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PCADCSV(Word cs, Word Ps)
{
      Word c,l,S,s,I,V,Vs;

Step1: /* */
      c = LELTI(cs,SC_REP);
      l = LELTI(c,LEVEL);
      if (l == 0) {
	Vs = NIL; goto Return; }
      S = LELTI(Ps,l);

      for(I = NIL; S != NIL; S = RED(S)) {
	s = FIRST(S);
	I = COMP(THIRD(LELTI(s,PO_LABEL)),I); }

      LBIBMS(I);
      I = CINV(I);

      V = FIRST(LELTI(c,SIGNPF));
      for(Vs = NIL;I != NIL; I = RED(I))
	Vs = COMP(LELTI(V,FIRST(I)),Vs);      

Return: /* Prepare to return. */
      return (Vs);
}
