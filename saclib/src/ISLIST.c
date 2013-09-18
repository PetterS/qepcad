/*===========================================================================
<macro>               t <- ISLIST(a)

Is list.

Inputs
  a  : a Word.

Outputs
  t  :  a BETA-digit.
        t = 1 if a is a list (possibly NIL),
        t = 0 otherwise.
===========================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word ISLIST(a)
       Word a;
{
  return((BETA < a && a < BETAp && (a & 1)) || a == BETA);
}
