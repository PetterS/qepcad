/*======================================================================
<macro>               a <- GCAGET(A,i)

Garbage collected array get element.

Inputs
  A : a GCA handle.
  i : a BETA-digit.

Outputs
  a : a Word, the i-th element of the array referenced by A (with 0 being
      the index of the first element).
======================================================================*/
#include "sactypes.h"
extern GCArray *GCASPACEBp;

Word GCAGET(A,i)
     Word A,i;
{
 return(GCASPACEBp[(A)].array[(i)]);
}
