/*======================================================================
<macro>               t <- ISGCA(a)

Test for GCA handle.

Inputs
  a  : a Word.

Outputs
  t  :  a BETA-digit.
        t = 1 if a is a GCA handle,
        t = 0 otherwise.
======================================================================*/
#ifndef NO_SACLIB_MACROS
#define NO_SACLIB_MACROS
#endif
#include "saclib.h"

Word ISGCA(a)
       Word a;
{
 return(BETAp < (a) && (a) < BETApp);
}
