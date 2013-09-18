/*======================================================================
<macro>               SFIRST(L,a)

Set first element.

Inputs
  L  : non empty list.
  a  : object.

Side effects
  The list L is modified by changing the first element to a.
======================================================================*/
#include "sactypes.h"
extern Word *SPACEB1;

void SFIRST(L,a)
       Word L,a;
{
  SPACEB1[L] = a;
}
