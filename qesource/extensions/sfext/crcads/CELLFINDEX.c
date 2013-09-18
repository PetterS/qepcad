/*======================================================================
                      CELLFINDEX(D,I)

Cell from index.

Inputs
 D : a CAD or RCAD.
 I : an index of a cell in D.
Outputs
 Ds: the cell in D with index I.
======================================================================*/
#include "qepcad.h"

Word CELLFINDEX(Word D, Word I)
{
      Word Ds,Is,i;

Step1: /* Get cell with index I from D. */
      Ds = D; Is = I;
      while (Is != NIL) {
	ADV(Is,&i,&Is);
	Ds = LELTI(LELTI(Ds,CHILD),i); }

Return: /* Prepare to return. */
      return (Ds);
}
