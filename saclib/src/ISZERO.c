/*======================================================================
<macro>               t <- ISZERO(a)

Test for zero.

Inputs
  a  : an object.

Outputs
  t  : a BETA-digit.
       t = 1 if a is the atom 0,
       t = 0 otherwise.
======================================================================*/
#include "sactypes.h"

Word ISZERO(a)
       Word a;
{
 return(a == 0);
}
