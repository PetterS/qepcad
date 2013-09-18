/*======================================================================
<macro>               SRED(L,Lp)

Set reductum.

Inputs
  L   : non empty list.
  Lp  : list.

Side effects
  The list L is modified by changing its reductum to Lp.
======================================================================*/
#include "sactypes.h"
extern Word *SPACEB;

void SRED(L,Lp)
       Word L,Lp;
{
  SPACEB[L] = Lp;
}
