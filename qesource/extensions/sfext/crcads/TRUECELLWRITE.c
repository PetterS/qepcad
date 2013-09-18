/*======================================================================
                 TRUECELLWRITE(D)

Write information for all true cells.

Inputs
  D : A CAD.

Side Effects
  Information for each true cell in the CAD is written to the output 
  stream.
======================================================================*/
#include "qepcad.h"

void QepcadCls::TRUECELLWRITE(Word D)
{
      Word T,F,c;

Step1: /* Get list of true cells, and write info for each element. */
      LISTOFCWTV(D,&T,&F);
      while (T != NIL) {
	ADV(T,&c,&T);
	CELLWR(c); }

Return: /* Prepare to return. */
      return;
}
