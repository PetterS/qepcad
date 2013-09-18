/*======================================================================
<macro>               Lp <- RED(L)

Reductum 1.

Inputs
  L  : list of length 1 or more.

Outputs
  Lp  : the first reductum of L.
======================================================================*/
#include "sactypes.h"
extern Word *SPACEB;

Word RED(L)
       Word L;
{
  return(SPACEB[L]);
}
