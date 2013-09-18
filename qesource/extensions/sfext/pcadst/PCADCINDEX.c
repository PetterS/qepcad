/*======================================================================
                     I <- PCADCINDEX(c)

Pruned-CAD cell index.

inputs
  c : a cell from a pruned CAD.
outputs
  I : the index of c.
======================================================================*/
#include "qepcad.h"
#include "coarsecad.h"

Word PCADCINDEX(Word c)
{
      Word I,Ip,p,i;

Step1: /* Get index of parent cell, and append index of c. */
      i = LELTI(c,SC_INX);
      p = LELTI(c,SC_PAR);
      if (p == NIL)
	I = NIL;
      else {
      Ip = PCADCINDEX(p);
      I = SUFFIX(Ip,i); }

Return: /* Prepare to return. */
      return (I);
}
