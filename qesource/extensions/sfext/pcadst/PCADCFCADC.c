/*======================================================================
                     cs <- PCADCFCADC(c,Cs)

Pruned-CAD cell from CAD cell.

inputs
  c : A qepcad cell data structure for a cell.
  Cs: A pruned partial cad data-structure.
note: Cs and the CAD in which c resides are assumed to have identical
      structure at least up to the level of c.
outputs
  cs: The cell in Cs corresponding to c.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PCADCFCADC(Word c, Word Cs)
{
      Word cs,I;

Step1: /* Follow c's index in Cs to arrive at cs. */
      I = LELTI(c,INDX);
      for(cs = Cs; I != NIL; I = RED(I))
	cs = LELTI(LELTI(cs,SC_CDTV),FIRST(I));

Return: /* Prepare to return. */
      return (cs);
}
