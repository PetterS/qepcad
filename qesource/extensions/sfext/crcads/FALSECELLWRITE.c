/*======================================================================
                 FALSECELLWRITE(D)

Write information for all false cells.

Inputs
  D : A CAD.

Side Effects
  Information for each false cell in the CAD is written to the output 
  stream.
======================================================================*/
#include "qepcad.h"

void QepcadCls::FALSECELLWRITE(Word D)
{
      Word T,F,c;

Step1: /* Get list of false cells, and write info for each element. */
      LISTOFCWTV(D,&T,&F);
      while (F != NIL) {
	ADV(F,&c,&F);
	CELLWR(c); }

Return: /* Prepare to return. */
      return;
}
