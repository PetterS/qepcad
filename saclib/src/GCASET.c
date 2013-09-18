/*======================================================================
<macro>                    GCASET(A,i,a)

Garbage collected array set element.

Inputs
  A : a GCA handle.
  i : a BETA-digit.
  a : a Word.

Side effects
  The i-th element of the array referenced by A is set to a (with 0 being
  the index of the first element). 
======================================================================*/
#include "sactypes.h"
extern GCArray *GCASPACEBp;

void GCASET(A,i,a)  
     Word A,i,a;
{
 GCASPACEBp[(A)].array[(i)] = (a);
}
