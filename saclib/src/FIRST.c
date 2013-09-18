/*======================================================================
<macro>               a <- FIRST(L)

First.

Inputs
  L  : list of length 1 or more.

Outputs
  a  : the first element of L.
======================================================================*/
#include "sactypes.h"
extern Word *SPACEB1;

Word FIRST(L)
       Word L;
{
 return(SPACEB1[L]);
}
