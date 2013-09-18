/*======================================================================
<macro>               t <- ISNIL(L)

Test for empty list.

Inputs
  L  : list.

Outputs
  t  :  t = 1 if L is empty,
        t = 0 otherwise.
======================================================================*/
#include "sactypes.h"

Word ISNIL(a)
       Word a;
{
 return(a == BETA);
}
